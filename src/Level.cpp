#include "Level.h"
#include <fstream>
#include <iostream>

// Initialize isCompleted to false when the level starts
Level::Level(float speed, float size) : scrollSpeed(speed), tileSize(size), isCompleted(false) {}

bool Level::LoadFromFile(const std::string& filepath) {
    // --- Clear obstacles ---
    obstacles.clear();
    // ---------------------------------

    // reset the completion status for the new level
    isCompleted = false;

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
            } else if (line[col] == 'F') {
                obstacles.emplace_back(x, y, tileSize, tileSize, ObstacleType::FINISH_LINE);
            }
        }
        row++;
    }
    
    return true;
}

void Level::Update() {
    for (auto& obstacle : obstacles) {
        obstacle.Update(scrollSpeed);

        // Check if the finish line has scrolled to the left side of the screen (x = 200)
        if (obstacle.GetType() == ObstacleType::FINISH_LINE && obstacle.GetHitBox().x <= 200.0f) {
            isCompleted = true;
        }
    }
}

void Level::Draw() const {
    for (const auto& obstacle : obstacles) {
        obstacle.Draw();
    }
}

const std::vector<Obstacle>& Level::GetObstacles() const { return obstacles; }
bool Level::IsCompleted() const { return isCompleted; }
