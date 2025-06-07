#pragma once
#include "block.hpp"
#include "Utils/Block_Array.hpp"
class Obstacle {
public:
    Vector2 position;
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> PixelsGrid; 

    Obstacle(Vector2 position);
    void Draw();
};

