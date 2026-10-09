#include <iostream>

#include "Character.h"
#include "Combat.h"

namespace {
    // The player starts knowing every generic skill; the special ones unlock by level.
    void learnGenericSkills(Character& player) {
        for (int id{static_cast<int>(SkillId::Invisible)}; id <= static_cast<int>(SkillId::Heal); ++id) {
            player.learnSkill(static_cast<SkillId>(id));
        }
    }

    bool askFightAgain() {
        char answer{};
        std::cout << "\nFight another monster? (y/n) ";
        std::cin >> answer;
        return std::cin && (answer == 'y' || answer == 'Y');
    }
}

int main() {
    Character player{CharacterStats{}};
    learnGenericSkills(player);

    do {
        Character monster{Combat::spawnMonster(player)};
        std::cout << "\nA monster appears! (" << monster.getMaxHealth() << " hp, "
                  << monster.getAttackDamage() << " attack)\n";
        Combat::combatBegin(player, monster);
    } while (player.isAlive() && askFightAgain());

    return 0;
}
