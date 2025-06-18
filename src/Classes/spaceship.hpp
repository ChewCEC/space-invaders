#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void ShootLaser();
        Rectangle GetRectangle();
        std::vector<Laser> lasers;
        void Reset();
    private:
        Texture2D image;
        Vector2 position;

};
