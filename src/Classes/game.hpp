#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include <vector>
#include "level.hpp"
#include "alien.hpp"
#include "laser.hpp"
#include "misteryship.hpp"

class Game
{
    private:
        Spaceship spaceship;
        MisteryShip misteryShip;
        std::vector<Obstacle> obstacles;
        std::vector<Obstacle> CreateObstacles();
        std::vector<Alien> aliens;
        std::vector<Alien> CreateAliens(int level);
        std::vector<Laser> alienLasers;
        int currentLevel = 0;
        void MoveAliens();
        int alienDirection; 
        void MoveDownAliens(int distance);

        void CheckCollisions();
        
        // Add timer variables for alien shooting
        float alienShootTimer;
        float alienShootInterval;
        void DebugDraw();

        float misteryShipSpawnTimer;
        float misteryShipSpawnInterval;

    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        void KillLaser();
        void NextLevel();
        void AlienShootLaser();

};

