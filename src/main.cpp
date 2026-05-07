#include <raylib.h>
#include <string>
#include "Level.h"
#include "player.h"
#include "camera.h"

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Geometry Dash Clone");
    SetTargetFPS(60);

    double startTime = GetTime();
    double elapsedSeconds = 0.0;

    enum GameState { MENU, PLAYING };
    GameState currentState = MENU;
    std::string selectedLevelPath = "";

    Level myLevel(6.0f, 60.0f);
    Player myPlayer(200.0f, 600.0f);
    GameCamera myGameCamera(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // --- 1. UPDATE LOGIC ---
        if (currentState == MENU) {
            bool levelSelected = false;

            if (IsKeyPressed(KEY_ONE)) { selectedLevelPath = "assets/level1.txt"; levelSelected = true; }
            else if (IsKeyPressed(KEY_TWO)) { selectedLevelPath = "assets/level2.txt"; levelSelected = true; }
            else if (IsKeyPressed(KEY_THREE)) { selectedLevelPath = "assets/level3.txt"; levelSelected = true; }

            if (levelSelected) {
                myLevel.LoadFromFile(selectedLevelPath);
                myPlayer.Reset(200.0f, 600.0f);
                startTime = GetTime();
                currentState = PLAYING;
            }
        }
        else if (currentState == PLAYING) {
            if (!myLevel.IsCompleted() && !myPlayer.isDead) {
                myLevel.Update();
                myPlayer.Update(myLevel.GetObstacles());
                myGameCamera.Update(myPlayer);
                elapsedSeconds = GetTime() - startTime;
            }

            if ((myPlayer.isDead || myLevel.IsCompleted()) && IsKeyPressed(KEY_M)) {
                currentState = MENU;
            }
        }

        // --- 2. DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (currentState == MENU) {
        	  DrawText("GEOMETRY DASH CLONE", screenWidth / 2 - 250, 150, 40, BLACK);
        	  DrawText("Press [1] for Level 1", screenWidth / 2 - 120, 300, 20, DARKGRAY);
        	  DrawText("Press [2] for Level 2", screenWidth / 2 - 120, 350, 20, DARKGRAY);
        	  DrawText("Press [3] for Level 3", screenWidth / 2 - 120, 400, 20, DARKGRAY);
        	  DrawText("Press ESC to leave", screenWidth / 2 - 120, 600, 20, DARKGRAY);
        }
        else if (currentState == PLAYING) {
            myGameCamera.Begin();
                myLevel.Draw();
                myPlayer.Draw();
            myGameCamera.End();

            DrawText(TextFormat("TIME: %.2f s", elapsedSeconds), 1100, 10, 20, DARKGRAY);

            if (myLevel.IsCompleted()) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
                DrawText("LEVEL COMPLETE!", screenWidth / 2 - 200, screenHeight / 2 - 50, 50, GREEN);
                DrawText("Press [M] for Menu", screenWidth / 2 - 100, screenHeight / 2 + 60, 20, WHITE);
            }
            else if (myPlayer.isDead) {
                DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));
                DrawText("GAME OVER", screenWidth / 2 - 150, screenHeight / 2 - 50, 50, RED);
                DrawText("Press [M] for Menu", screenWidth / 2 - 100, screenHeight / 2 + 60, 20, WHITE);
            }
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
