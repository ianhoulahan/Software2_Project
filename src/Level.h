#pragma once

#include <vector>
#include <string>
#include "Obstacle.h"

class Level {
private:
    std::vector<Obstacle> obstacles;
    float scrollSpeed;
    float tileSize;
    bool isCompleted; // Tracks if the player beat the level

public:
    Level(float speed, float size);

    bool LoadFromFile(const std::string& filepath);

    void Update();
    void Draw() const;

    const std::vector<Obstacle>& GetObstacles() const; 
    bool IsCompleted() const; // Getter for the win state
};