#include "alien.hpp"
#include "laser.hpp"

Texture2D Alien::alienImages[4] = {};

Alien::Alien(Vector2 pos, int alienType)
{
    this->position = pos;
    this->type = alienType;
    this->active = true;
    this->speed = 0.1f;


    if (alienImages[type - 1].id == 0) // Check if the texture is loaded
    {       
        switch (alienType)
        {
        case 1:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            color = WHITE;
            break;
        case 2:
            alienImages[1]  = LoadTexture("Graphics/alien_2.png");
            color = WHITE;
            break;
        case 3:
            alienImages[2] = LoadTexture("Graphics/alien_3.png");
            color = WHITE;
            break;
        default:
            alienImages[0] = LoadTexture("Graphics/alien_1.png");
            color = WHITE;
            break;
        }
    }
}

void Alien::Draw()
{
    // Draw the alien texture
    DrawTextureV(alienImages[type - 1], position, color);

    // Draw a red box around the alien for debugging
    Color debugColor = RED;
    debugColor.a = 128; // Semi-transparent red

    // Assuming the alien image is approximately 40x40 pixels
    // Adjust these values if your alien sprites have different dimensions
    Rectangle bounds = {
        position.x,
        position.y,
        (float)alienImages[type - 1].width,
        (float)alienImages[type - 1].height};

    // Draw the debug box
    DrawRectangleLinesEx(bounds, 2.0f, debugColor);

    // Optionally, display the alien type for additional debugging
    DrawText(TextFormat("%d", type), position.x, position.y - 20, 20, RED);
}

int Alien::GetType()
{
    return type;
}

void Alien::Update(int direction)
{
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
