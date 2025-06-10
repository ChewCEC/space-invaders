#include "alien.hpp"
#include "laser.hpp"

Alien::Alien(Vector2 pos, int alienType){
    this->position = pos;
    this->type = alienType;

    switch (alienType)
    {
    case 1:
        image = LoadTexture("Graphics/alien_1.png");
        color = WHITE; 
        break;
    case 2:
        image = LoadTexture("Graphics/alien_2.png");
        color = WHITE; 
        break;
    case 3:
        image = LoadTexture("Graphics/alien_3.png");
        color = WHITE; 
        break;
    case 0:
        image = LoadTexture("Graphics/alien_1.png");
        color = { 255, 0, 0, 0 }; // Red color for type 0
        break;

    default:
        image = LoadTexture("Graphics/alien_1.png");
        color = WHITE; 
        break;
    }

    speed = 2.0f;
    active = true;
}

void Alien::Draw() {
    // Draw the alien texture
    DrawTextureV(image, position, color);
    
    // Draw a red box around the alien for debugging
    Color debugColor = RED;
    debugColor.a = 128; // Semi-transparent red
    
    // Assuming the alien image is approximately 40x40 pixels
    // Adjust these values if your alien sprites have different dimensions
    Rectangle bounds = {
        position.x,
        position.y,
        (float)image.width,
        (float)image.height
    };
    
    // Draw the debug box
    DrawRectangleLinesEx(bounds, 2.0f, debugColor);
    
    // Optionally, display the alien type for additional debugging
    DrawText(TextFormat("%d", type), position.x, position.y - 20, 20, RED);
}

int Alien::GetType() {
    return type;
}
