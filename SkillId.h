#ifndef PROJECT1_SKILLID_H
#define PROJECT1_SKILLID_H


// One id per skill. Each id doubles as a bit position in Character's known-skills mask,
// so keep values below 32.

#include <vector>

#include "Character.h"

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

namespace SkillDb{
inline std::vector<SkillId> notAcquired {
    SkillId::Invisible, SkillId::Burn, SkillId::Poison, SkillId::Strengthen,SkillId::Flurry, SkillId::Flurry,
    SkillId::Chaos, SkillId::Skyfall, SkillId::MagmaChamber, SkillId::Stun, SkillId::Fear, SkillId::StoneThrow,
    SkillId::Agile, SkillId::Heal, SkillId::Exhaust, SkillId::Drown, SkillId::Consumption, SkillId::Plague,
    SkillId::Revival, SkillId::Ruin, SkillId::Vampire, SkillId::Explosion};


inline std::vector<SkillId> acquiredSkills {
};
}
#endif //PROJECT1_SKILLID_H
