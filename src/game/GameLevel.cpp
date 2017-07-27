#include "GameLevel.h"
#include "../utils/FileManager.h"
#include "../ResourceManager.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <cstdlib>
#include <sstream>
#include <iostream>

GameLevel::GameLevel(const std::string& path, int levelWidth, int levelHeight) {
    auto tiles = this->loadTiles(path);
    this->initLevel(tiles, levelWidth, levelHeight);
}

GameLevel::~GameLevel() {}

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

std::vector<std::vector<int>> GameLevel::loadTiles(const std::string& path) const {
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
    auto tileWidth = static_cast<float>(levelWidth) / tiles[0].size();
    auto tileHeight = static_cast<float>(levelHeight) / tiles.size();

    for (auto i = 0; i < tiles.size(); ++i) {
        for (auto j = 0; j < tiles[0].size(); ++j) {
            glm::vec2 position(tileWidth * j, tileHeight * i);
            glm::vec2 size(tileWidth, tileHeight);

            switch (tiles[i][j]) {
            case 1:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.8f, 0.8f, 0.7f),
                    ResourceManager::Instance().texture("block_solid"), true));
                break;
            case 2:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.2f, 0.6f, 1.0f),
                    ResourceManager::Instance().texture(rand() > RAND_MAX / 2 ? "block1" : "block2"), false));
                break;
            case 3:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.0f, 0.7f, 0.0f),
                    ResourceManager::Instance().texture(rand() > RAND_MAX / 2 ? "block1" : "block2"), false));
                break;
            case 4:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(0.8f, 0.8f, 0.4f),
                    ResourceManager::Instance().texture(rand() > RAND_MAX / 2 ? "block1" : "block2"), false));
                break;
            case 5:
                bricks_.push_back(std::make_unique<Brick>(position, size, glm::vec3(1.0f, 0.5f, 0.0f),
                    ResourceManager::Instance().texture(rand() > RAND_MAX / 2 ? "block1" : "block2"), false));
                break;
            default:
                break;
            }
        }
    }
}
