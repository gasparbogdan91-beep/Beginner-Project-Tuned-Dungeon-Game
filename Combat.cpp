//
// Created by bgdan on 10/3/26.
//

#include "cmake-build-debug/Combat.h"
#include "RollRNG.h"
#include "Character.h"
#include "MonsterTable.h"

// RNG System

bool hasCrit(const Character& character) {
    int getter {character.getCritChance()};
    int result = roll100(rng);
    return result <= getter; //if result smaller than the critchance returns bool true

}

bool rollBoon() {
    int result = roll25(rng);
    return result == 13;
}