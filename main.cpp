#include "SnakeGame.h"
#include <ctime>
#include <random>

int main()
{
    srand( time(0) );
    SnakeGame game;
    while(!game.getGameOver())
    {
        game.draw();
        game.input();
        game.logic();
    }
    return 0;
}
