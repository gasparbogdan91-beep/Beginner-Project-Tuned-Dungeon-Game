//
// Created by bgdan on 10/5/26.
//

#include "Boon.h"
#include <cmath>
#include "RollRNG.h"


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



void applyBoon(BoonID id, Character& target) {
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

bool rollBoonChanceAfterFight() {
    int result = roll25(rng);
    return result == 13;

}

BoonChoices drawThreeBoonsOnLvlUp() {
    BoonID first { castToBoonID(rollboon(rng))};
    BoonID second {castToBoonID(rollboon(rng))};
    while (first == second) {
        second =  castToBoonID(rollboon(rng));
    }
    BoonID third {castToBoonID(rollboon(rng))};

    while (first == third || third == second) {
        third =  castToBoonID(rollboon(rng));
    }
    return {first, second, third};
}

SingleBoon drawSingleBoon() {
    BoonID single {castToBoonID(rollboon(rng))};
    return {single};
}

