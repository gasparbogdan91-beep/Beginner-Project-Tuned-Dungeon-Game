
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
void StartGui();
int onetickcounter{ 0 };
int sixtytickcounter{ 0 };
int framecounter{ 0 };
int textcounter{ 0 };
int frameRec{ 0 };
std::vector<Color> colorVector;

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

void MenuGui()
{

    startButton.x = width / 2 - 100;
    startButton.y = height / 2 + 200;

    
    sourceRec = { .x = 500, .y = startButton.y, .width = 250, .height = 70 };
    mousePoint = { 0.0f, 0.0f };

    InitWindow(width, height, "GAME");

   

    fs::path folderPath = R"(C:\Users\flows\source\repos\gasparbogdan91-beep\Beginner-Project-Tuned-Dungeon-Game\resources)";

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

        mousePoint = GetMousePosition();
        startButton.isHovered = false;
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

    CloseWindow();
}


void StartGui() {

}