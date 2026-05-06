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
                
                // SPIKE COLLISION -> True Triangle Math
                if (obs.GetType() == ObstacleType::SPIKE) {
                    
                    Rectangle s = obs.GetHitBox();
                    
                    // 1. Define the 3 points of the Spike triangle
                    // We bring the tip down 8px and edges in 4px just to make it feel perfectly fair
                    Vector2 top = { s.x + (s.width / 2.0f), s.y + 8.0f }; 
                    Vector2 bottomLeft = { s.x + 4.0f, s.y + s.height }; 
                    Vector2 bottomRight = { s.x + s.width - 4.0f, s.y + s.height };

                    // 2. Define the points on the Player's body that might hit the spike
                    Vector2 pBottomLeft = { rect.x, rect.y + rect.height };
                    Vector2 pBottomRight = { rect.x + rect.width, rect.y + rect.height };
                    Vector2 pBottomCenter = { rect.x + (rect.width / 2.0f), rect.y + rect.height };
                    Vector2 pRightCenter = { rect.x + rect.width, rect.y + (rect.height / 2.0f) };

                    // 3. Check if any of the player's points have crossed into the triangle
                    if (CheckCollisionPointTriangle(pBottomLeft, top, bottomLeft, bottomRight) ||
                        CheckCollisionPointTriangle(pBottomRight, top, bottomLeft, bottomRight) ||
                        CheckCollisionPointTriangle(pBottomCenter, top, bottomLeft, bottomRight) ||
                        CheckCollisionPointTriangle(pRightCenter, top, bottomLeft, bottomRight)) {
                        
                        isDead = true;
                        return;
                    }
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
                    } // If the overlap is taller than it is wide, it MIGHT be a wall
                    else {
                        // THE SEAM CATCH FIX:
                        // Only die if the obstacle is actually tall enough to be a wall.
                        // 12-pixel buffer so falling fast onto floor seams is ignored.
                        if (rect.y + rect.height - 12.0f > obs.GetHitBox().y) {
                            isDead = true;
                            return;
                        }
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
