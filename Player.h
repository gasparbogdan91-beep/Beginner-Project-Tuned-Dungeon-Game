//
// Created by bgdan on 10/1/26.
//

#ifndef INC_1_PLAYER_H
#define INC_1_PLAYER_H
#include <cassert>


class Player {
private:
    int m_health{100};
    int m_maxHealth{100};
    int m_mana{100};
    int m_maxMana{100};
    int m_defense{10};
    int m_skillPower{5};
    int m_evadeChance{0};
    int m_hpRegen{0};
    int m_manaRegen{0};
    int m_attackDamage{20};
    int m_stunTurns{0};
    int m_damageReducedTurns{0};
    int m_turnsInvisible{0};
    int m_poisonedTurns{0};
    int m_burnedTurns{0};
public:
    Player(int hp, int maxhp, int mana, int maxmana, int defense,
            int skillpower, int evadechance, int hpregen,
            int manaregen, int attackdamage, int stunturns, int damagereducedturns,
            int turnsInvisible,int poisonedturns, int burnedturns)
        :  m_health { hp }, m_maxHealth { maxhp }, m_mana { mana },
            m_maxMana { maxmana }, m_defense { defense }, m_skillPower { skillpower },
            m_evadeChance { evadechance}, m_hpRegen { hpregen }, m_manaRegen { manaregen},
            m_attackDamage {attackdamage}, m_stunTurns { stunturns }, m_damageReducedTurns{ damagereducedturns },
            m_turnsInvisible{ turnsInvisible }, m_poisonedTurns { poisonedturns }, m_burnedTurns { burnedturns } {
        assert(m_health >= 0 && "Health is less than 0");
        assert(m_maxHealth >= 0 && "Max health is less than 0");
        assert(m_maxMana >= 0 && "Max mana is less than 0");
        assert(m_defense >= 0 && "Defense is less than 0");
        assert(m_skillPower >= 0 && "Skill power is less than 0");
        assert(m_evadeChance >= 0 && "Evade chance is less than 0");
        assert(m_hpRegen >= 0 && "HP regen is less than 0");
        assert(m_manaRegen >= 0 && "Mana regen is less than 0");
        assert(m_stunTurns >= 0 && "Stun turns is less than 0");
        assert(m_damageReducedTurns >= 0 && "Damage Reduced turns is less than 0");
        assert(m_turnsInvisible >= 0 && "Turns invisible is less than 0");
        assert(m_poisonedTurns >= 0 && "Poisoned turns is less than 0");
        assert(m_burnedTurns >= 0 && "Burned turns is less than 0");




    }

    // getters

    [[nodiscard]] int getHealth() const { return m_health; };
    [[nodiscard]] int getMaxHealth() const { return m_maxHealth; };
    [[nodiscard]] int getMana() const { return m_mana; };
    [[nodiscard]] int getMaxMana() const { return m_maxMana; };
    [[nodiscard]] int getDefense() const { return m_defense; };
    [[nodiscard]] int getSkillPower() const { return m_skillPower; };
    [[nodiscard]] int getEvadeChance() const { return m_evadeChance; };
    [[nodiscard]] int getHpRegen() const { return m_hpRegen; };
    [[nodiscard]] int getManaRegen() const { return m_manaRegen; };
    [[nodiscard]] int getAttackDamage() const { return m_attackDamage; };


    //debuff checkers
    [[nodiscard]] bool isBurned() const { return m_burnedTurns > 0; }
    [[nodiscard]] bool isPoisoned() const { return m_poisonedTurns > 0; }
    [[nodiscard]] bool isStunned() const { return m_stunTurns > 0; }
    [[nodiscard]] bool hasDamageReduced() const { return m_damageReducedTurns > 0; }
    [[nodiscard]] bool isAlive() const { return m_health > 0; }
    [[nodiscard]] bool isInvisible() const { return m_turnsInvisible > 0; }


    // function declarations
    void increaseMaxHealth(int amount);
    void takeDamage(int damage);
    void setHealth(int health);
    void setMaxHealth(int maxhealth);
    void setMana(int mana);
    void setMaxMana(int maxmana);
    void setDefense(int defense);
    void setSkillPower(int skillpower);
    void setEvadeChance(int evadechance);
    void setHpRegen(int hpregen);
    void setManaRegen(int manaregen);
    void regenHealth();
    void regenMana();
    void defenseIncrease(int amount);
    void defenseDecrease(int amount);
    void skillPowerIncrease(int amount);
    void skillPowerDecrease(int amount);
    void evadeChanceIncrease(int amount);
    void hpRegenIncrease(int amount);
    void manaRegenIncrease(int amount);
    void attackDamageIncrease(int amount);
    void manaDecrease(int amount);
    void attackDamageDecrease(int amount);
    void setAttackDamage(int amount);
    void decrementTicks();
    void applyStun(int turns);
    void getDamageReduced(int turns);
    void turnInvisible(int turns);
    void increaseMaxHealthByMultiplier(float multiplier);
    void increaseMaxManaByMultiplier(float multiplier);
    void increaseManaByMultiplier(float multiplier);
    void getPoisoned(int turns);
    void getBurned(int turns);
    void skillPowerIncreaseMultiplier(float multiplier);
    void defenseDecreaseByMultiplier(float multiplier) ;
};


#endif //INC_1_PLAYER_H