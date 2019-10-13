#include <iostream>
#include "Game.h"
#include "Constants.h"

int main(int argc, char* argv[])
{
    //Instantiate and initialise new game
    Game* game = new Game();
    game->Initialise(WINDOW_WIDTH, WINDOW_HEIGHT);
    // Game loop
    while(game->IsRunning())
    {
        game->ProcessInput();
        game->Update();
        game->Render();
    }
    // Clean up before finish
    game->Destroy();

    return 0;
}