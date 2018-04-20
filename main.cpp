#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

bool gameOver;
int const width = 40;
int const height = 20;
int x, y, fruitX, fruitY, score = 0;

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
 
int kbhit(void)
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

enum eDirection
{
    STOP = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT
};
eDirection dir;

void start()
{
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void draw()
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
                cout << "0";

            else if(i == fruitY && j == fruitX)
                cout << "F";

            cout << " ";
        }
        cout << endl;
    }

    for(int i = 0; i < width + 1; ++i)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;

       sleep(1);
}
void input()
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
void logic()
{
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
    }

    if ( x > width || x < 0 || y > height || y < 0)
        gameOver = true;
    if ( x == fruitX && y == fruitY)
    {
        score++;
    fruitX = rand() % width;
    fruitY = rand() % height;

    }
}

int main()
{
    start();
    while(!gameOver)
    {
        draw();
        input();
        logic();
    }
    return 0;
}