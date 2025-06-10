#include "level.hpp"
#include "alien.hpp"

Level::Level(Vector2 pos, std::vector<std::vector<int>> alienGrid)
{
    this->position = pos;

    for (int row = 0; row < alienGrid.size(); ++row) {
        for (int column = 0; column < alienGrid[0].size(); ++column) {
            if (alienGrid[row][column] != 0) {
                Vector2 alienPos = { pos.x + column * 50, pos.y + row * 50 };
                Alien alien(alienPos, alienGrid[row][column]);
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