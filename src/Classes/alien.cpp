#include "alien.hpp"
#include "laser.hpp"

Alien::Alien(Vector2 pos, int alienType){
    this->position = pos;
    this->type = alienType;

    switch (alienType)
    {
    case 1:
        image = LoadTexture("Graphics/alien_1.png");
        break;
    case 2:
        image = LoadTexture("Graphics/alien_2.png");
        break;
    case 3:
        image = LoadTexture("Graphics/alien_3.png");
        break;
    default:
        image = LoadTexture("Graphics/alien_1.png");
        break;
    }

    speed = 2.0f;
    active = true;
}

void Alien::Draw() {
    DrawTextureV(image, position, WHITE);
        
}

