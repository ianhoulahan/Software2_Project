#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, float width, float height, ObstacleType type) {
    this->hitBox = { x, y, width, height };
    this->type = type;
    
    // Spikes are red, Blocks are dark gray
    this->color = (type == ObstacleType::SPIKE) ? RED : DARKGRAY;
}

void Obstacle::Update(float scrollSpeed) {
    hitBox.x -= scrollSpeed;
}

void Obstacle::Draw() const {
    if (type == ObstacleType::SPIKE) {
        // Draw a triangle for spikes
        Vector2 top = { hitBox.x + (hitBox.width / 2), hitBox.y };
        Vector2 bottomLeft = { hitBox.x, hitBox.y + hitBox.height };
        Vector2 bottomRight = { hitBox.x + hitBox.width, hitBox.y + hitBox.height };
        
        DrawTriangle(top, bottomLeft, bottomRight, color);
    } else {
        // Draw a standard square for blocks
        DrawRectangleRec(hitBox, color);
    }
}

Rectangle Obstacle::GetHitBox() const { return hitBox; }
ObstacleType Obstacle::GetType() const { return type; }