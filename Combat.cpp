//
// Created by bgdan on 10/3/26.
//

#include "Combat.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <optional>
#include <random>

#include "Character.h"
#include "Config.h"
#include "MonsterTable.h"
#include "RollRNG.h"

namespace {
    // Burn, poison and drown hit before the actor decides anything, stun or not.
    void applyTicks(Character& character) {
        if (character.isBurned()) {
            character.takeTrueDamage(Config::burnTickDamage);
        }
        if (character.isPoisoned()) {
            character.takeTrueDamage(std::lround(character.getMaxHealth() * Config::poisonTickPercent));
        }
        if (character.isDrowned()) {
            character.manaDecrease(std::lround(character.getMaxMana() * Config::drownTickPercent));
        }
    }

    // ---- player input (the only place that touches std::cin) ----

    // Reads a whole number in [low, high]; asks again on letters or out-of-range numbers.
    // Returns nothing when the input stream is closed.
    std::optional<int> readNumber(int low, int high) {
        int value{};
        while (true) {
            if (std::cin >> value && value >= low && value <= high) {
                return value;
            }
            if (std::cin.eof()) {
                return std::nullopt;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter a number from " << low << " to " << high << ".\n";
        }
    }

    int playerChoice() {
        std::cout << "1) Attack  2) Skill  3) Skip\n> ";
        return readNumber(1, 3).value_or(3);
    }

    SkillId playerSkill(const Character& player) {
        const auto& known{player.getAcquiredSkills()};
        if (known.empty()) {
            std::cout << "You know no skills.\n";
            return noSkill;
        }
        for (std::size_t i{0}; i < known.size(); ++i) {
            std::cout << i + 1 << ") " << skillName(known[i])
                      << " (" << player.getSkillCost(known[i]) << " mana)\n";
        }
        std::cout << "0) Back\n> ";
        const int pick{readNumber(0, static_cast<int>(known.size())).value_or(0)};
        if (pick == 0) {
            return noSkill;
        }
        return known[static_cast<std::size_t>(pick) - 1];
    }

    // ---- monster decisions ----

    int monsterChoice() {
        const int result{roll100(rng)};
        if (result <= 60) return 1;
        if (result <= 95) return 2;
        return 3;
    }

    SkillId monsterSkill(const Character& monster) {
        const auto& known{monster.getAcquiredSkills()};
        if (known.empty()) {
            return noSkill;
        }
        std::uniform_int_distribution<std::size_t> pick{0, known.size() - 1};
        return known[pick(rng)];
    }

    // ---- turn logic ----

    // Returns true when the choice used up the turn, false when it was invalid (ask again).
    bool performAction(Character& actor, Character& other, bool isPlayer) {
        const int choice{isPlayer ? playerChoice() : monsterChoice()};
        switch (choice) {
            case 1:
                if (actor.isExhausted()) {
                    if (isPlayer) std::cout << "Exhausted: you cannot basic attack.\n";
                    return false;
                }
                std::cout << (isPlayer ? "You attack.\n" : "The monster attacks.\n");
                Target::basicAttack(actor, other);
                return true;
            case 2: {
                const SkillId skill{isPlayer ? playerSkill(actor) : monsterSkill(actor)};
                if (!actor.hasAcquiredSkill(skill)) {
                    return false;
                }
                const int cost{actor.getSkillCost(skill)};
                if (actor.getMana() < cost) {
                    if (isPlayer) std::cout << "Not enough mana.\n";
                    return false;
                }
                actor.manaDecrease(cost);
                std::cout << (isPlayer ? "You cast " : "The monster casts ") << skillName(skill) << ".\n";
                actor.castSkill(skill, actor, other);
                return true;
            }
            case 3:
                std::cout << (isPlayer ? "You skip your turn.\n" : "The monster waits.\n");
                return true;
            default:
                return false;
        }
    }

    // One turn for one side: ticks, regen, then the action (unless stunned),
    // then own counters count down.
    void takeTurn(Character& actor, Character& other, bool isPlayer) {
        applyTicks(actor);
        if (!actor.isAlive()) {
            return;
        }
        actor.regenHealth();
        actor.regenMana();
        if (actor.isStunned()) {
            std::cout << (isPlayer ? "You are stunned and lose your turn.\n"
                                   : "The monster is stunned and loses its turn.\n");
        } else {
            while (!performAction(actor, other, isPlayer)) {
            }
        }
        actor.decrementTicks();
    }

    // A fallen character with a Revival buff comes back once, at a share of max health.
    void tryRevive(Character& character, bool isPlayer) {
        if (character.isAlive() || !character.hasRevival()) {
            return;
        }
        character.useRevival();
        character.setHealth(std::max(1, static_cast<int>(
            std::lround(character.getMaxHealth() * Config::revivalHealthPercent))));
        std::cout << (isPlayer ? "Revival! You rise again.\n" : "Revival! The monster rises again.\n");
    }

    void rewardKill(Character& player) {
        const int levelBefore{player.getLevel()};
        const int reward{Config::xpRewardBase + Config::xpRewardPerLevel * levelBefore};
        player.addXp(reward);
        std::cout << "Victory! +" << reward << " xp ("
                  << player.getXp() << "/" << player.xpToNextLevel() << ")\n";
        for (int level{levelBefore + 1}; level <= player.getLevel(); ++level) {
            std::cout << "Level up! You are now level " << level << ".\n";
            const SkillId unlocked{Config::specialSkillForLevel(level)};
            if (unlocked != noSkill) {
                std::cout << "New skill unlocked: " << skillName(unlocked) << "!\n";
            }
        }
    }

    void printStatus(const Character& player, const Character& monster) {
        std::cout << "\nYou: " << player.getHealth() << "/" << player.getMaxHealth() << " hp, "
                  << player.getMana() << "/" << player.getMaxMana() << " mana"
                  << "   |   Monster: " << monster.getHealth() << "/" << monster.getMaxHealth() << " hp\n";
    }
}

namespace Combat {
    // TODO(combat), remaining:
    // - Poison is lround(5% of maxHP): 0 below 10 max HP; the design said minimum 1.
    // - Exhausted: attack speed 0 still needs a fallback (Combat.h).
    // - Buffs: a counter set on your own turn is decremented at the end of that same turn,
    //   so "Invisible 1" blocks nothing. Decide: +1 turn, or decrement only on the enemy's turn.
    // - Debuff counters carry over between fights (nothing clears them).
    // - Boons (rollBoonChanceAfterFight / drawThreeBoonsOnLvlUp) are not wired in.
    // - hasCrit()/hasEvaded() are non-const and not [[nodiscard]].

    Character spawnMonster(const Character& player) {
        switch (rollspawn(rng)) {
            case 1: return Character{stats(MonsterType::Goblin, player)};
            case 2: return Character{stats(MonsterType::Serpent, player)};
            case 3: return Character{stats(MonsterType::Stoner, player)};
            case 4: return Character{stats(MonsterType::Archer, player)};
            case 5: return Character{stats(MonsterType::Magma, player)};
            default: return Character{stats(MonsterType::Lich, player)};
        }
    }

    void combatBegin(Character& player, Character& monster) {
        while (player.isAlive() && monster.isAlive()) {
            printStatus(player, monster);
            takeTurn(player, monster, true);
            tryRevive(player, true);
            tryRevive(monster, false);
            if (!player.isAlive() || !monster.isAlive()) {
                break;
            }
            takeTurn(monster, player, false);
            tryRevive(player, true);
            tryRevive(monster, false);
        }
        if (player.isAlive()) {
            rewardKill(player);
        } else {
            std::cout << "You died.\n";
        }
    }
}
