#include <iostream>

#include "Character.h"
#include "Combat.h"
#include "gui.h"
#include <raylib.h>
#include <filesystem>
#include "MonsterTable.h"



int main() {


    InitWindow(1280, 720, "GAME");
    InitAudioDevice();

    Character player{ CharacterStats{} };
    

    while (!WindowShouldClose() && StateModifiers::g_menuState) {
        MenuGui();
    }
    while (!WindowShouldClose() && StateModifiers::g_chooseState)
    {
        GameGui();

    }
    while (!WindowShouldClose() && StateModifiers::g_startGameState)
    {
        
        player.setType();
        player.setStartAttributes(player);
        MonsterType type = rollMonster();
        Character monster{ stats(type, player) };
       
        DungeonGui(player, monster, type);

    }

    CloseWindow();
    return 0;
}
