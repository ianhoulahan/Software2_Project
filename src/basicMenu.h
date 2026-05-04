#pragma once
#include <raylib.h>

enum class GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING };

class GameMenu {
public:
    // Constructor
    GameMenu(int width, int height, const char* title);
    
    // Destructor
    ~GameMenu();

    // The main entry point for the screen logic
    void Run();

private:
    // Methods
    void Update();
    void Draw();

    // Variables
    int screenWidth;
    int screenHeight;
    GameScreen currentScreen;
    int framesCounter;
};