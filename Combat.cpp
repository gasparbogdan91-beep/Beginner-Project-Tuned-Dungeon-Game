//
// Created by bgdan on 10/3/26.
//


#include "Character.h"
#include "MonsterTable.h"
#include "Combat.h"
#include "Config.h"
#include "RollRNG.h"


namespace TurnSys {
    bool pTurn = false;
    bool npcTurn = false;


    int playerTurn(const Character& player, bool pTurn) {

        int choice = player.askChoice();
        switch (choice) {
            case 1: pTurn = false; return 1;
            case 2: pTurn = false; return 2;
            case 3: pTurn = false; return 3;
            default: pTurn = false; return 3;
        }




    }
    int enemyTurn(const Character& monster) {
        npcTurn = true;
        int choice = monster.askChoice();
        switch (choice) {
            case 1: npcTurn = false; return 1;
            case 2: npcTurn = false; return 2;
            case 3: npcTurn = false; return 3;
            default: npcTurn = false; return 3;
        }

    }




    void skipTurn(const Character& player, const Character& monster)
    {
        if (pTurn) {
            pTurn = false;
            enemyTurn(monster);
        }else {

            npcTurn = false;
            playerTurn(player, pTurn);
        }
    }


    void startTurns(const Character& monster, const Character& player) {
        while (pTurn) {
            playerTurn(player, pTurn);
            skipTurn(player, monster);
            break;
        }
        while (enemyTurn)

};

namespace Combat {
    // TODO(combat), state of the repo on 2026-10-08. Does NOT compile yet (items 1-3).
    // BUILD BREAKERS
    //done 1. Combat.cpp: stray `}` after namespace TurnSys. Inside combatBegin the `}}` after
    //    TurnSys::enemyTurn(Monster) closes the `if` AND the `while`, so ticks, choice and
    //    switch run once, outside the fight loop. Fix the braces first.
    //done 2. Character.cpp learnSkill/hasAcquiredSkill: `for (auto i: size, i++)` is not a valid
    //    for. Use an index loop (std::size_t i{0}; i < size; ++i) or std::find.
    //still on it 3. TurnSys::playerTurn/enemyTurn: the `default:` path leaves the function without a
    //    return (UB), and the end of each function has no return either.
    // SKILL STORAGE (the vector refactor)
    // 4. SkillDb::acquiredSkills/notAcquired are GLOBAL, so the monster "knows" the player's
    //    skills and learnSkill changes them for everyone. Make the known-skills vector a
    //    member of Character. notAcquired is derivable (all ids minus known); drop it.
    // 5. SkillId::Flurry is listed twice in notAcquired, learning it twice pushes it twice.
    //    Also erase() inside an index loop without `break` skips the next element.
    // 6. Stale leftovers: Character::m_acquiredSkills (unsigned) is unused now, and the
    //    "bit position / keep below 32" comment in SkillId.h is obsolete. SkillId.h and
    //    Character.h include each other; SkillId.h needs only <vector>.
    // 7. displaySkills() is declared but never defined (link error once called).
    //    displayChooseSkills() prints raw ints, reads std::cin with no validation (letters
    //    put cin in a fail state forever) and does I/O inside Character. Per the design it
    //    should live outside the rules and return a SkillId (raylib later).
    // TURN SYSTEM
    // 8. TurnSys::pTurn/npcTurn are never read for any decision, and playerTurn/enemyTurn only
    //    return a number, the monster never acts. Delete the flags; the loop order IS the
    //    turn order: player acts -> monster acts -> ticks -> decrement.
    // 9. skipTurn() calls enemyTurn and playerTurn recursively and the loop then calls
    //    enemyTurn again (monster would act twice). Stun should simply skip the action
    //    inside the loop; the ticks still run.
    // 10. Stun check is inverted: `if (!isStunned())` runs the monster, and a stunned
    //     player still acts. Also decrementTicks() is called at the TOP and again at the
    //     BOTTOM of the round (debuffs expire twice as fast). Keep only the bottom one,
    //     after the enemy's action.
    // 11. Player's choice 4 and 5 (askChoice returns 1-5) do nothing; the player's turn is
    //     lost silently. Same for an unknown/unaffordable skill: print why and re-ask.
    // 12. No isAlive() check after ticks or after the player's action: a monster killed by
    //     the player still takes its turn; a player killed by burn still attacks.
    // 13. The monster never takes ticks (burn/poison/drown) and never regenerates.
    //     Player regenHealth()/regenMana() are never called either. One function that runs
    //     the same round logic for both sides.
    // 14. Skill block: `hasMana()` is redundant with the cost check; spend mana BEFORE
    //     castSkill. Lifesteal/revival: hasRevival() is never consumed anywhere.
    // 15. Character::castSkill passes `target` to castRevival; it is a self-buff, it must
    //     get `caster` (right now it buffs the enemy).
    // RULES STILL OPEN
    // 16. Ticks: poison is lround(5% of maxHP) (0 below 10 max HP, design says minimum 1);
    //     burn is flat 20 (design said % of max HP); drown 30% of max mana. Percents and the
    //     20 belong in Config.h. Write one helper for tick damage.
    // 17. Exhausted: the branch is empty. Do not overwrite attack speed; let Combat refuse
    //     basic attacks while isExhausted(). Attack speed 0 still needs a fallback (Combat.h).
    // 18. Combat is not declared in Combat.h and main() is empty; nothing calls combatBegin.
    //     After the loop: report winner, give XP, revival check. Spawning a monster from
    //     stats(MonsterType, player) is not wired up.
    // 19. Small: parameters named `Player`/`Monster` look like types (use player/monster);
    //     hasCrit()/hasEvaded() are non-const and not [[nodiscard]]; `;;` in askChoice.
    void combatBegin(Character& Player, Character& Monster) {
        while (Player.isAlive() && Monster.isAlive()) {


            //before choice check for ticks,
            if (!Player.isStunned()) {
                Player.decrementTicks();
                TurnSys::enemyTurn(Monster);

            }
            if (Player.isBurned()) {
                Player.takeTrueDamage(20);
            }

            if (Player.isPoisoned()) {
                int damage = Player.getMaxHealth();
                Player.takeTrueDamage(std::lround(damage * 0.05f));}

            if (Player.isDrowned()) {
                int drown = Player.getMaxMana();
                Player.manaDecrease(std::lround(drown * 0.3f));}

            if (Player.isExhausted()) {
                //will change later. Player.setAttackSpeed(0);
            }

            //choosetarget





            //askchoice
            int choice =  TurnSys::playerTurn(Player);
            switch (choice) {
                case 1:  Target::basicAttack(Player, Monster);
                    break;
                case 2: {
                    SkillId skill = Player.displayChooseSkills();
                    if (Player.hasAcquiredSkill(skill) && Player.hasMana()){
                        int cost = Player.getSkillCost(skill); int mana = Player.getMana();
                        if (mana >= cost) {
                            Player.castSkill(skill, Player, Monster);
                            Player.manaDecrease(cost);
                        }
                    }
                    break;}
                case 3: TurnSys::skipTurn(Player, Monster); break;
                default: break;
            }



            Player.decrementTicks();
            TurnSys::enemyTurn(Monster);



        }
    }
}
