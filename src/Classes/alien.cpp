#include "alien.hpp"
#include "laser.hpp"

Texture2D Alien::alienImages[4] = {};

Alien::Alien(Vector2 pos, int alienType)
{
    this->position = pos;
    this->type = alienType;
    this->active = true;
    this->speed = 0.1f;

    switch (alienType)
    {
    case 1:
        if (alienImages[0].id == 0) 
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            color = WHITE;
        break;
    case 2:
        if (alienImages[1].id == 0)
            alienImages[1] = LoadTexture("Graphics/alien_2.png");
            color = WHITE;
        break;
    case 3:
        if (alienImages[2].id == 0)
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            color = WHITE;
        break;
    default:
        if (alienImages[0].id == 0)
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            color = WHITE;
            
        break;
    }
}


void Alien::Draw()
{
    DrawTextureV(alienImages[type - 1], position, color);
}

void Alien::DrawDebug()
{
    DrawTextureV(alienImages[type - 1], position, color);

    Color debugColor = RED;
    debugColor.a = 128; 

    Rectangle bounds = {
        position.x,
        position.y,
        (float)alienImages[type - 1].width,
        (float)alienImages[type - 1].height};

    DrawRectangleLinesEx(bounds, 2.0f, debugColor);

    DrawText(TextFormat("%d", type), position.x, position.y - 20, 20, RED);
}

int Alien::GetType()
{
    return type;
}

void Alien::Update(int direction)
{
    if (!active)
        return;
    position.x += speed * direction;
}

void Alien::UnloadImages()
{
    for(int i = 0; i < 4; i++){
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::GetRectangle()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}
