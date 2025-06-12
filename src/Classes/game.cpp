#include "game.hpp"
#include "iostream"
#include "Utils/level_list.hpp"

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens(currentLevel);
    alienDirection = 1;
    
    // Initialize shooting timer
    alienShootTimer = 0.0f;
    alienShootInterval = 0.335f; // Shoot every 1 second (adjust as needed)
}

Game::~Game() {
    Alien::UnloadImages(); // Unload alien images when the game is destroyed
}

void Game::Update()
{
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

    KillLaser();
    MoveAliens();
}

void Game::Draw()
{
    spaceship.Draw();

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
        alien.Draw();
    }

    for (auto &alienLaser : alienLasers)
    {
        alienLaser.Draw();
    }

    DebugDraw();
}

void Game::HandleInput()
{
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        spaceship.MoveLeft();
        if (IsKeyPressed(KEY_SPACE))
        {
            spaceship.ShootLaser();
        }
    }
    else if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        spaceship.MoveRight();
        if (IsKeyPressed(KEY_SPACE))
        {
            spaceship.ShootLaser();
        }
    }
    else if (IsKeyPressed(KEY_SPACE))
    {
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
                // Calculate position regardless of whether an alien is created
                float x = 110 + column * 2.0f * 44.0f;
                float y = 60 + row * 1.1f * 50.0f;

                Alien alien({x, y}, alienGrid[row][column]);
                aliensVector.push_back(alien);
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

void Game::AlienShootLaser()
{
    // Don't shoot if there are no aliens
    if (aliens.empty())
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
    if (currentLevel < LEVELS.size() - 1)
    {
        currentLevel++;
        aliens = CreateAliens(currentLevel);
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