//
// Created by bgdan on 10/3/26.
//


#include "RollRNG.h"
#include "Character.h"
#include "MonsterTable.h"
#include "Combat.h"

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