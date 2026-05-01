#include <raylib.h>
#include "Level.h"

int main() {
    // 1. Initialize the Window (1280x720)
    const int screenWidth = 1280;
    const int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Geometry Dash Clone");
    SetTargetFPS(60);

    // 2. Load the Level
    // Speed = 6.0f, TileSize = 60.0f
    // Because TileSize is 60, make sure your level1.txt is EXACTLY 12 rows tall (720 / 60 = 12)
    Level myLevel(6.0f, 60.0f); 
    myLevel.LoadFromFile("assets/level1.txt");

    // 3. Main Game Loop
    while (!WindowShouldClose()) {
        
        // --- UPDATE LOGIC ---
        myLevel.Update();

        // --- DRAWING ---
        BeginDrawing();
        ClearBackground(RAYWHITE);

        myLevel.Draw();

        // Testing text to make sure raylib compiled properly
        DrawFPS(10, 10);
        DrawText("If you see blocks scrolling left, your CMake worked!", 10, 40, 20, DARKGRAY);

        EndDrawing();
    }

    // 4. Clean Up
    CloseWindow();
    return 0;
}