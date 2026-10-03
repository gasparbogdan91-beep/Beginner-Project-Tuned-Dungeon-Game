# Dungeon1

A turn-based dungeon crawler written in C++23. I'm building it to learn C++ (I come from Python), so it's a work in progress and there's nothing playable yet.

## What's in it so far

- `Character` – stats (health, mana, defense, evade, crit, attack speed, etc.), damage, healing, and debuffs like poison, burn and stun.
- `MonsterTable.h` – monsters (Goblin, Serpent, Stoner, Archer, Magma, Lich) whose stats are built from the player's stats.
- `Config.h` – the numbers that tune the game, like the defense formula and skill helpers.
- `RollRNG.h` – the random number generator used for rolls.
- `Combat` – the fight logic. Only a skeleton for now.




- I'm yet  to design the combat loops and skills.
- Will power it with Raylib

