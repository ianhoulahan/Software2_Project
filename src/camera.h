#pragma once

#include <raylib.h>
#include "player.h"

class GameCamera {
public:
    Camera2D camera;

    GameCamera(int screenWidth, int screenHeight) {
        camera = { 0 };
        camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
        camera.target = (Vector2){ 0, 0 };
    }

    // Follows the player's center position
    void Update(Player& player) {
        camera.target = player.GetCenter();
    }

    // Wrappers for Raylib's mode functions
    void Begin() {
        BeginMode2D(camera);
    }

    void End() {
        EndMode2D();
    }
};
