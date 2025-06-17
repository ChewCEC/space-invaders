#include "misteryship.hpp"
#include <cmath>
#include <iostream>

MisteryShip::MisteryShip()
{
    image = LoadTexture("Graphics/mystery.png");
    position = { 0, 0 };
    speed = 1.0f;
    IsActive = false;

}

MisteryShip::~MisteryShip()
{
    UnloadTexture(image);
}

void MisteryShip::Spawn()
{
    position.y = 200.0f; // Set the y-coordinate to a fixed height
    
    int side = GetRandomValue(0, 1);
    if (side == 0){
        position.x = -image.width;
        speed = 1.0f;
    } else {
        position.x = GetScreenWidth() + image.width; // Start off-screen to the right
        speed = -1.0f; 
    }
    IsActive = true;

}

void MisteryShip::Update()
{
    if (IsActive)
    {
        // Move horizontally across the screen
        position.x += speed;
        
        position.y = 150.0f + 100.0f * sinf(position.x * 3.0f / 180.0f); // Sinusoidal movement
        
        // Check if the ship has moved off-screen
        if (position.x < -image.width || position.x > GetScreenWidth() + image.width + 10)
        {
            IsActive = false; // Deactivate the ship when it goes off-screen
            std::cout << "Mistery ship deactivated" << std::endl;
        }

    }
}

void MisteryShip::Draw()
{
    if (IsActive)
    {
        DrawTexture(image, position.x, position.y, WHITE);
    }
}

Rectangle MisteryShip::GetRectangle()
{
    if (!IsActive) {
        return {position.x, position.y, 0, 0}; // Return an empty rectangle if the ship is not active
    }
    return {position.x, position.y, float(image.width), float(image.height)};
}
