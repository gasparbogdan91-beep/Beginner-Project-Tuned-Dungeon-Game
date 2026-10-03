//
// Created by bgdan on 10/1/26.
//

#ifndef PROJECT1_CONFIG_H
#define PROJECT1_CONFIG_H
#include "Character.h"

namespace Config {
    inline constexpr float defenseK { 100.0f };
    inline constexpr float critMultiplier { 2.0f };
    inline constexpr int xpBase { 100 };
    inline constexpr double xpGrowth { 1.05 };
    inline constexpr int healthPerLevel { 25 };
    inline constexpr int manaPerLevel { 30 };
    inline constexpr int defensePerLevel { 10 };
}

enum class GenericSkillId {

    Invisible = 1,
    Burn = 2,
    Poison = 3,
    Strengthen = 4,
    Flurry = 5,
    Chaos = 6,
    Skyfall = 7,
    MagmaChamber = 8,
    Stun = 9,
    Fear = 10,
    StoneThrow = 11,
    Agile = 12,
    Heal = 13,
};


struct Target {

    static constexpr void castInvisible(Character& caster) {
        caster.increaseTurnsInvisible(1);
}
    static constexpr void castStrengthened(Character& caster) {
        int currentdefense = caster.getDefense();
        caster.defenseIncrease(0.3f * currentdefense );
    }
    static constexpr void castFlurry(Character& target, const Character& caster) {
        int currentdefense = target.getDefense();
        if (currentdefense < 20){target.defenseDecrease(currentdefense);}else
        {target.defenseDecrease(20);}
        target.takeDamage(std::lround(0.9f * caster.getAttackDamage()));
        if (currentdefense < 20){target.defenseIncrease(currentdefense);}else{target.defenseIncrease(20);}


    }
    static constexpr void castStun(Character& target) {
        target.increaseTurnsStun(1);
    }
    static constexpr void castFear(Character& target) {
        int currentmaxHP = target.getMaxHealth();
        target.setMaxHealth(std::lround(currentmaxHP / 2));
    }
    static constexpr void castPoison(Character& target) {
        target.increaseTurnsPoisoned(1);
    }

    static constexpr void castBurn(Character& target) {
        target.getBurned(1);
    }
    static constexpr void castSkyfall(Character& target, const Character& caster) {
        int skillpower = caster.getSkillPower();
        target.takeDamage(std::lround(2.0f * skillpower));
    }
    static constexpr void castChaos(Character& target) {
        int currentmaxMana = target.getMaxMana();
        int currentSP = target.getSkillPower();
        target.setMaxMana(std::lround(currentmaxMana * 0.9f));
        target.skillPowerDecrease(currentSP * 0.9f);

    }

    static constexpr void castMagmaChamber(Character& target, const Character& caster) {
        int casterSP = caster.getSkillPower();
        int targetmaxHP = target.getMaxHealth();
        target.defenseDecreaseByMultiplier(0.9f);
        target.takeDamage(std::lround((0.1f * targetmaxHP) + (1.0f * casterSP)));
        target.getBurned(1);
    }
    static constexpr void castStoneThrow(Character& target, const Character& caster) {
        int casterdefense = caster.getDefense();
        int castermaxHP = caster.getMaxHealth();
        target.takeDamage(std::lround(0.15f * castermaxHP + 0.25f * casterdefense));

    }
    static constexpr void castAgile(Character& caster) {
        int currentdefense = caster.getDefense();
        caster.defenseIncrease(std::lround(0.05f * currentdefense));
        caster.evadeChanceIncrease(15);
    }
    static constexpr void castHeal(Character& caster) {
        int castermaxHP = caster.getMaxHealth();
        int currentHP = caster.getHealth();
        caster.setHealth(currentHP + std::lround(0.2f * castermaxHP));

    }
};

#endif //PROJECT1_CONFIG_H