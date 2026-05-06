#pragma once

#include <raylib.h>
#include <vector>
#include "Obstacle.h"

class Player {
public:
    Rectangle rect;
    Color color;
    float verticalVelocity;
    bool isGrounded;
    
    const float gravity = 0.38f;
    const float jumpForce = -13.0f;
    bool isDead;  
    

    Player(float x, float y) {
        rect = { x, y, 60, 60 };
        color = BLUE;
        verticalVelocity = 0.0f;
        isGrounded = true;
        isDead = false;
    }

    // level's obstacles as a parameter
    void Update(const std::vector<Obstacle>& obstacles) {
        if (isDead) return; // Stop moving if dead

        // Jump input
        if (IsKeyPressed(KEY_SPACE) && isGrounded) {
            verticalVelocity = jumpForce;
            isGrounded = false;
        }

        // Apply physics (always applying gravity)
        verticalVelocity += gravity; 
        rect.y += verticalVelocity;

        // PIT DEATH (fall off bottom of screen)
        if (rect.y > 720) {
            isDead = true;
            return;
        }

        isGrounded = false;

        // COLLISION LOOP
        for (const auto& obs : obstacles) {
            if (CheckCollisionRecs(rect, obs.GetHitBox())) {
                
                if (obs.GetType() == ObstacleType::SPIKE) {
                    isDead = true; // Spike death
                    return;
                }

                if (obs.GetType() == ObstacleType::BLOCK) {
                    Rectangle overlap = GetCollisionRec(rect, obs.GetHitBox());

                    if (overlap.width > overlap.height) { // Top/Bottom collision
                        if (verticalVelocity > 0 && rect.y < obs.GetHitBox().y) {
                            rect.y = obs.GetHitBox().y - rect.height; // Landed on top
                            verticalVelocity = 0.0f;
                            isGrounded = true;
                        } else if (verticalVelocity < 0) {
                            rect.y = obs.GetHitBox().y + obs.GetHitBox().height; // Hit ceiling
                            verticalVelocity = 0.0f;
                        }
                    } else { // Side collision
                        isDead = true; // Wall death
                        return;
                    }
                }
            }
        }
    }

    void Draw() {
        DrawRectangleRec(rect, color);
    }

    Vector2 GetCenter() {
        return (Vector2){ rect.x + rect.width / 2.0f, rect.y + rect.height / 2.0f };
    }
};
