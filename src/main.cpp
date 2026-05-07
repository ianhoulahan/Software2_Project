#include <raylib.h>
#include "Level.h"
#include "player.h"
#include "camera.h"

int main() {
    // Initialize Window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Geometry Dash Clone");
    SetTargetFPS(60);
    double startTime = GetTime();
    double elapsedSeconds = 0.0;

    // Load Level
    Level myLevel(6.0f, 60.0f); 
    myLevel.LoadFromFile("assets/level3.txt");

    // Load Player 
    // Starting at Y: 600 
    Player myPlayer(200.0f, 600.0f); 

    // Initialize camera
    GameCamera myGameCamera(screenWidth, screenHeight);

    // Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE LOGIC ---
        // Only keep playing if we haven't won AND we aren't dead
        if (!myLevel.IsCompleted() && !myPlayer.isDead) {
            myLevel.Update();
            
            // Pass the obstacles into the player for hit detection!
            myPlayer.Update(myLevel.GetObstacles()); 
            
            myGameCamera.Update(myPlayer);

            elapsedSeconds = GetTime() - startTime;
        }

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        myGameCamera.Begin();

        myLevel.Draw();
        myPlayer.Draw();

        myGameCamera.End();

        // Draw Timer UI
        DrawText(TextFormat("TIME: %.2f s", elapsedSeconds), 1100, 10, 20, DARKGRAY);

        // --- GAME STATE OVERLAYS ---
        if (myLevel.IsCompleted()) {
            // WIN STATE
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            DrawText("LEVEL COMPLETE!", screenWidth / 2 - 200, screenHeight / 2 - 50, 50, GREEN);
            DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, WHITE);
        } 
        else if (myPlayer.isDead) {
            // DEATH STATE
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.8f));
            DrawText("GAME OVER", screenWidth / 2 - 150, screenHeight / 2 - 50, 50, RED);
            DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, WHITE);
        } 
        else {
            // PLAYING STATE
            DrawFPS(10, 10);
            DrawText("Wait for the green finish line...", 10, 40, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // Clean Up
    CloseWindow();
    return 0;
}