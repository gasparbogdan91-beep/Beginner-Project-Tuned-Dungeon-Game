//
// Created by bgdan on 10/1/26.
//

#ifndef PROJECT1_CONFIG_H
#define PROJECT1_CONFIG_H
#include "Character.h"
#include "RollRNG.h"

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

enum class SpecialSkillID {
    Exhaust = 14,
    Drown = 15,
    Consumption = 16,
    Plague = 17,
    Revival = 18,
    Ruin = 19,
    Vampire = 20,
    Explosion = 21,
};


enum class BoonID {
    //hp boons//
    FifteenHPIncrease = 1,
    HealMax = 2,
    TenHPRegenIncrease = 3,
    HalveHPRegenThird = 4,
    MaxHPIncreaseTwenty = 5,
    DoubleMaxHPHalvePower = 6,
    ThirdHPDoublePower = 7,
    IncreaseMaxManaFifteen = 8,
    HealMaxMana = 9,
    IncreaseManaRegenTwenty = 10,
    IncreaseManaRegenTen = 11,
    IncreaseManaRegenTwentyPercent = 12,
    ThirdManaDefenseIncreaseThird = 13,
    IncreaseBaseDefenseTen = 14,
    IncreaseBaseDefenseTwentyBoon = 15,
    IncreaseDefenseMultiplierFive = 16,
    IncreaseDefenseMultiplierTen = 17,
    IncreaseCritChanceTen = 18,
    IncreaseCritChanceFive = 19,
    IncreaseAttackSpeed = 20,
    ZeroAttackSpeedTripleSP = 21,
    IncreaseEvadeFive = 22,
    IncreaseEvadeTen = 23,
    IncreaseSPTenPercent = 24,
    IncreaseSPTen = 25,
    IncreaseSPTwenty = 26,
    DoubleSPHalfDefense = 27,
    IncreaseSPFivePercent = 28,
    MoreManaMoreSP = 29,
    ConvertSPToMaxHP = 30,
    IncreaseADBaseFifteen = 31,
    IncreaseADBaseTwenty = 32,
    MoreADMoreDefense = 33,
    DoubleADHalveHP = 34,
    IncreaseLifestealTen = 35,
    IncreaseLifestealFive = 36,
    MaxLifestealThirdHP = 37,
};



struct Boon {
    //hp boons
    static constexpr void increaseMaxHPByFifteenBoon(Character& target) {
        target.increaseMaxHealthByMultiplier(1.15f);
    }
    static constexpr void healToMaxHPBoon(Character& target) {
        int currentmaxHP = target.getMaxHealth();
        target.setHealth(currentmaxHP);
    }
    static constexpr void increaseHPRegenBaseByTenBoon(Character& target) {
        target.hpRegenIncrease(10);
    }
    static constexpr void halveHPandRegenThirdBoon(Character& target) {
        int currentmaxHP = target.getMaxHealth();
        int third = std::lround((currentmaxHP * 0.3f));
        target.setMaxHealth(currentmaxHP / 2);
        target.setHpRegen(third);
    }
    static constexpr void increaseMaxHPByTwentyBoon(Character& target) {
        target.increaseMaxHealthByMultiplier(1.2f);
    }
    static constexpr void doubleMaxHPandHalfPowerBoon(Character& target) {
        int currentmaxHP = target.getMaxHealth();
        int skillpower = target.getSkillPower();
        int attackdamage = target.getAttackDamage();
        int halfSP = skillpower / 2;
        int halfAD = attackdamage / 2;
        target.setMaxHealth(2 * currentmaxHP);
        target.setSkillPower(halfSP);
        target.setAttackDamage(halfAD);
    }

    static constexpr void thirdHPandDoublePowerBoon(Character& target) {
        int currentmaxHP = target.getMaxHealth();
        int skillpower = target.getSkillPower();
        int attackdamage = target.getAttackDamage();
        int thirdHP = currentmaxHP / 3;
        int doubleAD = std::lround(attackdamage * 2);
        int doubleSP = std::lround(skillpower * 2);
        target.setMaxHealth(thirdHP);
        target.setSkillPower(doubleSP);
        target.setAttackDamage(doubleAD);



    }

    //mana boons

    static constexpr void increaseMaxManaByFifteenBoon(Character& target) {
        target.increaseMaxManaByMultiplier(1.15f);
    }

    static constexpr void healToMaxManaBoon(Character& target) {
        int currentmaxMana = target.getMaxMana();
        target.setMana(currentmaxMana);
    }

    static constexpr void increaseManaRegenBaseByTwentyBoon(Character& target) {
        target.manaRegenIncrease(20);
    }

    static constexpr void increaseManaRegenBaseByTenBoon(Character& target) {
        target.manaRegenIncrease(10);
    }

    static constexpr void increaseManaRegenToTwentyPercentBoon(Character& target) {
        int currentmaxMana = target.getMaxMana();
        int percentage = std::lround((currentmaxMana * 0.2f));
        target.manaRegenIncrease(percentage);
    }

    static constexpr void thirdManaDefenseIncreaseThirdBoon(Character& target) {
        int currentmaxMana = target.getMaxMana();
        int currentdefense = target.getDefense();
        int thirdmana = currentmaxMana / 3;
        int thirdDEF = currentdefense / 3;
        target.setMaxMana(thirdmana);
        target.setDefense(currentdefense + thirdDEF);
    }

    //defense boons
    static constexpr void increaseBaseDefenseTenBoon(Character& target) {
        target.defenseIncrease(10);
    }

    static constexpr void increaseBaseDefenseTwentyBoon(Character& target) {
        target.defenseIncrease(20);
    }

    static constexpr void increaseDefenseMultiplierFiveBoon(Character& target) {
        int currentdefense = target.getDefense();
        target.setDefense(std::lround(currentdefense * 1.05f));
    }
    static constexpr void increaseDefenseMultiplierTenBoon(Character& target) {
        int currentdefense = target.getDefense();
        target.setDefense(std::lround(currentdefense * 1.10f));
    }

    // crit chance boons

    static constexpr void critChanceIncreaseByTenBoon(Character& target) {
        target.increaseCritChance(10);

    }

    static constexpr void critChanceIncreaseByFiveBoon(Character& target) {
        target.increaseCritChance(5);
    }

    //attack speed increase
    static constexpr void attackSpeedIncreaseBoon(Character& target) {
        target.increaseAttackSpeed(1);
    }

    static constexpr void attackSpeedZeroButTripleSPBoon(Character& target) {
        target.setAttackSpeed(0);
        int skillpower = target.getSkillPower();
        target.setSkillPower(3 * skillpower);
    }

    //evade chance

    static constexpr void evadeChanceIncreaseFiveBoon(Character& target) {
        target.evadeChanceIncrease(5);
    }

    static constexpr void evadeChanceIncreaseTenBoon(Character& target) {
        target.evadeChanceIncrease(10);
    }

    //skill power

    static constexpr void increaseSkillPowerByTenPercentBoon(Character& target) {
        int SP = target.getSkillPower();
        target.setSkillPower(std::lround(SP * 1.1f));
    }

    static constexpr void increaseSkillPowerByTenBoon(Character& target) {
        target.skillPowerIncrease(10);
    }

    static constexpr void increaseSkillPowerByTwentyBoon(Character& target) {
        target.skillPowerIncrease(20);
    }

    static constexpr void doubleSPHalfDefenseBoon(Character& target) {
        int SP = target.getSkillPower();
        int DEF = target.getDefense();
        target.setDefense(std::lround(DEF * 0.5f));
        target.setSkillPower(std::lround(SP * 2.0f));
    }

    static constexpr void increaseSkillPowerByFivePercentBoon(Character& target) {
        int SP = target.getSkillPower();
        target.setSkillPower(std::lround(SP * 1.05f));
    }

    static constexpr void moreManaMoreSPBoon(Character& target) {
        int maxmana = target.getMaxMana();
        int SP = target.getSkillPower();
        target.setMaxMana(std::lround(maxmana * 1.05f));
        target.setSkillPower(std::lround(SP * 1.05f));
    }
    static constexpr void convertSPToMaxHP(Character& target) {
        int SP = target.getSkillPower();
        int maxHP = target.getMaxHealth();
        target.setSkillPower(0);
        target.setMaxHealth(maxHP + SP);
    }

    //attack damage

    static constexpr void increaseAttackDamageBaseByFifteenBoon(Character& target) {
        target.attackDamageIncrease(15);
    }

    static constexpr void increaseAttackDamageBaseByTwentyBoon(Character& target) {
        target.attackDamageIncrease(20);
    }

    static constexpr void moreADMoreDefenseBoon(Character& target) {
        int defense = target.getDefense();
        int AD = target.getAttackDamage();
        target.setDefense(std::lround(defense * 1.05f));
        target.setAttackDamage(std::lround(AD * 1.05f));

    }

    static constexpr void doubleADHalveHPBoon(Character& target) {
        int maxHP = target.getMaxHealth();
        int AD = target.getAttackDamage();
        target.setMaxHealth(maxHP / 2);
        target.setAttackDamage(AD * 2);
    }



    //lifesteal
    static constexpr void increaseLifestealByBaseTenBoon(Character& target) {
        int lifesteal = target.getLifesteal();
        target.setLifesteal(lifesteal + 10);
    }

    static constexpr void increaseLifestealByFiveBoon(Character& target) {
        int lifesteal = target.getLifesteal();
        target.setLifesteal(lifesteal + 5);
    }

    static constexpr void maxLifestealThirdHPBoon(Character& target) {
        int maxHP = target.getMaxHealth();
        target.setMaxHealth(maxHP / 3);
        target.setLifesteal(100);
    }

};


struct BoonChoices {
    BoonID first;
    BoonID second;
    BoonID third;
};


[[nodiscard]] inline constexpr BoonID toBoonID(int roll) {
    assert(roll >= 1 && roll <= 37 && "Boon roll out of range");
    return static_cast<BoonID>(roll);
}

[[nodiscard]] inline constexpr BoonChoices ListBoons(int rolla, int rollb, int rollc) {
    while (rollb == rolla) { rollb = rollb % 37 + 1; }
    while (rollc == rolla || rollc == rollb) { rollc = rollc % 37 + 1; }
    return { toBoonID(rolla), toBoonID(rollb), toBoonID(rollc) };
}

inline constexpr void applyBoon(BoonID id, Character& target) {
    switch (id) {
        case BoonID::FifteenHPIncrease:             Boon::increaseMaxHPByFifteenBoon(target); break;
        case BoonID::HealMax:                       Boon::healToMaxHPBoon(target); break;
        case BoonID::TenHPRegenIncrease:            Boon::increaseHPRegenBaseByTenBoon(target); break;
        case BoonID::HalveHPRegenThird:             Boon::halveHPandRegenThirdBoon(target); break;
        case BoonID::MaxHPIncreaseTwenty:           Boon::increaseMaxHPByTwentyBoon(target); break;
        case BoonID::DoubleMaxHPHalvePower:         Boon::doubleMaxHPandHalfPowerBoon(target); break;
        case BoonID::ThirdHPDoublePower:            Boon::thirdHPandDoublePowerBoon(target); break;
        case BoonID::IncreaseMaxManaFifteen:        Boon::increaseMaxManaByFifteenBoon(target); break;
        case BoonID::HealMaxMana:                   Boon::healToMaxManaBoon(target); break;
        case BoonID::IncreaseManaRegenTwenty:       Boon::increaseManaRegenBaseByTwentyBoon(target); break;
        case BoonID::IncreaseManaRegenTen:          Boon::increaseManaRegenBaseByTenBoon(target); break;
        case BoonID::IncreaseManaRegenTwentyPercent: Boon::increaseManaRegenToTwentyPercentBoon(target); break;
        case BoonID::ThirdManaDefenseIncreaseThird: Boon::thirdManaDefenseIncreaseThirdBoon(target); break;
        case BoonID::IncreaseBaseDefenseTen:        Boon::increaseBaseDefenseTenBoon(target); break;
        case BoonID::IncreaseBaseDefenseTwentyBoon: Boon::increaseBaseDefenseTwentyBoon(target); break;
        case BoonID::IncreaseDefenseMultiplierFive: Boon::increaseDefenseMultiplierFiveBoon(target); break;
        case BoonID::IncreaseDefenseMultiplierTen:  Boon::increaseDefenseMultiplierTenBoon(target); break;
        case BoonID::IncreaseCritChanceTen:         Boon::critChanceIncreaseByTenBoon(target); break;
        case BoonID::IncreaseCritChanceFive:        Boon::critChanceIncreaseByFiveBoon(target); break;
        case BoonID::IncreaseAttackSpeed:           Boon::attackSpeedIncreaseBoon(target); break;
        case BoonID::ZeroAttackSpeedTripleSP:       Boon::attackSpeedZeroButTripleSPBoon(target); break;
        case BoonID::IncreaseEvadeFive:             Boon::evadeChanceIncreaseFiveBoon(target); break;
        case BoonID::IncreaseEvadeTen:              Boon::evadeChanceIncreaseTenBoon(target); break;
        case BoonID::IncreaseSPTenPercent:          Boon::increaseSkillPowerByTenPercentBoon(target); break;
        case BoonID::IncreaseSPTen:                 Boon::increaseSkillPowerByTenBoon(target); break;
        case BoonID::IncreaseSPTwenty:              Boon::increaseSkillPowerByTwentyBoon(target); break;
        case BoonID::DoubleSPHalfDefense:           Boon::doubleSPHalfDefenseBoon(target); break;
        case BoonID::IncreaseSPFivePercent:         Boon::increaseSkillPowerByFivePercentBoon(target); break;
        case BoonID::MoreManaMoreSP:                Boon::moreManaMoreSPBoon(target); break;
        case BoonID::ConvertSPToMaxHP:              Boon::convertSPToMaxHP(target); break;
        case BoonID::IncreaseADBaseFifteen:         Boon::increaseAttackDamageBaseByFifteenBoon(target); break;
        case BoonID::IncreaseADBaseTwenty:          Boon::increaseAttackDamageBaseByTwentyBoon(target); break;
        case BoonID::MoreADMoreDefense:             Boon::moreADMoreDefenseBoon(target); break;
        case BoonID::DoubleADHalveHP:               Boon::doubleADHalveHPBoon(target); break;
        case BoonID::IncreaseLifestealTen:          Boon::increaseLifestealByBaseTenBoon(target); break;
        case BoonID::IncreaseLifestealFive:         Boon::increaseLifestealByFiveBoon(target); break;
        case BoonID::MaxLifestealThirdHP:           Boon::maxLifestealThirdHPBoon(target); break;
    }
}



struct Target {

    static constexpr void castInvisible(Character& caster) {
        caster.increaseTurnsInvisible(1);
}
    static constexpr void castStrengthened(Character& caster) {
        int currentdefense = caster.getDefense();
        caster.setDefense(std::lround(1.3f * currentdefense ));
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
        target.setMaxHealth(currentmaxHP / 2);
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
        target.setSkillPower(std::lround(currentSP * 0.9f));

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
    static constexpr void castExhaust(Character& target) {
        target.increaseTurnsExhausted(3);

    }
    static constexpr void castDrown(Character& target) {
        target.increaseTurnsDrowned(3);
    }
    static constexpr void castConsumption(Character& caster) {
        int mana = caster.getMana();
        int maxMana = caster.getMaxMana();
        caster.setMana(mana + std::lround(0.3f * maxMana));
    }

    static constexpr void castPlague(Character& target) {
        int currentdefense = target.getDefense();
        int currentmaxHP = target.getMaxHealth();
        target.setMaxHealth(std::lround(currentmaxHP * 0.7f));
        target.defenseDecrease(std::lround(currentdefense * 0.7f));
    }

    static constexpr void castRevival(Character& caster) {
        caster.increaseRevivalEffect(1);
    }

    static constexpr void castRuin(Character& target) {
        int currenthealth = target.getHealth();
        int ratio1 = std::lround(0.15f * currenthealth);
        target.takeDamage(std::lround(ratio1));
        int currenthealth2 = target.getHealth();
        int ratio2 = std::lround(0.15f * currenthealth2);
        target.takeDamage(std::lround(ratio2));
        int currenthealth3 = target.getHealth();
        int ratio3 = std::lround(0.15f * currenthealth3);
        target.takeDamage(std::lround(ratio3));
    }

    static constexpr void castVampire(Character& target, Character& caster) {
        int targetcurrentHP = target.getHealth();
        int biteamount = std::lround(0.3f * targetcurrentHP);
        target.takeDamage(biteamount);
        caster.increaseHealth(biteamount);
    }

    static constexpr void castExplosion(Character& target, Character& caster) {
        int casterSP = caster.getSkillPower();
        int targetmaxHP = target.getMaxHealth();
        target.takeDamage(std::lround(0.15f * targetmaxHP) + std::lround(1.15f * casterSP));

    }


};



#endif //PROJECT1_CONFIG_H