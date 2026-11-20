
#include "gui.h"
#include <raylib.h>
#include <filesystem>
#include <iostream>
#include <climits>
#include <vector>
#include "../src/Character.h"

namespace fs = std::filesystem;


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
        heroFrame++;

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


void DungeonGui() {

    fs::path gameSound = fs::path(REPO_ROOT) / "resources" / "dungeon.wav";


    fs::path torch = fs::path(REPO_ROOT) / "resources" / "out3" / "torch_glow.png";
    fs::path fog = fs::path(REPO_ROOT) / "resources" / "out3" / "fog_tile.png";
    fs::path layer0 = fs::path(REPO_ROOT) / "resources" / "out3" / "layer0_room.png";
    fs::path layer1 = fs::path(REPO_ROOT) / "resources" / "out3" / "layer3_foreground.png";
    dungeon = LoadSound(gameSound.string().c_str());

    Texture2D torchT = LoadTexture(torch.string().c_str());
    Texture2D fogT = LoadTexture(fog.string().c_str());
    Texture2D layer0T = LoadTexture(layer0.string().c_str());
    Texture2D layer1T = LoadTexture(layer1.string().c_str());

    Rectangle fogRec{ 0, 0, 128, 184 };
    Vector2 fogPos{ 0, 300 };
    int clockTick{ 0 };
    int clockTick2{ 0 };
   

    SetTargetFPS(60);
    while (!WindowShouldClose() && StateModifiers::g_introGui)
    {
        clockTick++;
        song.playDungeonMusic();

        BeginDrawing();
        ClearBackground(BLACK);

        
        DrawText("You enter the dungeon, freightened. The floor is damp, the walls are dark and seem to be closing. \n From afar, you hear a crackling sound. You light a torch. From the far end, you only see a shape. \n As it closes in, you raise up your weapon, and fear for the worst. Now it begins.", TypeArcherRec.x, TypeArcherRec.y, 20, WHITE);




        if (clockTick == 600) {
            StateModifiers::g_beginRoll = true;
            StateModifiers::g_introGui = false;
        }


        EndDrawing();
    }

    while (!WindowShouldClose() && StateModifiers::g_beginRoll)
    {
        clockTick2++;
       
        
        BeginDrawing();
        ClearBackground(BLACK);


        if (clockTick2 == 0) {
            DrawTexture(torchT, 300, 200, WHITE);
        }
       
        if (clockTick2 > 80 && clockTick2 < 120)
        {
            DrawTexture(layer0T, 0, 0, WHITE);
            DrawTexture(layer1T, 0, 0, WHITE);

            
        }

        if (clockTick2 > 180)
        {
            DrawTexture(layer0T, 0, 0, WHITE);
            DrawTexture(layer1T, 0, 0, WHITE);


        }

        DrawTexture(fogT, fogPos.x, fogPos.y, WHITE);
       

        EndDrawing();
    }
 
    StopSound(dungeon);
    UnloadSound(dungeon);




}