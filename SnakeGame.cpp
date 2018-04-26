#include "SnakeGame.h"

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

using namespace std;



SnakeGame::SnakeGame() :
    dir(STOP),
    gameOver(false),
    width(40),
    height(20),
    x(width / 2 - 1),
    y(height / 2 - 1),
    fruitX(rand() % width),
    fruitY(rand() % height),
    score(0),
    nTail(0)
{
}


int SnakeGame::kbhit()
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

bool SnakeGame::getGameOver() const
{
    return gameOver;
}

void SnakeGame::draw()
{
    system("clear");
    for(int i = 0; i < width + 1; ++i)
        cout << "#";
    cout << endl;

    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {

            if(j == 0 || j == width - 1)
                cout << "#";

            if(i == y && j == x)
            {

                cout << "0";
            }

            else if(i == fruitY && j == fruitX)
            {

                cout << "F";
            }
            else
            {
                bool print = false;
                for(int k = 0; k < nTail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        print = true;
                        cout << "o";

                    }
                }
                if (!print)
                cout << " ";
            }
        }
        cout << endl;
    }

    for(int i = 0; i < width + 1; ++i)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;
        usleep(500 * 1000);

}
void SnakeGame::input()
{
    if(kbhit())
    switch(getchar())
    {
    case 'a':
        dir = LEFT;
        break;
    case 'd':
        dir = RIGHT;
        break;
    case 'w':
        dir = UP;
        break;
    case 's':
        dir = DOWN;
        break;
    case 'x':
        gameOver = true;
        break;
    }
}
void SnakeGame::logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prevX2, prevY2;
    tailX[0] = x;
    tailY[0] = y;
    for(int i = 1; i < nTail; i++)
    {
        prevX2 = tailX[i];
        prevY2 = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prevX2;
        prevY = prevY2;
    }
    switch(dir)
    {

    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

//    if ( x > width || x < 0 || y > height || y < 0)
//        gameOver = true;
    if(x >= width -1)
        x = 0;
    else if(x < 0)
        x = width - 2;

    if(y >= height)
        y = 0;
    else if(y < 0)
        y = height - 1;

    for(int i = 0; i < nTail; i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    if ( x == fruitX && y == fruitY)
    {
        score++;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail++;

    }
}
