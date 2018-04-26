#ifndef _SNAKE_GAME_H_
#define _SNAKE_GAME_H_

class SnakeGame
{
public:
    enum eDirection
    {
        STOP = 0,
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    SnakeGame();
    int kbhit();
    void draw();
    void logic();
    void input();

    bool getGameOver() const;

private:
    eDirection dir;
    bool gameOver;
    int const width;
    int const height;
    int x, y, fruitX, fruitY, score;
    int tailX[100];
    int tailY[100];
    int nTail;

};

#endif // _SNAKE_GAME_H_
