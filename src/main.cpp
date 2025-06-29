#include <raylib.h>
#include "Classes/game.hpp"
#include "Classes/spaceship.hpp"
#include "Classes/alien.hpp"

int main() 
{
    Color grey = {29, 29, 27, 255};
    int windowWidth = 1280;
    int windowHeight = 720;
    
    InitWindow(windowWidth, windowHeight, "Space Invaders");
    InitAudioDevice();

    SetTargetFPS(144); //framerate
    Game game;

    while(WindowShouldClose() == false){
        game.UpdateMusic();
        game.HandleInput();
        BeginDrawing();
        ClearBackground(grey);
       
        game.Draw(); 
        game.Update();
        
        EndDrawing();
        
    }

    CloseWindow();
    CloseAudioDevice();
    return 0;
}