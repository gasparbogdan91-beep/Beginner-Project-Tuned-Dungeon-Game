//
// Created by bgdan on 10/1/26.
//

#ifndef INC_1_CHARACTER_H
#define INC_1_CHARACTER_H
#include <cassert>

struct CharacterStats {
    int health{100};
    int maxHealth{100};
    int mana{100};
    int maxMana{100};
    int defense{10};
    int skillPower{5};
    int evadeChance{0};
    int hpRegen{0};
    int manaRegen{0};
    int attackDamage{20};
    int critChance{0};
    int attackSpeed{1};
    int xp{0};
    int level{1};
    int lifesteal{0};

};



class Character {
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
    int m_critChance{0};
    int m_attackSpeed{1};
    int m_xp{0};
    int m_level{1};
    int m_turnsExhausted{0};
    int m_revivaleffect{0};
    void gainLevel();
    int m_turnsDrowned{0};
    int m_lifesteal{0};

public:
    explicit Character(const CharacterStats& stats)
        :  m_health { stats.health }, m_maxHealth { stats.maxHealth }, m_mana { stats.mana },
            m_maxMana { stats.maxMana }, m_defense { stats.defense}, m_skillPower { stats.skillPower },
            m_evadeChance { stats.evadeChance}, m_hpRegen { stats.hpRegen }, m_manaRegen { stats.manaRegen },
            m_attackDamage {stats.attackDamage}, m_critChance{ stats.critChance }, m_attackSpeed { stats.attackSpeed },
            m_xp { stats.xp }, m_level { stats.level }, m_lifesteal { stats.lifesteal }

    {
        assert(m_health >= 0 && "Health is less than 0");
        assert(m_maxHealth >= 0 && "Max health is less than 0");
        assert(m_maxMana >= 0 && "Max mana is less than 0");
        assert(m_defense >= 0 && "Defense is less than 0");
        assert(m_skillPower >= 0 && "Skill power is less than 0");
        assert(m_evadeChance >= 0 && "Evade chance is less than 0");
        assert(m_hpRegen >= 0 && "HP regen is less than 0");
        assert(m_manaRegen >= 0 && "Mana regen is less than 0");
        assert(m_mana >= 0 && "Mana is less than 0");
        assert(m_health <= m_maxHealth && "Health is less than maxHP");
        assert(m_mana <= m_maxMana && "Mana is less than maxMana");
        assert(m_critChance >= 0 && "Crit chance is less than 0");
        assert(m_attackSpeed >= 0 && "Attack speed is less than 0");
        assert(m_xp >= 0 && "XP is less than 0");
        assert(m_level >= 1 && "Level is less than 1");
        assert(m_revivaleffect >= 0 && "Revival effect is less than 0");
        assert(m_turnsDrowned >= 0 && "Turns drowned is less than 0");
        assert(m_lifesteal >= 0 && "Lifesteal is less than 0");
    }

    // getters
    [[nodiscard]] int getLifesteal() const { return m_lifesteal; };
    [[nodiscard]] int getCritChance() const { return m_critChance; };
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
    [[nodiscard]] int getAttackSpeed() const { return m_attackSpeed;  };
    [[nodiscard]] int getXp() const { return m_xp; };
    [[nodiscard]] int getLevel() const { return m_level; };
    [[nodiscard]] int xpToNextLevel() const ;

    //debuff checkers
    [[nodiscard]] bool hasLifesteal() const { return m_lifesteal > 0; }
    [[nodiscard]] bool hasRevival() const { return m_revivaleffect > 0;}
    [[nodiscard]] bool isBurned() const { return m_burnedTurns > 0; }
    [[nodiscard]] bool isPoisoned() const { return m_poisonedTurns > 0; }
    [[nodiscard]] bool isStunned() const { return m_stunTurns > 0; }
    [[nodiscard]] bool hasDamageReduced() const { return m_damageReducedTurns > 0; }
    [[nodiscard]] bool isAlive() const { return m_health > 0; }
    [[nodiscard]] bool isInvisible() const { return m_turnsInvisible > 0; }
    [[nodiscard]] bool isExhausted() const { return m_turnsExhausted > 0; }
    [[nodiscard]] bool isDrowned() const { return m_turnsDrowned > 0; }

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
    void getDamageReduced(int turns);
    void increaseMaxHealthByMultiplier(float multiplier);
    void increaseMaxManaByMultiplier(float multiplier);
    void increaseManaByMultiplier(float multiplier);
    void getBurned(int turns);
    void skillPowerIncreaseMultiplier(float multiplier);
    void defenseDecreaseByMultiplier(float multiplier) ;
    void increaseCritChance(int amount);
    void decreaseCritChance(int amount);
    void increaseCritChanceMultiplier(float multiplier);
    void decreaseCritChanceMultiplier(float multiplier);
    void increaseAttackSpeed(int hitsperturn);
    void setAttackSpeed(int hitsperturn);
    void setXp(int xp);
    void addXp(int amount);
    void setLevel(int level);
    void increaseLevel(int amount);
    void increaseTurnsInvisible(int amount);
    void increaseTurnsPoisoned(int amount);
    void increaseTurnsStun(int amount);
    void increaseTurnsExhausted(int amount);
    void increaseRevivalEffect(int amount);
    void increaseHealth(int amount);
    void increaseTurnsDrowned(int amount);
    void setLifesteal(int amount);
};


#endif //INC_1_CHARACTER_H