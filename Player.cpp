//
// Created by bgdan on 10/1/26.
//
#include <limits>
#include <cmath>
#include <algorithm>
#include "Config.h"
#include "Player.h"



//HP CHANGERS
void Player::takeDamage(int damage) {
    damage = std::clamp(damage, 0, std::numeric_limits<int>::max());
    int result = static_cast<int>(std::lround(damage * (Config::defenseK / (m_defense + Config::defenseK))));
    m_health = std::clamp(m_health - result, 0, std::numeric_limits<int>::max());
}

void Player::hpRegenIncrease(int amount) {
    int result = m_hpRegen + amount;
    m_hpRegen = std::clamp(result, 0, m_maxHealth);
}

//sets
void Player::setHpRegen(int hpregen) {
    m_hpRegen = std::clamp(hpregen,0, m_maxHealth);
}
void Player::setMaxHealth(int maxhealth) {
    m_maxHealth = std::clamp(maxhealth, 0, std::numeric_limits<int>::max());
}
void Player::setHealth(int health) {
    int result = std::clamp(health, 0, std::numeric_limits<int>::max());
    if (result < m_health){m_health = result;}else{m_health = std::clamp(health, 0, m_maxHealth);}
}




void Player::regenHealth() {
    m_health = std::clamp(m_health + m_hpRegen, 0, m_maxHealth);
}

void Player::increaseMaxHealth(int amount) {

    m_maxHealth += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Player::increaseMaxHealthByMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());

    m_maxHealth = std::lround(m_maxHealth * multiplier);


}

//MANA CHANGERS

//sets
void Player::setMana(int mana) {
    int result = std::clamp(mana, 0, std::numeric_limits<int>::max());
    if (result < m_mana){m_mana = result;}else{m_mana = std::clamp(mana, 0, m_maxMana);}

}
void Player::setMaxMana(int maxmana) {
    m_maxMana = std::clamp(maxmana, 0, std::numeric_limits<int>::max());
}
void Player::setManaRegen(int manaregen) {
    m_manaRegen = std::clamp(manaregen, 0, m_maxMana);
}

void Player::manaDecrease(int amount) {
    m_mana -= std::clamp(amount, 0, m_mana);

}


void Player::regenMana() {

    m_mana = std::clamp(m_mana + m_manaRegen, 0, m_maxMana);
}

void Player::manaRegenIncrease(int amount) {
    int result = m_manaRegen + amount;
    m_manaRegen = std::clamp(result, 0, m_maxMana);
 }



void Player::increaseMaxManaByMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());

    m_maxMana = std::lround(m_maxMana* multiplier);
}

void Player::increaseManaByMultiplier(float multiplier)
{
    int result = std::lround(m_mana* multiplier);
    m_mana = std::clamp(result, 0, m_maxMana);
}


//DEFENSE CHANGERS
void Player::setDefense(int defense) {
    m_defense = std::clamp(defense, 0, std::numeric_limits<int>::max());
}



void Player::defenseIncrease(int amount) {
     m_defense += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Player::defenseDecrease(int amount) {
    int result = m_defense - amount;
    m_defense = std::clamp(result, 0, std::numeric_limits<int>::max());
}


void Player::defenseDecreaseByMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 0.0f, 1.0f);

    m_defense = std::lround(m_defense * multiplier);
}

//EVADE CHANGERS
void Player::setEvadeChance(int evadechance) {
    m_evadeChance = std::clamp(evadechance, 0, 100);
}


void Player::evadeChanceIncrease(int amount) {
    int result = m_evadeChance + amount;
    m_evadeChance = std::clamp(result, 0, 100);
}



//AD AND SP

void Player::setSkillPower(int skillpower) {
    m_skillPower = std::clamp(skillpower, 0, 100);
}



void Player::skillPowerIncrease(int amount) {
    int result = m_skillPower + amount;
    m_skillPower = std::clamp(result, 0, 100);
}
void Player::skillPowerDecrease(int amount) {
    int result = m_skillPower - amount;
    m_skillPower = std::clamp(result,0, 100);
}

void Player::skillPowerIncreaseMultiplier(float multiplier) {

    multiplier = std::clamp(multiplier, 1.0f, std::numeric_limits<float>::max());
    int result = std::lround(m_skillPower * multiplier);
    m_skillPower = std::clamp(result, 0, 100);
    }

//attk
void Player::setAttackDamage(int amount) {
    m_attackDamage = std::clamp(amount, 0, std::numeric_limits<int>::max());
}


void Player::attackDamageIncrease(int amount) {
    m_attackDamage += std::clamp(amount, 0, std::numeric_limits<int>::max());
}

void Player::attackDamageDecrease(int amount) {
    int result = m_attackDamage - amount;
    m_attackDamage = std::clamp(result, 0, std::numeric_limits<int>::max());
}

//TICK DECREMENT AND DEBUFF MODIFIERS


void Player::decrementTicks() {
    if (m_stunTurns > 0) { --m_stunTurns; }
    if (m_damageReducedTurns > 0) { --m_damageReducedTurns; }
    if (m_turnsInvisible > 0) { --m_turnsInvisible; }
    if (m_poisonedTurns > 0) { --m_poisonedTurns; }
    if (m_burnedTurns > 0) { --m_burnedTurns; }
}

void Player::applyStun(int turns){
    if ((m_stunTurns + turns) > 5) { m_stunTurns = 5; }else{m_stunTurns += turns;}
}
void Player::getDamageReduced(int turns) {
    if ((m_damageReducedTurns + turns) > 5) { m_damageReducedTurns = 5; }else{m_damageReducedTurns += turns;}
}

void Player::turnInvisible(int turns) {
    if ((m_turnsInvisible + turns) > 5) { m_turnsInvisible = 5; }else{m_turnsInvisible += turns;}
}

void Player::getPoisoned(int turns) {
    if ((m_poisonedTurns + turns) > 5) { m_poisonedTurns = 5; }else{m_poisonedTurns += turns;}
}

void Player::getBurned(int turns) {
    if ((m_burnedTurns + turns) > 5) { m_burnedTurns = 5; }else{m_burnedTurns += turns;}
}