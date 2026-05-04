#pragma once

#include <raylib.h>

enum class ObstacleType {
    BLOCK,
    SPIKE,
    FINISH_LINE 
};

class Obstacle {
private:
    Rectangle hitBox;
    ObstacleType type;
    Color color;

public:
    Obstacle(float x, float y, float width, float height, ObstacleType type);

    void Update(float scrollSpeed);
    void Draw() const;

    Rectangle GetHitBox() const;
    ObstacleType GetType() const;
};