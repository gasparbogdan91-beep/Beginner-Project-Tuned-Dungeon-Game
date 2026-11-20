#pragma once
#include "raylib.h" 


void MenuGui();
void GameGui();
void DungeonGui();


namespace StateModifiers {

	inline bool characterSelection_Chosen{ false };
	inline bool characterSelection_Mage{ false };
	inline bool characterSelection_Sword{ false };
	inline bool characterSelection_Archer{ false };


	inline bool g_menuState = true;
	inline bool g_chooseState = false;
	inline bool g_startGameState = false;
	inline bool g_introGui = false;
	inline bool g_beginRoll = false;


}