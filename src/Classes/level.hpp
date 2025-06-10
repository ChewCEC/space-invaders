#pragma once 
#include "raylib.h"
#include "alien.hpp"

class Level
{
public:
    Vector2 position;
    static std::vector<std::vector<int>> alienGrid;
    std::vector<Alien> aliens;

    Level(Vector2 pos, std::vector<std::vector<int>> alienGrid);

    void Draw();
};
