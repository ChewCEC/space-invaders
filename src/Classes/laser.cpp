#include "laser.hpp"

Laser::Laser(Vector2 position, float speed){
    this->position = position;
    this->speed = speed;
    active = true;
}

void Laser::Update() {
    position.y -= speed;
}

void Laser::Draw() {
    if (active) {
        DrawRectangleV(position, { 2, 10 }, RED);
    }

    if (position.y < 0) {
        active = false; // Deactivate laser when it goes off-screen
    }
    
}

