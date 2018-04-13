#include <iostream>
#include <unistd.h>
#include <ncurses.h>


using namespace std;

bool gameOver;
int const width = 40;
int const height = 20;
int x, y, fruitX, fruitY, score;

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
    x = width / 2 - 1;
    y = height / 2 - 1;
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

    sleep(1);
}
void input()
{
    if(kbhit())
    switch(getch())
    {
        if(getch() == 'a')
    }
}
void logic()
{

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
