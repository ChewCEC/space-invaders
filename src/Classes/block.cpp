#include "block.hpp"

Block::Block(Vector2 position){
    this->position = position;

}

Block::~Block(){
}

void Block::Draw(){
    DrawRectangle(position.x, position.y, 3, 3, RED);
}

Rectangle Block::GetRectangle(){
    return {position.x, position.y, 3, 3};
}


