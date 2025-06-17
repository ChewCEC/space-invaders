#pragma once
#include <vector>
#include <raylib.h>
#include "laser.hpp"

class Block {
    public:
        Block(Vector2 position);
        ~Block();
        void Draw();
        void Update();
        void Kill();
        void DestroyPosition();
        std::vector<std::vector<int>> PixelsGrid;
        Rectangle GetRectangle();
        private:
        Vector2 position;
        
    };
