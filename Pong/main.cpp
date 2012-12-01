#include "../ConsoleLibrary/Console.h"
#include "Ball.h"

#define WIDTH 40
#define HEIGHT 40

#define PAD_SIZE 8
#define PAD_STEP_SIZE 2


struct Vector
{
    float x;
    float y;
};

void keyUpFunction(WORD keyCode, DWORD modifier);
void timerFunction();

void initRound();

void computeBot();
void update();
void render();

Console* console;

COLOR_ID botColor;
COLOR_ID playerColor;
COLOR_ID scoreColor;
COLOR_ID ballColor;

int playerPos;
int botPos;
Ball* ball;

int botScore;
int playerScore;
int speedCounter;
int lostCounter;


int main(int argc, char* argv[])
{
    console = new Console("Pong", WIDTH, HEIGHT, BLACK, WHITE);

    botColor = console->createColor(GREEN, YELLOW);
    playerColor = console->createColor(RED, YELLOW);
    scoreColor = console->createColor(BLACK, WHITE);
    ballColor = console->createColor(BLUE, WHITE);

    botScore = 0;
    playerScore = 0;

    initRound();

    console->registerKeyUpEvent(&keyUpFunction);
    console->registerTimerEvent(&timerFunction, 50);

    console->run();

    delete console;
    
    return 0;
}

void initRound()
{
    playerPos = HEIGHT / 2 - 4;
    botPos = HEIGHT / 2 - 4;
    ball = new Ball(WIDTH / 2, HEIGHT / 2, 0.5f);
    ball->randomizeDirection();

    speedCounter = 0;

    lostCounter = 0;
}

void keyUpFunction(WORD keyCode, DWORD modifier)
{
    if (keyCode == VK_ESCAPE)
    {
        console->stop();
    }
    else if (keyCode == VK_UP && lostCounter == 0)
    {
        if (playerPos >= PAD_STEP_SIZE)
        {
            playerPos -= PAD_STEP_SIZE;
        }
        else if (playerPos > 0)
        {
            playerPos = 0;
        }
    }
    else if (keyCode == VK_DOWN && lostCounter == 0)
    {
        if (playerPos < HEIGHT - PAD_SIZE - PAD_STEP_SIZE)
        {
            playerPos += PAD_STEP_SIZE;
        }
        else if (playerPos < HEIGHT - 1)
        {
            playerPos = HEIGHT - PAD_SIZE;
        }
    }
}

void timerFunction()
{
    computeBot();
    update();
    render();
}

inline void computeBot()
{
    if (lostCounter == 0)
    {
        int ballX = ball->getNextX();
        int ballY = ball->getNextY();
        int botY = botPos + PAD_SIZE / 2;

        if (ballX < WIDTH * 3 / 4)
        {
            if (ballY - botY > 0)
            {
                if (botPos < HEIGHT - PAD_SIZE - PAD_STEP_SIZE)
                {
                    botPos += PAD_STEP_SIZE;
                }
                else if (botPos < HEIGHT - 1)
                {
                    botPos = HEIGHT - PAD_SIZE;
                }
            }
            else if (ballY - botY < 0)
            {
                if (botPos >= PAD_STEP_SIZE)
                {
                    botPos -= PAD_STEP_SIZE;
                }
                else if (botPos > 0)
                {
                    botPos = 0;
                }
            }
        }
    }
}

inline void update()
{

    if (lostCounter > 0)
    {
        if (++lostCounter == 20)
        {
            initRound();
        }
    }

    if (lostCounter == 0)
    {
        if (++speedCounter == 20)
        {
            speedCounter = 0;
            ball->speed += 0.05f;
        }

        int x = ball->getNextX();
        int y = ball->getNextY();

        if (y < 0 || y >= HEIGHT)
        {
            ball->dirY *= -1;
        }

        if (x <= 0)
        {
            if (y >= botPos && y < botPos + PAD_SIZE)
            {
                //ball->dirX *= -1;
                float step = 1.0f / (PAD_SIZE - 1);
                int pos = y - botPos;
                ball->bounce(step * pos);
            }
            else
            {
                playerScore++;
                lostCounter = 1;
                ball->move();
                ball->dirX = 0;
                ball->dirY = 0;
                ball->x = 0;
            }
        }

        else if (x >= WIDTH - 1)
        {
            if (y >= playerPos && y < playerPos + PAD_SIZE)
            {
                //ball->dirX *= -1;
                float step = 1.0f / (PAD_SIZE - 1);
                int pos = y - playerPos;
                ball->bounce(step * pos);
            }
            else
            {
                botScore++;
                lostCounter = 1;
                ball->move();
                ball->dirX = 0;
                ball->dirY = 0;
                ball->x = WIDTH - 1;
            }
        }

        ball->move();
    }
}

inline void render()
{
    console->clearConsole();

    for (int i = 0; i < PAD_SIZE; i++)
    {
        console->setTile(0, i + botPos, '#', botColor);
        console->setTile(WIDTH - 1, i + playerPos, '#', playerColor);
    }

    console->setTile(15, 1, 48 + botScore, scoreColor);
    console->setTile(WIDTH - 17, 1, 48 + playerScore, scoreColor);

    console->setTile(ball->getX(), ball->getY(), 'o', ballColor);

    console->redraw();
}