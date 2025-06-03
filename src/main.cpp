#include <raylib.h>
#include "Classes/game.hpp"

int main() 
{
    Color grey = {29, 29, 27, 255};
    int windowWidth = 1280;
    int windowHeight = 720;
    
    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(144); //framerate

    Game game;

    while(WindowShouldClose() == false){
        
        game.HandleInput();
        BeginDrawing();
        ClearBackground(grey);
        game.Draw(); 

        EndDrawing();
        
    }
}