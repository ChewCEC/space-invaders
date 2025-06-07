#include "obstacle.hpp"

// Define the static member
std::vector<std::vector<int>> Obstacle::PixelsGrid = grid;

Obstacle::Obstacle(Vector2 pos)
{
    this->position = pos;

    for (int row = 0; row < grid.size(); ++row){
        for (int column = 0; column < grid[0].size(); ++column){
            if (grid[row][column] == 1){
                float pos_x = pos.x + column*3;
                float pos_y = pos.y + row*3;
                Block block = Block({pos_x, pos_y});
                blocks.push_back(block);

            }
        }
    }
}

void Obstacle::Draw(){
    for(auto& block:blocks){
        block.Draw();
    }
}



