#include "game.hpp"
#include "iostream"
Game::Game(){}

Game::~Game(){}

void Game::Update(){
    for(auto& laser : spaceship.lasers) {
        laser.Update();
    }
    KillLaser(); 
}

void Game::Draw(){
    spaceship.Draw();

    for(auto& laser : spaceship.lasers) {
        laser.Draw();
    }
}

void Game::HandleInput(){
    if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        spaceship.MoveLeft();
        if(IsKeyPressed(KEY_SPACE)){
            spaceship.ShootLaser();
    } 
    }else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        spaceship.MoveRight();
        if(IsKeyPressed(KEY_SPACE)){
            spaceship.ShootLaser();
    } 
    }else if(IsKeyPressed(KEY_SPACE)){
        spaceship.ShootLaser();
    } 
}

void Game::KillLaser() {
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
    if (!it->active) {
        it = spaceship.lasers.erase(it); // Remove inactive laser
        std::cout << "Laser removed" << std::endl;
    } else {
        ++it; // Move to the next laser
    }
}
}
