#ifndef PROJECT1_SKILLID_H
#define PROJECT1_SKILLID_H


#include <string_view>
#include <vector>


enum class SkillId {
    // generic
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
    // special
    Exhaust = 14,
    Drown = 15,
    Consumption = 16,
    Plague = 17,
    Revival = 18,
    Ruin = 19,
    Vampire = 20,
    Explosion = 21,
};

// "no skill" marker for invalid input; it is not one of the enumerators on purpose,
// so the switches over SkillId do not have to handle it.
inline constexpr SkillId noSkill { static_cast<SkillId>(0) };

[[nodiscard]] constexpr std::string_view skillName(SkillId skill) {
    switch (skill) {
        case SkillId::Invisible:    return "Invisible";
        case SkillId::Burn:         return "Burn";
        case SkillId::Poison:       return "Poison";
        case SkillId::Strengthen:   return "Strengthen";
        case SkillId::Flurry:       return "Flurry";
        case SkillId::Chaos:        return "Chaos";
        case SkillId::Skyfall:      return "Skyfall";
        case SkillId::MagmaChamber: return "Magma Chamber";
        case SkillId::Stun:         return "Stun";
        case SkillId::Fear:         return "Fear";
        case SkillId::StoneThrow:   return "Stone Throw";
        case SkillId::Agile:        return "Agile";
        case SkillId::Heal:         return "Heal";
        case SkillId::Exhaust:      return "Exhaust";
        case SkillId::Drown:        return "Drown";
        case SkillId::Consumption:  return "Consumption";
        case SkillId::Plague:       return "Plague";
        case SkillId::Revival:      return "Revival";
        case SkillId::Ruin:         return "Ruin";
        case SkillId::Vampire:      return "Vampire";
        case SkillId::Explosion:    return "Explosion";
    }
    return "Unknown";
}

#endif //PROJECT1_SKILLID_H
