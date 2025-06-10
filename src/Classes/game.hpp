#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include <vector>
#include "level.hpp"
#include "alien.hpp"

class Game
{
private:
    Spaceship spaceship;
    std::vector<Obstacle> obstacles;
    std::vector<Obstacle> CreateObstacles();
    std::vector<Alien> aliens;
    std::vector<Alien> CreateAliens(int level);
    int currentLevel = 0;
public:
    Game(/* args */);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    void KillLaser();
    void NextLevel();
};

