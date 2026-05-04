#pragma once

#include <raylib.h>

class Player {
public:
    Rectangle rect;
    Color color;
    float verticalVelocity;
    bool isGrounded;
    
    const float gravity = 0.15f;
    const float jumpForce = -3.0f; 
    const float groundY = 550.0f;  // The starting Y position

    Player(float x, float y) {
        rect = { x, y, 40, 40 };
        color = RED;
        verticalVelocity = 0.0f;
        isGrounded = true;
    }

    void Update() {
        // Jump input
        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            verticalVelocity = jumpForce;
            isGrounded = false;
        }

        // Apply physics
        if (!isGrounded) {
            verticalVelocity += gravity; // Gravity pulls the player down
            rect.y += verticalVelocity;
        }

        // Check for ground collision
        if (rect.y >= groundY) {
            rect.y = groundY;
            verticalVelocity = 0.0f;
            isGrounded = true;
        }
    }

    void Draw() {
        DrawRectangleRec(rect, color);
    }

    Vector2 GetCenter() {
        return (Vector2){ rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f };
    }
};
