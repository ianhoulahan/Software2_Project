#include "Obstacle.h"

Obstacle::Obstacle(float x, float y, float width, float height, ObstacleType type) {
    this->hitBox = { x, y, width, height };
    this->type = type;
    
    // Assign colors based on the type of obstacle
    if (type == ObstacleType::SPIKE) {
        this->color = RED;
    } else if (type == ObstacleType::BLOCK) {
        this->color = DARKGRAY;
    } else if (type == ObstacleType::FINISH_LINE) {
        this->color = GREEN; 
    }
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
        // Draw a standard square for both blocks AND the finish line
        DrawRectangleRec(hitBox, color);
    }
}

Rectangle Obstacle::GetHitBox() const { return hitBox; }
ObstacleType Obstacle::GetType() const { return type; }