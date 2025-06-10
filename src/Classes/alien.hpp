#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Alien {
public:
    Alien(Vector2 position, int type);
    void Draw();
    void ShootLaser();
    int GetType();

    Vector2 position;
    int type;
    std::vector<Laser> lasers;
private:
    Color color;
    Texture2D image;
    float speed;
    bool active;

};