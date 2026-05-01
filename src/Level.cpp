#include "Level.h"
#include <fstream>
#include <iostream>

Level::Level(float speed, float size) : scrollSpeed(speed), tileSize(size) {}

bool Level::LoadFromFile(const std::string& filepath) {
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "ERROR: Failed to load level file at: " << filepath << std::endl;
        return false;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        for (size_t col = 0; col < line.length(); ++col) {
            float x = col * tileSize;
            float y = row * tileSize;

            if (line[col] == 'B') {
                obstacles.emplace_back(x, y, tileSize, tileSize, ObstacleType::BLOCK);
            } else if (line[col] == 'S') {
                obstacles.emplace_back(x, y, tileSize, tileSize, ObstacleType::SPIKE);
            }
        }
        row++;
    }
    
    return true;
}

void Level::Update() {
    for (auto& obstacle : obstacles) {
        obstacle.Update(scrollSpeed);
    }
}

void Level::Draw() const {
    for (const auto& obstacle : obstacles) {
        obstacle.Draw();
    }
}

const std::vector<Obstacle>& Level::GetObstacles() const {
    return obstacles;
}