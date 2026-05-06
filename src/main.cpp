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
    myLevel.LoadFromFile("assets/level1.txt");

    //Load Player (Position x:100, y: groundY)
    Player myPlayer(100.0f, 580.0f);

    //Initialize camera
    GameCamera myGameCamera(screenWidth, screenHeight);

    // Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE LOGIC ---
        // Only keep scrolling the level if the player hasn't won yet
        if (!myLevel.IsCompleted()) {
            myLevel.Update();
            myPlayer.Update();
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

        DrawText(TextFormat("TIME: %.2f s",elapsedSeconds),1100,10,20,DARKGRAY);

        // Check the win state to draw the UI overlay
        if (myLevel.IsCompleted()) {
            // Draw a semi-transparent black box over the whole screen
            DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.5f));
            
            // Draw the Win Text
            DrawText("LEVEL COMPLETE!", screenWidth / 2 - 200, screenHeight / 2 - 50, 50, GREEN);
            DrawText("Press ESC to exit", screenWidth / 2 - 100, screenHeight / 2 + 20, 20, WHITE);
        } else {
            // Draw standard UI while playing
            DrawFPS(10, 10);
            DrawText("Wait for the green finish line...", 10, 40, 20, DARKGRAY);
        }

        EndDrawing();
    }

    // Clean Up
    CloseWindow();
    return 0;
}
