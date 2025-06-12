#include "level.hpp"
#include "alien.hpp"

Level::Level(Vector2 pos, std::vector<std::vector<int>> grid)
{
    this->position = pos;

    for (int row = 0; row < grid.size(); ++row) {
        for (int column = 0; column < grid[0].size(); ++column) {
            if (grid[row][column] != 0) {
                Vector2 alienPos = { pos.x + column * 50, pos.y + row * 50 };
                Alien alien(alienPos, grid[row][column]);
                aliens.push_back(alien);
            }
        }
    }
}

void Level::Draw() {
    for (auto& alien : aliens) {
        alien.Draw();
    }
}