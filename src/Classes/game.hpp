#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include <vector>
#include "level.hpp"
#include "alien.hpp"
#include "laser.hpp"

class Game
{
    private:
        Spaceship spaceship;
        std::vector<Obstacle> obstacles;
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> aliens;
        std::vector<Alien> CreateAliens(int level);
        std::vector<Laser> alienLasers;
        int currentLevel = 0;
        void MoveAliens();
        int alienDirection; 
        void MoveDownAliens(int distance);

        // Add timer variables for alien shooting
        float alienShootTimer;
        float alienShootInterval;

        void DebugDraw();

    public:
        Game(/* args */);
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        void KillLaser();
        void NextLevel();
        void AlienShootLaser();
                        
};

