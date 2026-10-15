
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
std::vector<Color> colorVector;
class Button {

public:
    float x, y;
    bool isPressed;
    

    void Draw() {


        DrawRectangleRec(sourceRec, BLANK);
        DrawText("PLAY", x, y, 64, colorVector[std::clamp(textcounter, 0, 1)]);
        DrawText("PLAY", x, y + 3, 64, colorVector[std::clamp(textcounter, 0, 1)]);

        if (isPressed)
        {
            StartGui();
        }

    }

    void Update() {

        if (CheckCollisionPointRec(mousePoint, sourceRec)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                isPressed = true;
                
            }
        }
        
      
         

    }
    
    
};



Button startButton;

void MenuGui()
{

    startButton.x = width / 2 - 100;
    startButton.y = height / 2 + 200;
    

    sourceRec = { .x = (float)startButton.x, .y = startButton.y, .width = 150, .height = 60 };
    mousePoint = { 0.0f, 0.0f };

    InitWindow(width, height, "GAME");
    fs::path folderPath = R"(C:\Users\flows\source\repos\gasparbogdan91-beep\Beginner-Project-Tuned-Dungeon-Game\resources)";

    fs::path heroPath = folderPath / "hero_walk_sheet.png";

    fs::path bgPath1 = folderPath / "dungeon_anim_0.png";
    fs::path bgPath2 = folderPath / "dungeon_anim_1.png";
    fs::path bgPath3 = folderPath / "dungeon_anim_2.png";
    fs::path bgPath4 = folderPath / "dungeon_anim_3.png";

    Texture2D bg1 = LoadTexture(bgPath1.string().c_str());
    Texture2D bg2 = LoadTexture(bgPath2.string().c_str());
    Texture2D bg3 = LoadTexture(bgPath3.string().c_str());
    Texture2D bg4 = LoadTexture(bgPath4.string().c_str());

    

    std::vector<Texture2D> bgVector{ bg1, bg2, bg3, bg4 };
    colorVector = { WHITE, BLACK };
    Texture2D hero = LoadTexture(heroPath.string().c_str());





    SetTargetFPS(60);
    while (!WindowShouldClose())
    {

        sixtytickcounter++;
        onetickcounter++;




            //update

            mousePoint = GetMousePosition();

            BeginDrawing();

            ClearBackground(BLACK);

            if (sixtytickcounter == 15) {
                sixtytickcounter = 0;
                framecounter++;
                if (framecounter > 3) {
                    framecounter = 0;
                     }
            }

            if (onetickcounter == 30) {
                onetickcounter = 0;
                textcounter++;
                if (textcounter > 3) {
                    textcounter = 0;
                }
            }

   
            
            DrawTexture(bgVector[framecounter], 0, 0, WHITE);
            startButton.Update();


            DrawText("WELCOME TO DUNGEON ARENA", width / 2 - 500, height / 7.1, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("WELCOME TO DUNGEON ARENA", width / 2 - 500, height / 7, 64, colorVector[std::clamp(textcounter, 0, 1)]);
            DrawText("WELCOME TO DUNGEON ARENA", width / 2 - 500, height / 6.9, 64, colorVector[std::clamp(textcounter, 0, 1)]);
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