//
// Created by bgdan on 10/3/26.
//


#include "Character.h"
#include "MonsterTable.h"
#include "Combat.h"
#include "Config.h"


namespace Combat {

    // TODO(combatBegin): known problems, fix next session. File does NOT compile yet (items 1, 2).
    // 1. Line `if (Player.hasAcquiredSkill(skill))`: `skill` is undeclared (input step not built yet).
    //    The `}` after Target::basicAttack closes the outer while, so the skill block sits outside
    //    the fight loop and the final `}` of the file is extra. Fix braces; comment out the skill
    //    block until the choice step exists.
    // 2. Skill block: check getMana() >= getSkillCost(skill) first, then spend, then castSkill.
    //    Currently it casts first and subtracts after, so an unaffordable skill still casts.
    // 3. Stun: `if (!Player.isStunned()) {}` has an empty body. Plan: a skipTurn() in the turn
    //    system. Ticks must still run when stunned; only the action is skipped.
    // 4. After the ticks, check isAlive(). A player killed by burn/poison still attacks.
    // 5. decrementTicks() runs BEFORE the action, so 1-turn debuffs expire before they matter
    //    (e.g. invisible). Move it to the end of the round, after the enemy's action.
    // 6. The monster never acts or takes ticks. Same turn logic for both sides.
    // 7. Exhausted: do not overwrite attack speed (it is never restored). Let Combat treat an
    //    exhausted character as unable to basic-attack while isExhausted() is true.
    // 8. Poison: lround(5% of maxHP) is 0 below 10 max HP; design says minimum 1.
    //    Burn is a flat 20; design said a percentage of max HP. Percents belong in Config.h.
    // 9. Basic attack always runs; the player's choice (basic attack vs skill) is not read yet.
    //    Attack speed 0 has no fallback action (see TODO in Combat.h).
    void combatBegin(Character& Player, Character& Monster) {

        while (Player.isAlive() && Monster.isAlive()) {


            //before choice check for ticks,
            if (!Player.isStunned()) {}//skipturn}

            if (Player.isBurned()) {
                Player.takeTrueDamage(20);}

            if (Player.isPoisoned()) {
                    int damage = Player.getMaxHealth();
                    Player.takeTrueDamage(std::lround(damage * 0.05f));}

            if (Player.isDrowned()) {
                    int drown = Player.getMaxMana();
                    Player.manaDecrease(std::lround(drown * 0.3f));}

            if (Player.isExhausted()) {
                //will change later. Player.setAttackSpeed(0);
            }


            //askchoice


            Player.decrementTicks();//while player choice is basic attack,
            Target::basicAttack(Player, Monster);} //break out of while

            //while player choice is cast skill
            //display acquired skills.
            //player chooses skill > input comes back > we check
            if (Player.hasAcquiredSkill(skill)){
                Player.castSkill(skill, Player, Monster);
                int cost = Player.getSkillCost(skill);
                Player.manaDecrease(cost);
            }

            //while player choice is
        }






    }





}