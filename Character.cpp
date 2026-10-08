//
// Created by bgdan on 10/1/26.
//
#include <limits>
#include <cmath>
#include <algorithm>
#include "Config.h"
#include "Character.h"

#include <iostream>
#include <ostream>

#include "RollRNG.h"
#include "SkillId.h"


//HP CHANGERS
void Character::takeDamage(int damage) {
    damage = std::clamp(damage, 0, std::numeric_limits<int>::max());
    int result = static_cast<int>(std::lround(damage * (Config::defenseK / (m_defense + Config::defenseK))));
    m_health = std::clamp(m_health - result, 0, std::numeric_limits<int>::max());
}

void Character::takeTrueDamage(int damage) {
    damage = std::clamp(damage, 0, std::numeric_limits<int>::max());
    m_health = std::clamp(m_health - damage, 0, std::numeric_limits<int>::max());
}
void Character::hpRegenIncrease(int amount) {
    int result = m_hpRegen + amount;
    m_hpRegen = std::clamp(result, 0, m_maxHealth);
}

//sets
void Character::setHpRegen(int hpregen) {
    m_hpRegen = std::clamp(hpregen,0, m_maxHealth);
}
void Character::setMaxHealth(int maxhealth) {
    m_maxHealth = std::clamp(maxhealth, 0, std::numeric_limits<int>::max());

    if (m_health> m_maxHealth) {
        m_health = m_maxHealth;
    }
    if (m_hpRegen > m_maxHealth) {
        m_hpRegen = m_maxHealth;
    }
}
void Character::setHealth(int health) {
    int result = std::clamp(health, 0, std::numeric_limits<int>::max());
    if (result < m_health){m_health = result;}else{m_health = std::clamp(health, 0, m_maxHealth);}
}




void Character::regenHealth() {
    m_health = std::clamp(m_health + m_hpRegen, 0, m_maxHealth);
}


void Character::increaseHealth(int amount) {
    if (amount <= 0) {return;}
    m_health = std::clamp(m_health + amount, m_health, m_maxHealth);
}
void Character::increaseMaxHealth(int amount) {

    m_maxHealth += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Character::increaseMaxHealthByMultiplier(float multiplier) {

        multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());

        m_maxHealth = std::lround(m_maxHealth * multiplier);
    }


//MANA CHANGERS

//sets
void Character::setMana(int mana) {
    int result = std::clamp(mana, 0, std::numeric_limits<int>::max());
    if (result < m_mana){m_mana = result;}else{m_mana = std::clamp(mana, 0, m_maxMana);}

}
void Character::setMaxMana(int maxmana) {

    m_maxMana = std::clamp(maxmana, 0, std::numeric_limits<int>::max());

    if (m_mana > m_maxMana) {
        m_mana = m_maxMana;
    }
    if (m_manaRegen > m_maxMana) {
        m_manaRegen = m_maxMana;
    }
}

void Character::setManaRegen(int manaregen) {
    m_manaRegen = std::clamp(manaregen, 0, m_maxMana);
}

void Character::manaDecrease(int amount) {
    m_mana -= std::clamp(amount, 0, m_mana);

}


void Character::regenMana() {

    m_mana = std::clamp(m_mana + m_manaRegen, 0, m_maxMana);
}

void Character::manaRegenIncrease(int amount) {
    int result = m_manaRegen + amount;
    m_manaRegen = std::clamp(result, 0, m_maxMana);
}

void Character::increaseMaxManaByMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());

    m_maxMana = std::lround(m_maxMana* multiplier);
}

void Character::increaseManaByMultiplier(float multiplier)
{
    int result = std::lround(m_mana* multiplier);
    m_mana = std::clamp(result, 0, m_maxMana);
}


//DEFENSE CHANGERS
void Character::setDefense(int defense) {
    m_defense = std::clamp(defense, 0, std::numeric_limits<int>::max());
}



void Character::defenseIncrease(int amount) {
     m_defense += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Character::defenseDecrease(int amount) {
    int result = m_defense - amount;
    m_defense = std::clamp(result, 0, std::numeric_limits<int>::max());
}


void Character::defenseDecreaseByMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 0.0f, 1.0f);

    m_defense = std::lround(m_defense * multiplier);
}

//EVADE CHANGERS
void Character::setEvadeChance(int evadechance) {
    m_evadeChance = std::clamp(evadechance, 0, 100);
}


void Character::evadeChanceIncrease(int amount) {
    int result = m_evadeChance + amount;
    m_evadeChance = std::clamp(result, 0, 100);
}



//AD AND SP

void Character::setSkillPower(int skillpower) {
    m_skillPower = std::clamp(skillpower, 0, 100);
}



void Character::skillPowerIncrease(int amount) {
    int result = m_skillPower + amount;
    m_skillPower = std::clamp(result, 0, 100);
}
void Character::skillPowerDecrease(int amount) {
    int result = m_skillPower - amount;
    m_skillPower = std::clamp(result,0, 100);
}

void Character::skillPowerIncreaseMultiplier(float multiplier) {

        multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());
        int result = std::lround(m_skillPower * multiplier);
        m_skillPower = std::clamp(result, 0, 100);
    }

//attk
void Character::setAttackDamage(int amount) {
    m_attackDamage = std::clamp(amount, 0, std::numeric_limits<int>::max());
}


void Character::attackDamageIncrease(int amount) {
    m_attackDamage += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Character::attackDamageDecrease(int amount) {
    int result = m_attackDamage - amount;
    m_attackDamage = std::clamp(result, 0, std::numeric_limits<int>::max());
}


//crit chance

void Character::increaseCritChance(int amount) {
    int result = m_critChance + amount;
    m_critChance = std::clamp(result, 0, 100);
}


void Character::decreaseCritChance(int amount) {
    int result = m_critChance - amount;
    m_critChance = std::clamp(result, 0, 100);


}

void Character::increaseCritChanceMultiplier(float multiplier) {

    multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());
    int result = std::lround(m_critChance * multiplier);
    m_critChance = std::clamp(result, 0, 100);
}


void Character::decreaseCritChanceMultiplier(float multiplier) {

    multiplier = std::clamp(multiplier, 0.0f, 1.0f);

    m_critChance = static_cast<int>(std::lround(m_critChance * multiplier));

    m_critChance = std::clamp(m_critChance, 0, 100);
}

//attack speed modifiers

void Character::increaseAttackSpeed(int hitsperturn) {

    int result = std::clamp(hitsperturn, 0, std::numeric_limits<int>::max());
    m_attackSpeed = std::clamp(m_attackSpeed + result, 0, std::numeric_limits<int>::max());
}

void Character::setAttackSpeed(int hitsperturn) {
    int result = std::clamp(hitsperturn, 0, std::numeric_limits<int>::max());
    m_attackSpeed = result;
}


//xp and level

void Character::setXp(int xp) {
    m_xp = std::clamp(xp, 0, std::numeric_limits<int>::max());
}

int Character::xpToNextLevel() const {
    double needed = Config::xpBase * std::pow(Config::xpGrowth, m_level - 1);
    return static_cast<int>(std::lround(std::min(needed, static_cast<double>(std::numeric_limits<int>::max()))));
}

void Character::addXp(int amount) {
    int result = std::clamp(amount, 0, std::numeric_limits<int>::max());
    m_xp = std::clamp(m_xp + result, 0, std::numeric_limits<int>::max());

    while (m_xp >= xpToNextLevel()) {
        m_xp -= xpToNextLevel();
        gainLevel();
    }
}

void Character::gainLevel() {
    ++m_level;
    increaseMaxHealth(Config::healthPerLevel);
    setHealth(m_health + Config::healthPerLevel);
    setMaxMana(m_maxMana + Config::manaPerLevel);
    setMana(m_mana + Config::manaPerLevel);
    defenseIncrease(Config::defensePerLevel);
}

void Character::setLevel(int level) {
    m_level = std::clamp(level, 1, std::numeric_limits<int>::max());
}

void Character::increaseLevel(int amount) {
    for (int i = 0; i < amount; ++i) {
        gainLevel();
    }
}


//TICK DECREMENT AND DEBUFF MODIFIERS


void Character::decrementTicks() {
    if (m_stunTurns > 0) { --m_stunTurns; }
    if (m_damageReducedTurns > 0) { --m_damageReducedTurns; }
    if (m_turnsInvisible > 0) { --m_turnsInvisible; }
    if (m_poisonedTurns > 0) { --m_poisonedTurns; }
    if (m_burnedTurns > 0) { --m_burnedTurns; }
    if (m_turnsExhausted > 0) { --m_turnsExhausted; }
    if (m_turnsDrowned > 0) { --m_turnsDrowned; }
}

void Character::getDamageReduced(int turns) {
    if ((m_damageReducedTurns + turns) > 5) { m_damageReducedTurns = 5; }else{m_damageReducedTurns += turns;}
}

void Character::getBurned(int turns) {
    if ((m_burnedTurns + turns) > 5) { m_burnedTurns = 5; }else{m_burnedTurns += turns;}
}

void Character::increaseTurnsInvisible(int amount)
{
    if (m_turnsInvisible + amount >= 5) { m_turnsInvisible = 5;}else{m_turnsInvisible += amount;}
}
void Character::increaseTurnsPoisoned(int amount)
{
    if (m_poisonedTurns + amount >= 5) { m_poisonedTurns = 5;}else{m_poisonedTurns += amount;}
}
void Character::increaseTurnsStun(int amount) {
    if (m_stunTurns + amount >= 5) { m_stunTurns = 5;}else{m_stunTurns += amount;}
}


void Character::increaseTurnsExhausted(int amount) {
    if (m_turnsExhausted + amount >= 5 ) { m_turnsExhausted = 5;}else{m_turnsExhausted += amount;}
}

void Character::increaseRevivalEffect(int amount) {
    if (m_revivaleffect > 0){m_revivaleffect = 1;}else{m_revivaleffect += amount;}
}

void Character::increaseTurnsDrowned(int amount) {
    if (m_turnsDrowned + amount >= 5) {m_turnsDrowned = 5;}else{m_turnsDrowned += amount;}
    }

void Character::setLifesteal(int amount) {
    m_lifesteal = std::clamp(amount, 0, 100);
}



//combat modifiers
bool Character::hasCrit() {
    int getter = getCritChance();
    int result = roll100(rng);
    return result <= getter; //if result smaller than the critchance returns bool true

}


bool Character::hasEvaded() {
    int getter = getEvadeChance();
    int result = roll100(rng);
    return result <= getter;
}




void Character::castSkill(SkillId skill, Character& caster, Character& target) {
    switch (skill) {
        case SkillId::Invisible:         Target::castInvisible(caster); break;
        case SkillId::Burn:              Target::castBurn(target); break;
        case SkillId::Strengthen:      Target::castStrengthened(caster); break;
        case SkillId::Flurry:            Target::castFlurry(target,caster); break;
        case SkillId::Stun:              Target::castStun(target); break;
        case SkillId::Fear:             Target::castFear(target); break;
        case SkillId::Poison:           Target::castPoison(target); break;
        case SkillId::Skyfall:           Target::castSkyfall(target, caster); break;
        case SkillId::Chaos:             Target::castChaos(target); break;
        case SkillId::MagmaChamber:      Target::castMagmaChamber(target, caster); break;
        case SkillId::StoneThrow:        Target::castStoneThrow(target, caster); break;
        case SkillId::Agile:            Target::castAgile(caster); break;
        case SkillId::Heal:             Target::castHeal(caster); break;



        case SkillId::Exhaust:         Target::castExhaust(target); break;
        case SkillId::Drown:           Target::castDrown(target); break;
        case SkillId::Consumption:     Target::castConsumption(caster); break;
        case SkillId::Plague:          Target::castPlague(target); break;
        case SkillId::Revival:         Target::castRevival(target); break;
        case SkillId::Ruin:            Target::castRuin(target); break;
        case SkillId::Vampire:          Target::castVampire(target, caster); break;
        case SkillId::Explosion:         Target::castExplosion(target, caster); break;

        default:   break;
    }





}

void Character::learnSkill(SkillId skill) {
    for (std::size_t i{0}; i < SkillDb::notAcquired.size(), ++i)
        if (SkillDb::notAcquired[i] == skill) {
            SkillDb::acquiredSkills.push_back(std::move(SkillDb::notAcquired[i]));
            SkillDb::notAcquired.erase(SkillDb::notAcquired.begin() + i);
        }

}

bool Character::hasAcquiredSkill(SkillId skill) const {
    for (auto i: SkillDb::acquiredSkills.size(), i++)
        if (SkillDb::acquiredSkills[i] == skill) {
            return true;
        }
    return false;

}

int Character::getSkillCost(SkillId skill) const {
    switch (skill) {
        case SkillId::Invisible:    return ManaCost::invisibleusage * m_level;
        case SkillId::Burn:         return ManaCost::burnusage * m_level;
        case SkillId::Poison:       return ManaCost::poisonusage * m_level;
        case SkillId::Strengthen:   return ManaCost::strengthenusage * m_level;
        case SkillId::Flurry:       return ManaCost::flurryusage * m_level;
        case SkillId::Chaos:        return ManaCost::chaosusage * m_level;
        case SkillId::Skyfall:      return ManaCost::skyfallusage * m_level;
        case SkillId::MagmaChamber: return ManaCost::magmausage * m_level;
        case SkillId::Stun:         return ManaCost::stunusage * m_level;
        case SkillId::Fear:         return ManaCost::fearusage * m_level;
        case SkillId::StoneThrow:   return ManaCost::stonethrowusage * m_level;
        case SkillId::Agile:        return ManaCost::agileusage * m_level;
        case SkillId::Heal:         return ManaCost::healusage * m_level;
        case SkillId::Exhaust:      return ManaCost::exhaustusage * m_level;
        case SkillId::Drown:        return ManaCost::drownusage * m_level;
        case SkillId::Consumption:  return ManaCost::consumptionusage * m_level;
        case SkillId::Plague:       return ManaCost::plagueusage * m_level;
        case SkillId::Revival:      return ManaCost::revivalusage * m_level;
        case SkillId::Ruin:         return ManaCost::ruinusage * m_level;
        case SkillId::Vampire:      return ManaCost::vampireusage * m_level;
        case SkillId::Explosion:    return ManaCost::explosionusage * m_level;
    }
    assert(false && "getSkillCost: unknown SkillId");
    return 0;
}




//will update ask choice when we have handleinput and draw. for now it returns random int 1-5
int Character::askChoice() const{
    int choice = rollchoice(rng);;
    return choice;
}

SkillId Character::displayChooseSkills() const {
    for (const auto& skill : SkillDb::acquiredSkills) {
        std::cout << static_cast<int>(skill) << std::endl;
    }
    int choice;
    std::cin >> choice;
    return static_cast<SkillId>(choice);
}







