#include "game.hpp"
#include "iostream"
#include "Utils/level_list.hpp"

Game::Game()
{
    backgroundMusic = LoadMusicStream("Sounds/03. Mercury.mp3");
    explosionSound = LoadSound("Sounds/explosion.wav");
    spaceshipShoot = LoadSound("Sounds/shoot.wav");
    fastinvader_1 = LoadSound("Sounds/fastinvader1.wav");
    fastinvader_2 = LoadSound("Sounds/fastinvader2.wav");
    fastinvader_3 = LoadSound("Sounds/fastinvader3.wav");
    invaderkilled = LoadSound("Sounds/invaderkilled.wav");
    mysteryShipSoundHigh = LoadSound("Sounds/ufo_highpitch.wav");
    mysteryShipSoundLow = LoadSound("Sounds/ufo_lowpitch.wav");


    SetMusicVolume(backgroundMusic, 0.5f);
    backgroundMusic.looping = true;
    PlayMusicStream(backgroundMusic);
    LoadBestScore();
    InitGame();
}


Game::~Game() {
    Alien::UnloadImages(); 
    UnloadMusicStream(backgroundMusic);
    UnloadSound(explosionSound);
    UnloadSound(spaceshipShoot);
    UnloadSound(fastinvader_1);
    UnloadSound(fastinvader_2);
    UnloadSound(fastinvader_3);
    UnloadSound(invaderkilled);
    UnloadSound(mysteryShipSoundHigh);
    UnloadSound(mysteryShipSoundLow);
}

void Game::Update()
{
    if(!run)
        GameOver();
    ;

    double currentTime = GetTime();
    if (currentTime - misteryShipSpawnTimer >= misteryShipSpawnInterval)
    {
        if(GetRandomValue(0, 1) > 0.5f){
            PlaySound(mysteryShipSoundHigh);
        }else{
            PlaySound(mysteryShipSoundLow);
        }

        misteryShip.Spawn();
        misteryShipSpawnTimer = currentTime;
        misteryShipSpawnInterval = GetRandomValue(10, 20);
    }

    for (auto &laser : spaceship.lasers)
    {
        laser.Update();
    }

    for (auto &laser: alienLasers)
    {
        laser.Update();
    }

    // Update the alien shooting timer
    alienShootTimer += GetFrameTime();
    if (alienShootTimer >= alienShootInterval)
    {
        AlienShootLaser();
        alienShootTimer = 0.0f; // Reset timer
    }

    NextLevel();
    KillLaser();
    MoveAliens();
    misteryShip.Update();
    CheckCollisions();
}

void Game::Draw()
{
    spaceship.Draw();
    misteryShip.Draw();

    for (auto &laser : spaceship.lasers)
    {
        laser.Draw();
    }

    for (auto &obstacle : obstacles)
    {
        obstacle.Draw();
    }

    for (auto &alien : aliens)
    {
        alien.DrawDebug();
    }

    for (auto &alienLaser : alienLasers)
    {
        alienLaser.Draw();
    }

    // Draw UI elements
    DrawUI();
    
    // DebugDraw();
}

void Game::DrawUI()
{
    // Display player lives
    DrawText("LIVES:", 20, 20, 20, WHITE);
    
    // Draw small spaceships to represent lives
    for (int i = 0; i < player_lives; i++) {
        DrawRectangle(100 + (i * 30), 20, 20, 20, RED);
    }
    
    // Display scores
    DrawText(TextFormat("SCORE: %d", currentScore), 20, 50, 20, WHITE);
    DrawText(TextFormat("BEST: %d", bestScore), 20, 80, 20, WHITE);
}

void Game::HandleInput()
{
    if(!run){
        return;
    }

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
        if (IsKeyPressed(KEY_SPACE))
        {   
            PlaySound(spaceshipShoot);
            spaceship.ShootLaser();
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
        if (IsKeyPressed(KEY_SPACE))
        {
            PlaySound(spaceshipShoot);
            spaceship.ShootLaser();
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
        PlaySound(spaceshipShoot);
        spaceship.ShootLaser();
    }
}

void Game::KillLaser()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();)
    {
        if (!it->active)
        {
            it = spaceship.lasers.erase(it); // Remove inactive laser
        }
        else
        {
            ++it; // Move to the next laser
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();)
    {
        if (!it->active)
        {
            it = alienLasers.erase(it); // Remove inactive laser
        }
        else
        {
            ++it; // Move to the next laser
        }
    }
}

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::PixelsGrid[0].size() * 3;
    float gap = (GetScreenWidth() - (obstacleWidth * 4)) / 5.0f;

    for (int i = 0; i < 4; ++i)
    {
        float offsetX = (i + 1) * gap + i * obstacleWidth;
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 100)}));
    }
    return obstacles;
}

std::vector<Alien> Game::CreateAliens(int level_number)
{
    std::vector<Alien> aliensVector;
    if (level_number < LEVELS.size())
    {
        const std::vector<std::vector<int>> alienGrid = *LEVELS[level_number];

        for (int row = 0; row < alienGrid.size(); ++row)
        {
            for (int column = 0; column < alienGrid[0].size(); ++column)
            {
                if (alienGrid[row][column] != 0){
                    // Calculate position regardless of whether an alien is created
                    float x = 110 + column * 2.0f * 44.0f;
                    float y = 60 + row * 1.1f * 50.0f;

                    Alien alien({x, y}, alienGrid[row][column]);
                    aliensVector.push_back(alien);
                }
            }
        }
    }
    return aliensVector;
}

void Game::MoveAliens()
{
    for (auto &alien : aliens)
    {
        if (alien.position.x + alien.alienImages[alien.type - 1].width > GetScreenWidth() - 110){
            alienDirection = -1; // Change direction to left
            MoveDownAliens(4);
        }
        if (alien.position.x < 110){
            alienDirection= 1;
            MoveDownAliens(4);
        }
        alien.Update(alienDirection); // Move aliens to the right by default
        
    }
}

void Game::MoveDownAliens(int distance)
{
    for (auto &alien : aliens)
    {
        alien.position.y += distance; // Move down by 4 pixels
    }
}

void Game::CheckCollisions()
{
    for(auto& laser: spaceship.lasers){
        auto alien_it = aliens.begin();
        while(alien_it != aliens.end()){
            if(CheckCollisionRecs(laser.GetRectangle(), alien_it->GetRectangle())){
                // Add score based on alien type
                AddScore(&*alien_it);
                PlaySound(invaderkilled);
                alien_it = aliens.erase(alien_it);
                laser.active = false; 
            }
            else{
                ++alien_it; 
            }
        }

        for(auto& obstacle: obstacles){
            auto block_it = obstacle.blocks.begin();
            while(block_it != obstacle.blocks.end()){
                if(CheckCollisionRecs(laser.GetRectangle(), block_it->GetRectangle())){
                    block_it = obstacle.blocks.erase(block_it); 
                    laser.active = false; 
                }
                else{
                    ++block_it;
                }
            }
        }

        if(CheckCollisionRecs(laser.GetRectangle(), misteryShip.GetRectangle())){
            misteryShip.IsActive = false; 
            laser.active = false;
            PlaySound(invaderkilled);            
            currentScore += 400;
        }
    }

    for(auto& alienLaser: alienLasers){
        if(CheckCollisionRecs(alienLaser.GetRectangle(), spaceship.GetRectangle())){
            player_lives--; 
            alienLaser.active = false; 

            if (player_lives == 0) {
                GameOver();
            }
        }

        for(auto& obstacle: obstacles){
            auto block_it = obstacle.blocks.begin();
            while(block_it != obstacle.blocks.end()){
                if(CheckCollisionRecs(alienLaser.GetRectangle(), block_it->GetRectangle())){
                    block_it = obstacle.blocks.erase(block_it); 
                    alienLaser.active = false; 
                }
                else{
                    ++block_it;
                }
            }
        }
    }

    // Alien colissions with obstacles
    for(auto& alien: aliens){
        for(auto& obstacle: obstacles){
            auto block_it = obstacle.blocks.begin();
            while(block_it != obstacle.blocks.end()){
                if(CheckCollisionRecs(alien.GetRectangle(), block_it->GetRectangle())){
                    block_it = obstacle.blocks.erase(block_it); // Remove the block                    
                }
                else{
                    ++block_it;
                }
            }
        }
    }
}

void Game::AlienShootLaser()
{
    // Don't shoot if there are no aliens
    if (aliens.empty() )
        return;
        
    // Get a random alien to shoot
    int randomIndex = GetRandomValue(0, aliens.size() - 1);
    
    // Make the selected alien shoot
    Alien &randomAlien = aliens[randomIndex];
    float cord_x = randomAlien.position.x + randomAlien.alienImages[randomAlien.type - 1].width / 2;
    float cord_y = randomAlien.position.y + randomAlien.alienImages[randomAlien.type - 1].height + 10;

    alienLasers.push_back(Laser({cord_x, cord_y}, -4.0f));
    
    // Optional: Add some randomness to the interval for more natural behavior
    alienShootInterval = GetRandomValue(40, 150) / 100.0f; // Random interval between 0.8 and 2.0 seconds
}


void Game::NextLevel()
{
    if (currentLevel < LEVELS.size() - 1 && aliens.empty())
    {
        aliens.clear();
        obstacles.clear();

        obstacles = CreateObstacles();

        currentLevel++;
        spaceship.Reset(); 

        // Create new aliens for the next level
        aliens = CreateAliens(currentLevel);
    }
    else if (currentLevel == LEVELS.size() - 1 && aliens.empty())
    {
        run = false;
        // Display a message indicating the game is completed
        DrawText("Congratulations! You've completed all levels!", GetScreenWidth() / 2 -
            MeasureText("Congratulations! You've completed all levels!", 20) / 2,
            GetScreenHeight() / 2 - 10, 20, RED);
    }
}

void Game::DebugDraw()
{
    // Draw debug lines with specified offsets
    // Horizontal line with Y offset of 55
    DrawLine(0, 55, GetScreenWidth(), 55, RED);

    // Vertical lines with X offset of 110
    DrawLine(110, 0, 110, GetScreenHeight(), RED);
    DrawLine(GetScreenWidth() - 110, 0, GetScreenWidth() - 110, GetScreenHeight(), RED);

    // Optional: Add labels for clarity
    DrawText("Y=55", 10, 55 - 20, 20, RED);
    DrawText("X=110", 110 + 5, 10, 20, RED);
}

void Game::InitGame()
{
    currentLevel = 0;
    obstacles = CreateObstacles();
    aliens = CreateAliens(currentLevel);
    
    run = true; 
    player_lives = 3;
    currentScore = 0;

    alienDirection = 1;
    
    // Initialize shooting timer
    alienShootTimer = 0.0f;
    alienShootInterval = 0.335f;
    misteryShipSpawnTimer = 0.0f;
    misteryShipSpawnInterval = GetRandomValue(10, 20);
}

void Game::Restart()
{
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    misteryShip.IsActive = false;
    
}

void Game::GameOver()
{
    run = false;
    
    // Update best score if current score is higher
    if (currentScore > bestScore) {
        bestScore = currentScore;
        SaveBestScore();
    }
    
    // Display game over message
    DrawText("Game Over", GetScreenWidth() / 2 - MeasureText("Game Over", 20) / 2, GetScreenHeight() / 2 - 10, 20, RED);
    DrawText("Press R to Restart", GetScreenWidth() / 2 - MeasureText("Press R to Restart", 20) / 2, GetScreenHeight() / 2 + 20, 20, RED);
    if (IsKeyPressed(KEY_R))
    {
        Restart();
        InitGame();
    }
}

void Game::SaveBestScore()
{
    // Save best score to a file
    FILE* file = fopen("highscore.dat", "wb");
    if (file) {
        fwrite(&bestScore, sizeof(int), 1, file);
        fclose(file);
    }
}

void Game::LoadBestScore()
{
    // Initialize best score to 0
    bestScore = 0;
    
    // Try to load from file
    FILE* file = fopen("highscore.dat", "rb");
    if (file) {
        fread(&bestScore, sizeof(int), 1, file);
        fclose(file);
    }
}
    
void Game::AddScore(Alien* alien_it)
{
    switch(alien_it->type) {
        case 1: currentScore += 100; break;
        case 2: currentScore += 200; break;
        case 3: currentScore += 300; break;
        default: currentScore += 100; break;
    }

}

void Game::UpdateMusic()
{
    UpdateMusicStream(backgroundMusic);
}