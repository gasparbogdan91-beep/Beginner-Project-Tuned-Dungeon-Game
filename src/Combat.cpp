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

bool g_isPlayerTurn{ true };
bool g_isEnemyTurn{ false };

enum class PlayerChoices{

    choiceAttack,
    choiceChooseSkill,
    choiceDefend,
    choiceSkipTurn,
    max_choices,
};

enum class EnemyChoices {
    choiceAttack,
    castSkill,
    choiceDefend,
    choiceSkipTurn,
    max_choices,
};

PlayerChoices playerChoice(Character& player)
{
    
    int input;

    std::cin >> input;

    switch (input)
    {
    case 1: return PlayerChoices::choiceAttack; break;
    case 2: return PlayerChoices::choiceChooseSkill; break;
    case 3: return PlayerChoices::choiceDefend; break;
    case 4: return PlayerChoices::choiceSkipTurn; break;

    default: return PlayerChoices::choiceSkipTurn; break;

    }


}

void castChoice(PlayerChoices& choice, Character& player, Character& target)
{
    switch (choice) {
    case PlayerChoices::choiceAttack: {

        int damage{ player.getAttackDamage() };
        for (int i{ 0 }; i < player.getAttackSpeed(); i++)
        {

            if (target.isAlive()) {
                if (player.getAttackSpeed() == 0) {
                    target.takeDamage(0);
                }
                else { target.takeDamage(damage); }
            }
        }
    }



    case PlayerChoices::choiceChooseSkill: {
        
        SkillId skill{ player.askChoice() };
        int skillcost{ player.getSkillCost(skill) };
        if (player.hasAcquiredSkill(skill) && player.getMana() > skillcost)
            player.castSkill(skill, player, target);

    }


    case PlayerChoices::choiceDefend:  break;
    case PlayerChoices::choiceSkipTurn:  break;
    }
}




int castToInt(PlayerChoices& choice)
{
    switch (choice) {
    case PlayerChoices::choiceAttack: return 1; break;
    case PlayerChoices::choiceChooseSkill: return 2; break;
    case PlayerChoices::choiceDefend: return 3; break;
    case PlayerChoices::choiceSkipTurn: return 4; break;
    }
}

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

 
    
    
    void combatLoop(Character& player, Character& target)
    {
        assert(g_isPlayerTurn == true && g_isEnemyTurn == false);

        while (player.isAlive() && target.isAlive()) {
            
            if (g_isPlayerTurn && !player.isStunned()) {

             
                applyTicks(player);
                PlayerChoices choice{ playerChoice(player) };
      
                castChoice(choice, player, target);
                
                g_isPlayerTurn == false;


                









            }
            
















        }
        
    }

  

  
}
