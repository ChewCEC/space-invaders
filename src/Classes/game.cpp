#include "game.hpp"

Game::Game(){}

Game::~Game(){}

void Game::Draw(){
    spaceship.Draw();
}

void Game::HandleInput(){
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        spaceship.MoveLeft();
   }else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        spaceship.MoveRight();
   } 
}
