//
// Created by bgdan on 10/3/26.
//

#ifndef PROJECT1_COMBAT_H
#define PROJECT1_COMBAT_H
#include "Character.h"

namespace Combat {
    Character spawnMonster(const Character& player);
    void combatBegin(Character& player, Character& monster);
}

// TODO(combat rule): attack speed can legitimately be 0 (ZeroAttackSpeedTripleSP boon).
// A character with getAttackSpeed() == 0 cannot basic-attack, so Combat needs an
// alternative action for that case (e.g. skills only, or a fallback single hit).








#endif //PROJECT1_COMBAT_H