#pragma once

#include "SpriteRenderer.h"
#include "Brick.h"
#include <string>
#include <vector>

class GameLevel {
public:
    GameLevel(const std::string& path, int levelWidth, int levelHeight);
    ~GameLevel();

    void render(SpriteRenderer& renderer);
    bool isCompleted();

    std::vector<Brick>& getBricks();
private:
    std::vector<Brick> bricks;

    std::vector<std::vector<int>> loadTiles(const std::string& path);
    void initLevel(std::vector<std::vector<int>> tiles, int levelWidth, int levelHeight);
};
