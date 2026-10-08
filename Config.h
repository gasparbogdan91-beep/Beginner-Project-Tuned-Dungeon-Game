//
// Created by bgdan on 10/1/26.
//

#ifndef PROJECT1_CONFIG_H
#define PROJECT1_CONFIG_H
#include "Character.h"
#include "RollRNG.h"
#include "SkillId.h"

namespace Config {
    inline constexpr float defenseK { 100.0f };
    inline constexpr float critMultiplier { 2.0f };
    inline constexpr int xpBase { 100 };
    inline constexpr double xpGrowth { 1.05 };
    inline constexpr int healthPerLevel { 35 };
    inline constexpr int manaPerLevel { 40 };
    inline constexpr int defensePerLevel { 10 };

    // tick damage, applied at the start of the affected character's turn
    inline constexpr int burnTickDamage { 20 };            // flat true damage
    inline constexpr float poisonTickPercent { 0.05f };    // of max health
    inline constexpr float drownTickPercent { 0.3f };      // of max mana

    inline constexpr float revivalHealthPercent { 0.5f };  // of max health, when Revival fires

    // xp for a kill = xpRewardBase + xpRewardPerLevel * (player level)
    inline constexpr int xpRewardBase { 50 };
    inline constexpr int xpRewardPerLevel { 5 };

    // the level at which each special skill unlocks
    inline constexpr int exhaustUnlockLevel { 3 };
    inline constexpr int drownUnlockLevel { 5 };
    inline constexpr int consumptionUnlockLevel { 7 };
    inline constexpr int plagueUnlockLevel { 9 };
    inline constexpr int revivalUnlockLevel { 11 };
    inline constexpr int ruinUnlockLevel { 13 };
    inline constexpr int vampireUnlockLevel { 15 };
    inline constexpr int explosionUnlockLevel { 17 };

    // which special skill (if any) is unlocked on reaching this exact level
    [[nodiscard]] constexpr SkillId specialSkillForLevel(int level) {
        switch (level) {
            case exhaustUnlockLevel:     return SkillId::Exhaust;
            case drownUnlockLevel:       return SkillId::Drown;
            case consumptionUnlockLevel: return SkillId::Consumption;
            case plagueUnlockLevel:      return SkillId::Plague;
            case revivalUnlockLevel:     return SkillId::Revival;
            case ruinUnlockLevel:        return SkillId::Ruin;
            case vampireUnlockLevel:     return SkillId::Vampire;
            case explosionUnlockLevel:   return SkillId::Explosion;
            default:                     return noSkill;
        }
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
        target.setMaxMana(std::lround(currentmaxMana * 0.75f));
        target.setSkillPower(std::lround(currentSP * 0.75f));

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

    static constexpr void basicAttack(Character& caster, Character& target) {
        int attackspeed = caster.getAttackSpeed();
        int damage = caster.getAttackDamage();
        int critdamage = std::lround(damage * Config::critMultiplier);

        if (target.isAlive() && attackspeed > 0) {
            if (target.isInvisible()){target.takeDamage(0);}
            else{
                for (int hit{0}; hit < attackspeed; hit++) {

                    if (target.isAlive()){
                        if (target.hasEvaded()){target.takeDamage(0);}
                        else if (caster.hasCrit()){target.takeDamage(critdamage);}
                        else{target.takeDamage(damage);}
                    }
                }
            }

        }
    }
};


namespace ManaCost {

    inline constexpr int invisibleusage{20};
    inline constexpr int burnusage{20};
    inline constexpr int poisonusage{20};
    inline constexpr int strengthenusage{30};
    inline constexpr int flurryusage{40};
    inline constexpr int chaosusage{25};
    inline constexpr int skyfallusage{50};
    inline constexpr int magmausage{50};
    inline constexpr int stunusage{25};
    inline constexpr int fearusage{20};
    inline constexpr int stonethrowusage{30};
    inline constexpr int agileusage{15};
    inline constexpr int healusage{30};
    inline constexpr int exhaustusage{30};
    inline constexpr int drownusage{40};
    inline constexpr int consumptionusage{40};
    inline constexpr int plagueusage{50};
    inline constexpr int revivalusage{60};
    inline constexpr int ruinusage{45};
    inline constexpr int vampireusage{35};
    inline constexpr int explosionusage{50};

}

#endif //PROJECT1_CONFIG_H