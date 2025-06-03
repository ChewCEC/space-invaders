#pragma once
#include "spaceship.hpp"

class Game
{
private:
    Spaceship spaceship;
public:
    Game(/* args */);
    ~Game();
    void Draw();
    void Update();
    void HandleInput();
    void KillLaser();
};

