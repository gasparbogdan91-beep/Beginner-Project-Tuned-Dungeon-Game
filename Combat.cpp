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




	void turnBegin(Character& character) {
		applyTicks(character);
		character.regenHealth();
		character.regenMana();
		
   
        character.decrementTicks();

	}

};



