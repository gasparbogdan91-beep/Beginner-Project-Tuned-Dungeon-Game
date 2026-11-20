//
// Created by bgdan on 10/3/26.
//


#ifndef PROJECT1_MONSTERTABLE_H
#define PROJECT1_MONSTERTABLE_H

#include <cmath>
#include "Character.h"
#include "RollRNG.h"
inline int scale(int value, float ratio) {
    return static_cast<int>(std::lround(value * ratio));
}

inline int basePlusScale(int value, int base, float ratio) {
    return static_cast<int>(std::lround(base+(value * ratio)));
}
enum class MonsterType {
    Goblin = 1,
    Serpent = 2,
    Stoner = 3,
    Magma = 4,
    Lich = 5,

};


inline MonsterType rollMonster() {


    int roll = rollspawn(rng);

    switch (roll) {
    case 1: return MonsterType::Goblin; break;

    case 2: return MonsterType::Serpent; break;

    case 3: return MonsterType::Stoner; break;

    case 4: return MonsterType::Magma; break;

    case 5: return MonsterType::Lich; break;

    }



}


inline CharacterStats stats(MonsterType type, const Character& player) {
    const int hp   { player.getMaxHealth() };
    const int mana { player.getMaxMana() };
    const int def  { player.getDefense() };
    const int lvl  { player.getLevel() };

    switch (type) {
        case MonsterType::Goblin:
            return { .health = scale(hp, 0.5f), .maxHealth = scale(hp, 0.5f),
                     .mana = scale(mana, 1.0f), .maxMana = scale(mana, 1.0f),
                     .defense = basePlusScale(def, 5, 0.1f), .skillPower = 1 * lvl,
                     .manaRegen = scale(mana, 0.1f), .attackDamage = scale(hp, 0.05f),
                     .attackSpeed = 1 };
        case MonsterType::Serpent:
            return { .health = scale(hp, 0.8f), .maxHealth = scale(hp, 0.8f),
                     .mana = scale(mana, 2.0f), .maxMana = scale(mana, 2.0f),
                     .defense = basePlusScale(def, 0, 0.5f), .skillPower = 2 * lvl,
                     .manaRegen = scale(mana, 0.2f), .attackDamage = scale(hp, 0.02f),
                     .attackSpeed = 1 };
        case MonsterType::Stoner:
            return { .health = scale(hp, 1.35f), .maxHealth = scale(hp, 1.35f),
                     .mana = scale(mana, 0.3f), .maxMana = scale(mana, 0.3f),
                     .defense = basePlusScale(def, 30, 0.75f), .skillPower = 1 * lvl,
                     .manaRegen = scale(mana, 0.1f), .attackDamage = scale(hp, 0.18f),
                     .attackSpeed = 1 };
        
        case MonsterType::Magma:
            return { .health = scale(hp, 0.3f), .maxHealth = scale(hp, 0.3f),
                     .mana = scale(mana, 1.5f), .maxMana = scale(mana, 1.5f),
                     .defense = basePlusScale(def, 8, 0.3f), .skillPower = 2 * lvl,
                     .manaRegen = scale(mana, 0.3f), .attackDamage = scale(hp, 0.05f),
                     .attackSpeed = 1 };
        case MonsterType::Lich:
            return { .health = scale(hp, 1.0f), .maxHealth = scale(hp, 1.0f),
                     .mana = scale(mana, 3.0f), .maxMana = scale(mana, 3.0f),
                     .defense = basePlusScale(def, 0, 0.1f), .skillPower = player.getSkillPower(),
                     .manaRegen = scale(mana, 1.0f), .attackDamage = scale(hp, 0.05f),
                     .attackSpeed = 1 };
        default:
            return {};
    }
}
#endif //PROJECT1_MONSTERTABLE_H
