#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include <vector>

class Game
{
private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
public:
    Game(/* args */);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    void KillLaser();
};

