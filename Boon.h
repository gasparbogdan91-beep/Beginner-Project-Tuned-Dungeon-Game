//
// Created by bgdan on 10/5/26.
//

#ifndef PROJECT1_BOON_H
#define PROJECT1_BOON_H
#include "Character.h"
#include <cmath>



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



;


struct BoonChoices {
    BoonID first;
    BoonID second;
    BoonID third;
};

struct SingleBoon {
    BoonID single;
};


[[nodiscard]] inline constexpr BoonID castToBoonID(int roll) {
    assert(roll >= 1 && roll <= 37 && "Boon roll out of range");
    return static_cast<BoonID>(roll);
}


//forward declarations
void applyBoon(BoonID id, Character& target);
bool rollBoonChanceAfterFight();
BoonChoices drawThreeBoonsOnLvlUp();







#endif //PROJECT1_BOON_H