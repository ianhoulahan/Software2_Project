#include <raylib.h>
#include "Level.h"

int main() {
    // Initialize Window
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Geometry Dash Clone");
    SetTargetFPS(60);

    // Load Level
    Level myLevel(6.0f, 60.0f); 
    myLevel.LoadFromFile("assets/level1.txt");

    // Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE LOGIC ---
        // Only keep scrolling the level if the player hasn't won yet
        if (!myLevel.IsCompleted()) {
            myLevel.Update();
        }

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        myLevel.Draw();

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