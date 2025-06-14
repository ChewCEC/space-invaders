#pragma once
#include "raylib.h"

class MisteryShip {
    // Constructor
    public:
        MisteryShip();
        ~MisteryShip();
        void Update();
        void Draw();
        void Spawn();
        bool IsActive;
    private:
        Vector2 position;
        float speed;
        Texture2D image;
};
