#include "GameLevel.h"
#include "../utils/FileManager.h"
#include "../ResourceManager.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <sstream>
#include <iostream>

GameLevel::GameLevel(const std::string& path, int levelWidth, int levelHeight) {
    std::cout << "GameLevel constructor" << std::endl;

    std::vector<std::vector<int>> tiles = this->loadTiles(path);
    this->initLevel(tiles, levelWidth, levelHeight);
}

GameLevel::~GameLevel() {
    std::cout << "GameLevel destructor" << std::endl;
}

void GameLevel::render(SpriteRenderer& renderer) {
    for (auto& brick: bricks_) {
        if (!brick->isDestroyed()) {
            brick->render(renderer);
        }
    }
}

void GameLevel::reset() {
    for (auto& brick: bricks_) {
        brick->isDestroyed(false);
    }
}

bool GameLevel::isCompleted() {
    for (auto& brick: bricks_) {
        if (!brick->isSolid() && !brick->isDestroyed()) return false;
    }

    return true;
}

std::vector<std::vector<int>> GameLevel::loadTiles(const std::string &path) {
    std::vector<std::vector<int>> tiles;

    int tile;
    std::stringstream level(FileManager::readAsText(path));
    std::string line;
    while (std::getline(level, line)) {
        std::istringstream rowStream(line);
        std::vector<int> row;
        while(rowStream >> tile) {
            row.push_back(tile);
        }
        tiles.push_back(row);
    }

    return tiles;
}

void GameLevel::initLevel(std::vector<std::vector<int>>& tiles, int levelWidth, int levelHeight) {
    float tileWidth = (float) levelWidth / (float) tiles[0].size();
    float tileHeight = (float) levelHeight / (float) tiles.size();

    for (unsigned int i = 0; i < tiles.size(); ++i) {
        for (unsigned int j = 0; j < tiles[0].size(); ++j) {
            glm::vec2 position(tileWidth * j, tileHeight * i);
            glm::vec2 size(tileWidth, tileHeight);

            switch (tiles[i][j]) {
            case 1:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.8f, 0.8f, 0.7f),
                                                          ResourceManager::Instance().texture("block_solid"),
                                                          true));
                break;
            case 2:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.2f, 0.6f, 1.0f),
                                                          ResourceManager::Instance().texture("block"),
                                                          false));
                break;
            case 3:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.0f, 0.7f, 0.0f),
                                                          ResourceManager::Instance().texture("block"),
                                                          false));
                break;
            case 4:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.8f, 0.8f, 0.4f),
                                                          ResourceManager::Instance().texture("block"),
                                                          false));
                break;
            case 5:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(1.0f, 0.5f, 0.0f),
                                                          ResourceManager::Instance().texture("block"),
                                                          false));
                break;
            default:
                break;
            }
        }
    }
}
