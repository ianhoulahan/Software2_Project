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
    
    const float gravity = 0.70f;
    const float jumpForce = -14.0f;
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

                // BLOCK COLLISION -> Time-Rewind Logic (Continuous Collision)
                if (obs.GetType() == ObstacleType::BLOCK) {
                    
                    // Look back 1 frame to see where the player's feet used to be
                    float previousBottom = (rect.y + rect.height) - verticalVelocity;
                    float blockTop = obs.GetHitBox().y;

                    // 1. SAFE LANDING (Top Collision)
                    // If we are falling, and our feet started above (or exactly level with) the block...
                    if (verticalVelocity > 0 && previousBottom <= blockTop + 0.1f) {
                        rect.y = blockTop - rect.height; // Snap feet perfectly to the surface
                        verticalVelocity = 0.0f;
                        isGrounded = true;
                    } 
                    // 2. CEILING BONK (Bottom Collision)
                    // If moving up, and our head started below the block...
                    else if (verticalVelocity < 0 && (rect.y - verticalVelocity) >= obs.GetHitBox().y + obs.GetHitBox().height) {
                        rect.y = obs.GetHitBox().y + obs.GetHitBox().height; // Push down
                        verticalVelocity = 0.0f;
                    } 
                    // 3. WALL SMASH (Side Collision)
                    // If we didn't land on it, and we didn't bonk our head under it, we hit a wall!
                    else {
                        isDead = true;
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

    void Reset(float startX, float startY) {
        rect.x = startX;
        rect.y = startY;
        verticalVelocity = 0.0f;
        isGrounded = false; // Set to false to let gravity settle the player
        isDead = false;
    }
};
