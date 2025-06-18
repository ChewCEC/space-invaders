#pragma once
#include <raylib.h>
#include <vector>
#include "laser.hpp"

class Alien {
public:
    Alien(Vector2 position, int type);
    void Draw();
    void DrawDebug();
    void ShootLaser();
    void Update(int direction);
    int GetType();
    static void UnloadImages();
    Rectangle GetRectangle();
    
    static Texture2D alienImages[4];
    Vector2 position;
    std::vector<Laser> lasers;
    int type;

private:
    Color color;
    float speed;
    bool active;

};