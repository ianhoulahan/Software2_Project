#pragma once

#include <vector>
#include <string>
#include "Obstacle.h"

class Level {
private:
    std::vector<Obstacle> obstacles;
    float scrollSpeed;
    float tileSize;

public:
    Level(float speed, float size);

    bool LoadFromFile(const std::string& filepath);

    void Update();
    void Draw() const;

    const std::vector<Obstacle>& GetObstacles() const; 
};