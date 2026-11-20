
#include "gui.h"
#include <raylib.h>
#include <filesystem>
#include <iostream>
#include <climits>
#include <vector>
#include "../src/Character.h"
#include "../src/MonsterTable.h"

namespace fs = std::filesystem;

//
const int width = 1280;
const int height = 720;
Vector2 mousePoint;
Rectangle sourceRec;
Rectangle TypeArcherRec;
Rectangle TypeMageRec;
Rectangle TypeSwordRec;
Rectangle dragRec;
Rectangle volumeRec;
void StartGui();
fs::path textLoad();
int onetickcounter{ 0 };
int sixtytickcounter{ 0 };
int framecounter{ 0 };
int textcounter{ 0 };
int frameRec{ 0 };
std::vector<Color> colorVector;
Sound bgm;
float volume{ 0.5f };
Sound game;
Sound dungeon;
Rectangle LargerMonsterGoblinRec;






fs::path textLoad() {

    if (StateModifiers::characterSelection_Archer) {
        return fs::path(REPO_ROOT) / "resources" / "archer_idle.png";
    }

    else if (StateModifiers::characterSelection_Mage) {
        return fs::path(REPO_ROOT) / "resources" / "mage_idle.png";
    }

    else {
        return fs::path(REPO_ROOT) / "resources" / "knight_idle.png";
    }

}

void skipIntro() {


    if (IsKeyPressed(KEY_SPACE)) {

        StateModifiers::g_introGui = false;
        StateModifiers::g_beginRoll = true;

    }

}
struct CharacterDraw {

    
    Texture2D character;
    Rectangle charRec;
    Rectangle largerRec;
    Vector2 charPos;

    Texture2D hpBar;
    Rectangle hpRec;
    Rectangle largerhpRec;
    Vector2 hpPos;


    Texture2D manaBar;
    Rectangle manaRec;
    Rectangle largermanaRec;
    Vector2 manaPos;

    Texture2D AS;
    Rectangle asRec;
    Rectangle smallerAsRec;
    Vector2 asPos;

    Texture2D DEF;
    Rectangle defenseRec;
    Rectangle smallerDefRec;
    Vector2 defPos;


    Texture2D SP;
    Rectangle spRec;
    Rectangle smallerSpRec;
    Vector2 spPos;

    
    Texture2D goblin;
    Texture2D serpent;
    Texture2D stoner;
    Texture2D magma;
    Texture2D lich;
    Rectangle monsterRec;
    Rectangle largerMonsterRec;
    Vector2 monsterPos;

    Texture2D mhpBar;
    Rectangle mhpRec;
    Rectangle mlargerhpRec;
    Vector2 mhpPos;


    Texture2D mmanaBar;
    Rectangle mmanaRec;
    Rectangle mlargermanaRec;
    Vector2 mmanaPos;

    Texture2D mAS;
    Rectangle masRec;
    Rectangle msmallerAsRec;
    Vector2 masPos;

    Texture2D mDEF;
    Rectangle mdefenseRec;
    Rectangle msmallerDefRec;
    Vector2 mdefPos;


    Texture2D mSP;
    Rectangle mspRec;
    Rectangle msmallerSpRec;
    Vector2 mspPos;

    
    int hp;
    int mana;
    int maxhp;
    int maxmana;
    int attackspeed;
    int defense;
    int skillpower;
    int level;
    int charFrame{ 0 };
    int mcharFrame{ 0 };
    int tickCounter{ 0 };
    int mtickCounter{ 0 };
    int xRec{ 128 };
    int barFrame{ 0 };

    int mhp;
    int mmana;
    int mmaxhp;
    int mmaxmana;
    int mattackspeed;
    int mdefense;
    int mskillpower;
    int mlevel;
    

  
    void DrawPlayer(Character& player) {

        tickCounter++;
       


        if (tickCounter == 7)
        {
   
            tickCounter = 0;
            charFrame++;

            if (charFrame == 4)
                charFrame = 0;
                charRec.x = charFrame * xRec;
                
         
        }


        DrawTexturePro(character, charRec, largerRec, { 0, 0 }, 0, WHITE);
        
        DrawTexturePro(hpBar, hpRec, largerhpRec, { 0,0 }, 0, WHITE);
        DrawText(TextFormat("%d", hp), hpPos.x + 190, hpPos.y + 10, 18, WHITE);
        DrawTexturePro(manaBar, manaRec, largermanaRec, { 0,0 }, 0, WHITE);
        DrawText(TextFormat("%d", mana), manaPos.x+ 190, manaPos.y + 10, 18, WHITE);

        DrawTexturePro(AS, asRec, smallerAsRec, { 0, 0 }, 0, WHITE);
        DrawTexturePro(DEF, defenseRec, smallerDefRec, { 0, 0 }, 0, WHITE);
        DrawTexturePro(SP, spRec, smallerSpRec, { 0, 0 }, 0, WHITE);
        DrawText(TextFormat("%d  ", attackspeed), asPos.x + 40, asPos.y + 10, 18, WHITE);
        DrawText(TextFormat("%d  ", defense), defPos.x + 40, defPos.y + 10, 18, WHITE);
        DrawText(TextFormat("%d  ", skillpower), spPos.x + 40, spPos.y + 10, 18, WHITE);
        DrawText(TextFormat("LV. %d ", level), spPos.x + 200, spPos.y - 130, 24, YELLOW);

        DrawText("YOU", manaPos.x + 90, manaPos.y - 120, 64, BLACK);
        DrawText("YOU", manaPos.x + 90, manaPos.y - 125, 64, YELLOW);
        
    }

    void UpdateBar(Character& player)  {

        

        hp = player.getHealth();
        mana = player.getMana();
        maxhp = player.getMaxHealth();
        maxmana = player.getMaxMana();
        attackspeed = player.getAttackSpeed();
        defense = player.getDefense();
        skillpower = player.getSkillPower();
        level = player.getLevel();

        int f = static_cast<int>(std::ceil(hp * 10.0f / maxhp));
        hpRec.y = std::clamp(f, 0, 10) * 24;
       
        int g = static_cast<int>(std::ceil(mana * 10.0f / maxmana));
        manaRec.y = std::clamp(g, 0, 10) * 24;

        
    }

    void DrawMonster(Character& mob, MonsterType type) {
        
        mtickCounter++;
        

        if (mtickCounter == 7)
        {

            mtickCounter = 0;
            mcharFrame++;

            if (mcharFrame == 4)
                mcharFrame = 0;
            monsterRec.x = mcharFrame * xRec;


        }

        if (type == MonsterType::Goblin) {
            DrawTexturePro(goblin, monsterRec, largerMonsterRec, { 0,0 }, 0, WHITE);
            DrawText("THE GOBLIN", mmanaPos.x - 50, mmanaPos.y - 120, 64, BLACK);
            DrawText("THE GOBLIN", mmanaPos.x - 50, mmanaPos.y - 125, 64, YELLOW);


        }

        if (type == MonsterType::Serpent) {
            DrawTexturePro(serpent, monsterRec, largerMonsterRec, { 0,0 }, 0, WHITE);
            DrawText("THE SERPENT", mmanaPos.x - 50, mmanaPos.y - 120, 64, BLACK);
            DrawText("THE SERPENT", mmanaPos.x - 50, mmanaPos.y - 125, 64, YELLOW);
        }
        if (type == MonsterType::Stoner) {
            DrawTexturePro(stoner, monsterRec, largerMonsterRec, { 0,0 }, 0, WHITE);
            DrawText("THE STONER", mmanaPos.x - 50, mmanaPos.y - 120, 64, BLACK);
            DrawText("THE STONER", mmanaPos.x - 50, mmanaPos.y - 125, 64, YELLOW);
        }
        if (type == MonsterType::Magma) {
            DrawTexturePro(magma, monsterRec, largerMonsterRec, { 0,0 }, 0, WHITE);
            DrawText("THE MAGMA", mmanaPos.x - 50, mmanaPos.y - 120, 64, BLACK);
            DrawText("THE MAGMA", mmanaPos.x - 50, mmanaPos.y - 125, 64, YELLOW);
        }
        if (type == MonsterType::Lich) {
            DrawTexturePro(lich, monsterRec, largerMonsterRec, { 0,0 }, 0, WHITE);
            DrawText("THE LICH", mmanaPos.x - 50, mmanaPos.y - 120, 64, BLACK);
            DrawText("THE LICH", mmanaPos.x - 50, mmanaPos.y - 125, 64, YELLOW);
        }

        DrawTexturePro(mhpBar, mhpRec, mlargerhpRec, { 0,0 }, 0, WHITE);
        DrawText(TextFormat("%d", mhp), mhpPos.x + 190, mhpPos.y + 10, 18, WHITE);
        DrawTexturePro(mmanaBar, mmanaRec, mlargermanaRec, { 0,0 }, 0, WHITE);
        DrawText(TextFormat("%d", mmana), mmanaPos.x + 190, mmanaPos.y + 10, 18, WHITE);

        DrawTexturePro(mAS, masRec, msmallerAsRec, { 0, 0 }, 0, WHITE);
        DrawTexturePro(mDEF, mdefenseRec, msmallerDefRec, { 0, 0 }, 0, WHITE);
        DrawTexturePro(mSP, mspRec, msmallerSpRec, { 0, 0 }, 0, WHITE);
        DrawText(TextFormat("%d  ", mattackspeed), masPos.x + 40, masPos.y + 10, 18, WHITE);
        DrawText(TextFormat("%d  ", mdefense), mdefPos.x + 40, mdefPos.y + 10, 18, WHITE);
        DrawText(TextFormat("%d  ", mskillpower), mspPos.x + 40, mspPos.y + 10, 18, WHITE);
        DrawText(TextFormat("LV. %d ", mlevel), mspPos.x - 300, mspPos.y - 130, 24, YELLOW);
    }

    void UpdateMobBar(Character& mob) {



        mhp = mob.getHealth();
        mmana = mob.getMana();
        mmaxhp = mob.getMaxHealth();
        mmaxmana = mob.getMaxMana();
        mattackspeed = mob.getAttackSpeed();
        mdefense = mob.getDefense();
        mskillpower = mob.getSkillPower();
        mlevel = mob.getLevel();
        int f = static_cast<int>(std::ceil(hp * 10.0f / maxhp));
        mhpRec.y = std::clamp(f, 0, 10) * 24;

        int g = static_cast<int>(std::ceil(mana * 10.0f / maxmana));
        mmanaRec.y = std::clamp(g, 0, 10) * 24;


    }
    };

class BGM {
    
public:
    float startx, endx;
    float starty, endy;
   
    bool isHovered;
    bool isPressed;

    void playDungeonMusic() {
        if (!IsSoundPlaying(dungeon))
        {
            PlaySound(dungeon);
        }
    }
    void playGameMusic() {
        if (!IsSoundPlaying(game))
            PlaySound(game);
    }
    void playMusic() {

        if(!IsSoundPlaying(bgm))
        PlaySound(bgm);

    }

    void ChangeVolume() {

        if (isPressed)
        {

            dragRec.x = std::clamp((int)mousePoint.x, 800, 920);
          
            
            volume = std::clamp((dragRec.x - 800) / 120.0f, 0.0f, 1.0f);
            SetSoundVolume(bgm, volume);

        }
    }

        void drawVolume() {

            DrawRectangleRec(volumeRec, BLANK);
            DrawLine(800, 560, 920, 560, MAROON);
            DrawText("VOLUME", 800, 500, 32, BLACK);
            DrawText("VOLUME", 800, 503, 32, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("VOLUME", 800, 506, 32, MAROON);

            DrawRectangleRec(dragRec, MAROON);


           

            if (isPressed) {

                DrawRectangleRec(dragRec, MAROON);
                DrawRectangleRec(volumeRec, YELLOW);
                DrawLine(800, 560, 920, 560, MAROON);
                DrawText("VOLUME", 800, 500, 32, BLACK);
                DrawText("VOLUME", 800, 503, 32, colorVector[std::clamp(textcounter, 0, 1)]);
                DrawText("VOLUME", 800, 506, 32, MAROON);
            }


        }

    

        void Update() {

            if (CheckCollisionPointRec(mousePoint, dragRec)) {

                if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

                    isPressed = true;


                }

                




                if (CheckCollisionPointRec(mousePoint, volumeRec)) {
                    isHovered = true;
                }




            }

            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                isPressed = false;
            }
        }
};



class Button {

public:
    float x, y;
    bool isPressed;
    bool isHovered{ false };

    void Draw() {

        

        DrawRectangleRec(sourceRec, BLANK);
        DrawText("PLAY", x, y, 64, BLACK);
        DrawText("PLAY", x, y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("PLAY", x, y + 7, 64, MAROON);
        if (isPressed)
        {
            StateModifiers::g_menuState = false;
            StateModifiers::g_chooseState = true;
        }

        if (isHovered)
        {
            DrawRectangleRec(sourceRec, YELLOW);
            DrawText("PLAY", x, y, 64, BLACK);
            DrawText("PLAY", x, y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("PLAY", x, y + 7, 64, WHITE);
        }

      
    }

  

    void Update() {

        if (CheckCollisionPointRec(mousePoint, sourceRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressed = true;

            }
        }

        if (CheckCollisionPointRec(mousePoint, sourceRec)) {
            isHovered = true;
        }
    

    }
    
    
};



Button startButton;
BGM song;


class CharacterButton {

public:
    float x, y;
    bool isPressedSword;
    bool isPressedMage;
    bool isPressedArcher;
    bool isHoveredArcher{ false };
    bool isHoveredMage{ false };
    bool isHoveredSword{ false };

    void DrawMage() {

        DrawRectangleRec(TypeMageRec, BLANK);
        DrawText("MAGE", TypeMageRec.x, TypeMageRec.y, 64, WHITE);
        DrawText("MAGE", TypeMageRec.x, TypeMageRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("MAGE", TypeMageRec.x, TypeMageRec.y + 6, 64, MAROON);
        if (isPressedMage)
        {
             
            StateModifiers::characterSelection_Chosen = true;

            StateModifiers::characterSelection_Mage = true;

            StateModifiers::g_chooseState = false;

            StateModifiers::g_startGameState = true;


            StateModifiers::g_introGui = true;
        }

        if (isHoveredMage)
        {
            DrawRectangleRec(TypeMageRec, YELLOW);
            DrawText("MAGE", TypeMageRec.x, TypeMageRec.y, 64, WHITE);
            DrawText("MAGE", TypeMageRec.x, TypeMageRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("MAGE", TypeMageRec.x, TypeMageRec.y + 6, 64, MAROON);
        }



    }


    void DrawArcher() {


        DrawRectangleRec(TypeArcherRec, BLANK);
        DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y, 64, WHITE);
        DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y + 6, 64, MAROON);
        if (isPressedArcher)
        {

            StateModifiers::characterSelection_Chosen = true;

            StateModifiers::characterSelection_Archer= true;

            StateModifiers::g_chooseState = false;

            StateModifiers::g_startGameState = true;

            StateModifiers::g_introGui = true;

        }

        if (isHoveredArcher)
        {
            DrawRectangleRec(TypeArcherRec, YELLOW);
            DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y, 64, WHITE);
            DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("ARCHER", TypeArcherRec.x, TypeArcherRec.y + 6, 64, MAROON);
        }
    }

    void DrawSword() {
        DrawRectangleRec(TypeSwordRec, BLANK);
        DrawText("KNIGHT",TypeSwordRec.x, TypeSwordRec.y, 64, WHITE);
        DrawText("KNIGHT", TypeSwordRec.x, TypeSwordRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("KNIGHT", TypeSwordRec.x, TypeSwordRec.y + 6, 64, MAROON);
        if (isPressedSword)
        {

            StateModifiers::characterSelection_Chosen = true;

            StateModifiers::characterSelection_Sword = true;

            StateModifiers::g_chooseState = false;

            StateModifiers::g_startGameState = true;

            StateModifiers::g_introGui = true;

            
            
        }

        if (isHoveredSword)
        {
            DrawRectangleRec(TypeSwordRec, YELLOW);
            DrawText("KNIGHT", TypeSwordRec.x, TypeSwordRec.y, 64, WHITE);
            DrawText("KNIGHT", TypeSwordRec.x, TypeSwordRec.y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("KNIGHT", TypeSwordRec.x, TypeSwordRec.y + 6, 64, MAROON);
        }
    }



    void Update() {

        if (CheckCollisionPointRec(mousePoint, TypeMageRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressedMage = true;

            }
        }

        if (CheckCollisionPointRec(mousePoint, TypeMageRec)) {
            isHoveredMage = true;
        }

        if (CheckCollisionPointRec(mousePoint, TypeArcherRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressedArcher = true;

            }
        }

        if (CheckCollisionPointRec(mousePoint, TypeArcherRec)) {
            isHoveredArcher = true;
        }

        if (CheckCollisionPointRec(mousePoint, TypeSwordRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressedSword = true;

            }
        }

        if (CheckCollisionPointRec(mousePoint, TypeSwordRec)) {
            isHoveredSword = true;
        }


    }

};

CharacterButton choice;



void MenuGui()
{

    startButton.x = width / 2 - 100;
    startButton.y = height / 2 + 200;
    
    volume = { 0.5f };
    dragRec = { .x = 860, .y = 540, .width= 10, .height = 30 };
    sourceRec = { .x = 500, .y = startButton.y, .width = 250, .height = 70 };
    mousePoint = { 0.0f, 0.0f };

    
    fs::path folderPath = R"(C:\Users\flows\source\repos\gasparbogdan91-beep\Beginner-Project-Tuned-Dungeon-Game\resources)";


    fs::path bgmPath = folderPath / "bgm.wav";
    bgm = LoadSound(bgmPath.string().c_str());
    volumeRec = { 800, 500, 140, 35 };
    song.startx = volumeRec.x - 100;
    song.endx = volumeRec.x;
    song.starty = volumeRec.y - 100;
    song.endy = volumeRec.y;

    fs::path heroPath = folderPath / "hero_idle_sheet_380.png";

    fs::path bgPath1 = folderPath / "hall_anim_0.png";
    fs::path bgPath2 = folderPath / "hall_anim_1.png";
    fs::path bgPath3 = folderPath / "hall_anim_2.png";
    fs::path bgPath4 = folderPath / "hall_anim_3.png";

 

    Texture2D bg1 = LoadTexture(bgPath1.string().c_str());
    Texture2D bg2 = LoadTexture(bgPath2.string().c_str());
    Texture2D bg3 = LoadTexture(bgPath3.string().c_str());
    Texture2D bg4 = LoadTexture(bgPath4.string().c_str());

    
    Rectangle heroRec = { 0, 0, 380, 380};
    std::vector<Texture2D> bgVector{ bg1, bg2, bg3, bg4 };
    colorVector = { GOLD, BLACK };
    Texture2D hero = LoadTexture(heroPath.string().c_str());
    Vector2 position{ 200, height / 2 + 50 };
    std::vector<int> framesPerRow{ 12, 12, 12, 12 };  
    int row{ 0 };         
    int heroFrame{ 0 };   
    int bgcount{ 0 };
    SetTargetFPS(60);
    while (!WindowShouldClose() && StateModifiers::g_menuState)
    {
        
        bgcount++;
        sixtytickcounter++;
        onetickcounter++;
        frameRec++;



        //update
        song.playMusic();
        song.ChangeVolume();
        
       
        mousePoint = GetMousePosition();
        startButton.isHovered = false;
        song.isHovered = false;
        
        BeginDrawing();

      

        ClearBackground(BLACK);

      


        if (sixtytickcounter == 30) {
            sixtytickcounter = 0;
            framecounter++;
           
            if (framecounter > 3) {
                framecounter = 0;
            }

            
        }

        if (onetickcounter == 15) {
            onetickcounter = 0;
            textcounter++;
            if (textcounter > 3) {
                textcounter = 0;
            }
        }

         
         DrawTexture(bgVector[std::clamp(framecounter, 0, 3)], 0, 0, WHITE);
         startButton.Update();
         song.Update();

         song.drawVolume();
        
        if (onetickcounter == 14) {
            heroFrame++;
            if (heroFrame >= framesPerRow[row])
                heroFrame = 0;

            heroRec.x = heroFrame * 380;
            heroRec.y = row * 380;
        }
            
        DrawTextureRec(hero, heroRec, position, WHITE);

        DrawText("A NEW CHALLENGER APPROACHES", width / 2 - 400, height / 7.1, 48, BLACK);
        DrawText("A NEW CHALLENGER APPROACHES", width / 2 - 400, height / 6.9, 48, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("A NEW CHALLENGER APPROACHES", width / 2 - 400, height / 6.8, 48, MAROON);
        startButton.Draw();
        
        EndDrawing();

       
    }

    UnloadTexture(hero);
    UnloadTexture(bg1);
    UnloadTexture(bg2);
    UnloadTexture(bg3);
    UnloadTexture(bg4);
    UnloadSound(bgm);
    
    

}


void GameGui() {

    startButton.x = width / 2 - 100;
    startButton.y = height / 2 + 200;

    TypeMageRec = { .x = 900, .y = 400, .width = 180, .height = 75 };

    TypeArcherRec = { .x = 155, .y = 400, .width = 275, .height = 75 };

    TypeSwordRec = { .x = 540, .y = 400, .width = 255, .height = 75 };

    sourceRec = { .x = 500, .y = startButton.y, .width = 250, .height = 70 };
    mousePoint = { 0.0f, 0.0f };

    volume = { 0.5f };

    fs::path gameSound = fs::path(REPO_ROOT) / "resources" / "game.wav";

    game = LoadSound(gameSound.string().c_str());

    fs::path bgGame = fs::path(REPO_ROOT) / "resources" / "background.png";
    fs::path swordIdle = fs::path(REPO_ROOT) / "resources" / "knight_idle.png";
    fs::path archerIdle = fs::path(REPO_ROOT) / "resources" / "archer_idle.png";
    fs::path mageIdle = fs::path(REPO_ROOT) / "resources" / "mage_idle.png";
    Texture2D archer = LoadTexture(archerIdle.string().c_str());
    Texture2D sword = LoadTexture(swordIdle.string().c_str());
    Texture2D mage = LoadTexture(mageIdle.string().c_str());
    Rectangle knightRec{ 0, 0, 128, 130 };
    Vector2 archerPosition{ TypeArcherRec.x , TypeArcherRec.y - 400 };
    Vector2 position{ TypeSwordRec.x, TypeSwordRec.y - 400 };
    Rectangle largerRec{ position.x, position.y, 384, 384 };
    Rectangle largerArcherRec{ archerPosition.x, archerPosition.y, 384, 384 };
    Vector2 magePosition{TypeMageRec.x, TypeMageRec.y - 400};
    Rectangle largerMageRec{ magePosition.x, magePosition.y, 384, 384 };
    Texture2D bg = LoadTexture(bgGame.string().c_str());

    int swordFrame{ 0 };
    int heroFrame{ 0 };
    SetTargetFPS(60);
    while (!WindowShouldClose() && StateModifiers::g_chooseState)
    {
        swordFrame++;
        

        song.playGameMusic();

        choice.isHoveredMage = false;
        choice.isPressedMage = false;

        choice.isHoveredArcher = false;
        choice.isPressedArcher = false;

        choice.isHoveredSword = false;
        choice.isPressedSword = false;

        song.Update();
        choice.Update();
        mousePoint = GetMousePosition();


        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexture(bg, 0, 0, WHITE);
        
        choice.DrawMage();
        
        choice.DrawArcher();

        choice.DrawSword();

        DrawRectangle(380, 95, 600, 15, BLACK);
        DrawText("It's time to choose your path.", 400, 75, 38, WHITE);
        DrawRectangle(400, 145, 520, 15, BLACK);
        DrawText("Select a character class:", 420, 120, 38, BLACK);
        DrawText("Select a character class", 420, 123, 38, WHITE);
        DrawText("Select a character class", 420, 125, 38, YELLOW);

       //
         DrawText("'The mage is a powerful spell casting class \n which heavily impacts duels, but relies on \n mana and skillpower to match the damage'", TypeMageRec.x - 20, TypeMageRec.y + 90, 14, BLACK);
         DrawText("'The mage is a powerful spell casting class \n which heavily impacts duels, but relies on \n mana and skillpower to match the damage'", TypeMageRec.x - 20 , TypeMageRec.y + 93, 14, WHITE);
         DrawText("+20 Starting SKILLPOWER\n+50 Starting MAX MANA\n-10 Starting DEFENSE", TypeMageRec.x, TypeMageRec.y + 170, 20, BLACK);
         DrawText("+20 Starting SKILLPOWER\n+50 Starting MAX MANA\n-10 Starting DEFENSE", TypeMageRec.x, TypeMageRec.y + 173, 20, WHITE);
     
         if (swordFrame == 15) {
             swordFrame = 0;
             heroFrame++;
             if (heroFrame == 4)
                 heroFrame = 0;
             knightRec.x = heroFrame * 128;
          
             
         }

         DrawRectangle(TypeArcherRec.x, TypeSwordRec.y - 163, 1000, 150, LIGHTGRAY);
         DrawRectangle(TypeArcherRec.x, TypeSwordRec.y - 159, 1000, 150, BLACK);
         DrawRectangle(TypeArcherRec.x , TypeSwordRec.y - 155, 1000, 140, DARKGRAY);
         DrawTexturePro(sword, knightRec, largerRec, { 0,0 }, 0, WHITE);
         DrawTexturePro(archer, knightRec, largerArcherRec, { 0,0 }, 0, WHITE);
         DrawTexturePro(mage, knightRec, largerMageRec, { 0,0 }, 0, WHITE);
         DrawText("'The knight shines heavier with his sword \n and shield at his side. His attacks are fierce \n and his defense is stronger than the \n other classes'", TypeSwordRec.x - 20, TypeSwordRec.y + 90, 14, BLACK);
         DrawText("'The knight shines heavier with his sword \n and shield at his side. His attacks are fierce \n and his defense is stronger than the \n other classes'", TypeSwordRec.x - 20, TypeSwordRec.y + 93, 14, WHITE);
         DrawText("+30 Starting ATTACKDAMAGE\n-10 Starting MAX MANA\n+20 Starting DEFENSE", TypeSwordRec.x, TypeSwordRec.y + 170, 20, BLACK);
         DrawText("+30 Starting ATTACKDAMAGE\n-10 Starting MAX MANA\n+20 Starting DEFENSE", TypeSwordRec.x, TypeSwordRec.y + 173, 20, WHITE);

         DrawText("'The archer and his bow are one. He's fast \n and almost uncatchable, shoots multiple arrows \n from a distance, and relies on accuracy and \n speed to win duels'", TypeArcherRec.x - 20, TypeArcherRec.y + 90, 14, BLACK);
         DrawText("'The archer and his bow are one. He's fast \n and almost uncatchable, shoots multiple arrows \n from a distance, and relies on accuracy and \n speed to win duels'", TypeArcherRec.x - 20, TypeArcherRec.y + 93, 14, WHITE);
         DrawText("+1 Starting ATTACKSPEED\n-20 Starting MAX MANA\n+25% DEFLECT CHANCE", TypeArcherRec.x, TypeArcherRec.y + 170, 20, BLACK);
         DrawText("+1 Starting ATTACKSPEED\n-20 Starting MAX MANA\n+25% DEFLECT CHANCE", TypeArcherRec.x, TypeArcherRec.y + 173, 20, WHITE);

        EndDrawing();
       

    }
    UnloadTexture(bg);
    StopSound(game);
    UnloadSound(game);




}


void DungeonGui(Character& player, Character& mob, MonsterType type) {

    fs::path gameSound = fs::path(REPO_ROOT) / "resources" / "dungeon.wav";


    fs::path goblin = fs::path(REPO_ROOT) / "resources" / "monster1_goblin.png";
    Texture2D goblinText = LoadTexture(goblin.string().c_str());
    fs::path serpent = fs::path(REPO_ROOT) / "resources" / "monster2_serpent.png";
    Texture2D serpentText = LoadTexture(serpent.string().c_str());
    fs::path stoner = fs::path(REPO_ROOT) / "resources" / "monster3_stoner.png";
    Texture2D stonerText = LoadTexture(stoner.string().c_str());
    fs::path magma = fs::path(REPO_ROOT) / "resources" / "monster4_magma.png";
    Texture2D magmaText = LoadTexture(magma.string().c_str());
    fs::path lich = fs::path(REPO_ROOT) / "resources" / "monster5_lich.png";
    Texture2D lichText = LoadTexture(lich.string().c_str());

    Vector2 monsterPos = { 800, 380 };
    Rectangle monsterRec{ 0,0, 128, 128 };
    Rectangle largerMonsterGoblinRec{ monsterPos.x - 100, monsterPos.y, 384, 384 };
    Rectangle largerMonsterRec{ monsterPos.x, monsterPos.y, 384, 384 };
    Vector2 mhpVec = { 850, 120 };
    Vector2 mmanaVec = { 850, 150 };
    Vector2 masPos{ 1115, 190 };
    Vector2 mdefVec{ 905, 190 };
    Vector2 mspVec{ 1010, 190 };
    fs::path torch = fs::path(REPO_ROOT) / "resources" / "out3" / "torch_glow.png";
    fs::path fog = fs::path(REPO_ROOT) / "resources" / "out3" / "fog_tile.png";
    fs::path layer0 = fs::path(REPO_ROOT) / "resources" / "out3" / "0.png";
    fs::path layer1 = fs::path(REPO_ROOT) / "resources" / "out3" / "layer3_foreground.png";
    dungeon = LoadSound(gameSound.string().c_str());

    Rectangle largerBG{ 0, 0, 1280, 720 };
    Rectangle bgRec{ 0, 0, 384, 216 };
    Texture2D torchT = LoadTexture(torch.string().c_str());
    Texture2D fogT = LoadTexture(fog.string().c_str());
    Texture2D layer0T = LoadTexture(layer0.string().c_str());
    Texture2D layer1T = LoadTexture(layer1.string().c_str());

    Rectangle fogRec{ 0, 0, 128, 184 };
    Vector2 fogPos{ 0, 300 };
    int clockTick{ 0 };
    int clockTick2{ 0 };



    fs::path hpPath = fs::path(REPO_ROOT) / "resources" / "hp_bar_sheet.png";
    Texture2D hpText = LoadTexture(hpPath.string().c_str());
    Rectangle hpRec = { 0, 0, 160, 24 };
    Vector2 hpVec = { 100, 120 };
    Rectangle largerHpRec = { hpVec.x, hpVec.y, 360, 44 };
    Rectangle largerMobHpRec = { mhpVec.x, mhpVec.y, 360, 44 };

    fs::path manaPath = fs::path(REPO_ROOT) / "resources" / "mana_bar_sheet.png";
    Texture2D manaText = LoadTexture(manaPath.string().c_str());
    Rectangle manaRec = { 0, 0, 160, 24 };
    Vector2 manaVec = { 100, 150 };
    Rectangle largerManaRec = { manaVec.x, manaVec.y, 360, 44 };
    Rectangle largerMobManaRec = { mmanaVec.x, mmanaVec.y, 360, 44 };
    fs::path playerText = textLoad();

    Texture2D playerTexture = LoadTexture(playerText.string().c_str());
    Rectangle playerRec = { 0, 0, 128, 128 };
    Vector2 playerVec = { 50, 210 };
    Rectangle largerRec = { playerVec.x, playerVec.y, 512, 512 };


    fs::path asPath = fs::path(REPO_ROOT) / "resources" / "attackspeed.png";
    Texture2D asText = LoadTexture(asPath.string().c_str());
    Rectangle asRec = { 0, 0, 512, 512 };
    Vector2 asVec = { 415, 190 };

    Rectangle largerAsRec = { asVec.x, asVec.y, 32, 32 };
    Rectangle largerMobAsRec = { masPos.x, masPos.y, 32, 32 };


    fs::path defPath = fs::path(REPO_ROOT) / "resources" / "shield.png";
    Texture2D defText = LoadTexture(defPath.string().c_str());
    Rectangle defRec = { 0, 0, 512, 512 };
    Vector2 defVec = { 200, 190 };
    Rectangle largerDefRec = { defVec.x, defVec.y, 32, 32 };
    Rectangle largerMobDefRec = { mdefVec.x, mdefVec.y, 32, 32 };

    fs::path spPath = fs::path(REPO_ROOT) / "resources" / "skillpower.png";
    Texture2D spText = LoadTexture(spPath.string().c_str());
    Rectangle spRec = { 0, 0, 512, 512 };
    Vector2 spVec = { 295,  190 };
    Rectangle largerSpRec = { spVec.x, spVec.y, 32, 32};
    Rectangle largerMobSpRec = { mspVec.x, mspVec.y, 32, 32 };


    CharacterDraw charDraw{ .character = playerTexture, .charRec = playerRec, .largerRec = largerRec, .charPos = playerVec, .hpBar = hpText, .hpRec = hpRec, .largerhpRec = largerHpRec, .hpPos = hpVec,
        .manaBar = manaText, .manaRec = manaRec, .largermanaRec = largerManaRec, .manaPos = manaVec, .AS = asText, .asRec = asRec, .smallerAsRec = largerAsRec, .asPos = asVec,
         .DEF = defText, .defenseRec = defRec, .smallerDefRec = largerDefRec, .defPos = defVec, .SP = spText, .spRec = spRec, .smallerSpRec = largerSpRec, .spPos = spVec, .goblin = goblinText, .serpent = serpentText,
        .stoner = stonerText, .magma = magmaText, .lich = lichText, .monsterRec = monsterRec, .largerMonsterRec = largerMonsterRec, .monsterPos = monsterPos, .mhpBar = hpText, .mhpRec = hpRec, .mlargerhpRec = largerMobHpRec,
        .mhpPos = mhpVec, .mmanaBar = manaText, .mmanaRec = manaRec, .mlargermanaRec = largerMobManaRec, .mmanaPos = mmanaVec, .mAS = asText, .masRec = asRec, .msmallerAsRec = largerMobAsRec, .masPos = masPos,
        .mDEF = defText, .mdefenseRec = defRec, .msmallerDefRec = largerMobDefRec, .mdefPos = mdefVec, .mSP = spText, .mspRec = spRec, .msmallerSpRec = largerMobSpRec, .mspPos = mspVec };

    SetTargetFPS(60);

    while (!WindowShouldClose() && StateModifiers::g_introGui)
    {
       

        clockTick++;
        song.playDungeonMusic();
        skipIntro();
        BeginDrawing();
        ClearBackground(BLACK);


        DrawText("You enter the dungeon, freightened. The floor is damp, the walls are dark and seem to be closing. \n From afar, you hear a crackling sound. You light a torch. From the far end, you only see a shape. \n As it closes in, you raise up your weapon, and fear for the worst. Now it begins.", TypeArcherRec.x, TypeArcherRec.y, 20, WHITE);

        DrawText("Press SPACEBAR to SKIP instantly", 50, 50, 18, WHITE);



        if (clockTick == 600) {
            StateModifiers::g_beginRoll = true;
            StateModifiers::g_introGui = false;
        }


        EndDrawing();
    }

    while (!WindowShouldClose() && StateModifiers::g_beginRoll)
    {
        clockTick2++;
        charDraw.UpdateMobBar(mob);
        charDraw.UpdateBar(player);

        BeginDrawing();
        ClearBackground(BLACK);


        if (clockTick2 == 0) {
            DrawTexture(torchT, 300, 200, WHITE);
            
        }

        if (clockTick2 > 80 && clockTick2 < 120)
        {
            DrawTexturePro(layer0T, bgRec, largerBG, { 0,0 }, 0, WHITE);
            DrawTexture(layer1T, 0, 0, WHITE);
            charDraw.DrawPlayer(player);

        }

        if (clockTick2 > 180)
        {
            DrawTexturePro(layer0T, bgRec, largerBG, { 0,0 }, 0, WHITE);
            DrawTexture(layer1T, 0, 0, WHITE);
            DrawRectangle(0, height - 695, 1280, 90, BLACK);
            DrawRectangle(0, height - 700, 1280, 80, RED);
            DrawRectangle(0, height - 700, 640, 80, ORANGE);

            DrawRectangle(0, height - 610, 1280, 80, Fade(GRAY, 0.3f));
            charDraw.DrawPlayer(player);
            charDraw.DrawMonster(mob, type);

        }
        
        DrawTexture(fogT, fogPos.x, fogPos.y, WHITE);
        


        EndDrawing();
    }

    StopSound(dungeon);
    UnloadSound(dungeon);


}