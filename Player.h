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

public:
    Player(int hp, int maxhp, int mana, int maxmana, int defense, int skillpower, int evadechance, int hpregen, int manaregen)
        :  m_health { hp }, m_maxHealth { maxhp }, m_mana { mana }, m_maxMana { maxmana }, m_defense { defense }, m_skillPower { skillpower }, m_evadeChance { evadechance}, m_hpRegen { hpregen }, m_manaRegen { manaregen} {

        assert(m_health >= 0 && "Health is less than 0");
        assert(m_maxHealth >= 0 && "Max health is less than 0");
        assert(m_maxMana >= 0 && "Max mana is less than 0");
        assert(m_defense >= 0 && "Defense is less than 0");
        assert(m_skillPower >= 0 && "Skill power is less than 0");
        assert(m_evadeChance >= 0 && "Evade chance is less than 0");
        assert(m_hpRegen >= 0 && "HP regen is less than 0");
        assert(m_manaRegen >= 0 && "Mana regen is less than 0");

        if (m_health <= m_maxHealth) m_health = m_maxHealth;
        if (m_mana <= m_maxMana) m_mana = m_maxMana;




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

    // function declarations

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

};


#endif //INC_1_PLAYER_H