#include "game.hpp"
#include "iostream"

Game::Game(){
    obstacles = CreateObstacles();
}

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

    for(auto& obstacle : obstacles) {
        obstacle.Draw();    

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
        } else {
            ++it; // Move to the next laser
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles() {
    int obstacleWidth = Obstacle::PixelsGrid[0].size() * 3;
    float gap = (GetScreenWidth() - (obstacleWidth * 4)) / 5.0f;

    for(int i = 0; i < 4; ++i) {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}
    