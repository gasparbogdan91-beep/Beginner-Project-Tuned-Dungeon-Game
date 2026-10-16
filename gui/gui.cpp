
#include "gui.h"
#include <raylib.h>
#include <filesystem>
#include <iostream>
#include <climits>
#include <vector>

namespace fs = std::filesystem;


const int width = 1280;
const int height = 720;
Vector2 mousePoint;
Rectangle sourceRec;
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



class BGM {
    
public:
    float startx, endx;
    float starty, endy;
   
    bool isHovered;
    bool isPressed;

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
            StartGui();
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

void MenuGui()
{

    startButton.x = width / 2 - 100;
    startButton.y = height / 2 + 200;
    
    volume = { 0.5f };
    dragRec = { .x = 860, .y = 540, .width= 10, .height = 30 };
    sourceRec = { .x = 500, .y = startButton.y, .width = 250, .height = 70 };
    mousePoint = { 0.0f, 0.0f };

    InitWindow(width, height, "GAME");
    
    fs::path folderPath = R"(C:\Users\flows\source\repos\gasparbogdan91-beep\Beginner-Project-Tuned-Dungeon-Game\resources)";

    InitAudioDevice();
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
    while (!WindowShouldClose())
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
    CloseWindow();
}


void StartGui() {

}