

#include "../ConsoleLibrary/Console.h"
#include "Shape.h"

#include <vector>
#include <time.h>


#define WIDTH 50
#define HEIGHT 40

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 20


void keyFunction(WORD keyCode);
void timerFunction();

void render();
void checkForFullLines();


Console* console;
Matrix* matrix;
Shape* shape;


int main(int argc, char* argv[])
{
    srand(time_t(NULL));

    console = new Console("Tetris", WIDTH, HEIGHT, WHITE, BLACK);
    matrix = new Matrix(MATRIX_WIDTH, MATRIX_HEIGHT);

    console->registerKeyEvent(&keyFunction);
    console->registerTimerEvent(&timerFunction, 50);

    shape = new Shape(matrix, 10);

    console->run();

    delete matrix;
    delete console;
}


void keyFunction(WORD keyCode)
{
    if (keyCode == VK_LEFT)
    {
        shape->moveLeft();
    }
    else if (keyCode == VK_RIGHT)
    {
        shape->moveRight();
    }
    else if (keyCode == VK_DOWN)
    {
        shape->moveDown();
    }
    else if (keyCode == VK_UP)
    {
        shape->rotateLeft();
    }
    else if (keyCode == VK_SPACE)
    {
        shape->rotateRight();
    }
    else if (keyCode == VK_ESCAPE)
    {
        console->stop();
    }
}


void timerFunction()
{
    // is shape already placed on the matrix
    if (shape->checkForCollision(shape->x, shape->y))
    {
        matrix->reset();
        shape = new Shape(matrix, 10);
        return;
    }

    if (!shape->update())
    {
        shape = new Shape(matrix, 10);
    }

    checkForFullLines();

    render();
}


void checkForFullLines()
{
    for (int y = MATRIX_HEIGHT - 1; y >= 0; y--)
    {
        // search for a full line
        int x;
        for (x = 0; x < MATRIX_WIDTH; x++)
        {
            if (!matrix->field[y][x])
            {
                break;
            }
        }

        // delete the found line and move all bricks above downwards
        if (x == MATRIX_WIDTH)
        {
            for (int cy = y - 1; cy > 0; cy--)
            {
                for (int cx = 0; cx < MATRIX_WIDTH; cx++)
                {
                    matrix->field[cy + 1][cx] = matrix->field[cy][cx];
                }
            }

            for (x = 0; x < MATRIX_WIDTH; x++)
            {
                matrix->field[0][x] = false;
            }

            // do not ignore the next line
            y++;
        }
    }
}


void render()
{
    console->clearConsole();

    for (int y = 0; y < MATRIX_HEIGHT; y++)
    {
        for (int x = 0; x < MATRIX_WIDTH; x++)
        {
            if (matrix->field[y][x])
            {
                console->setTile(2 * x,     2 * y,     '#');
                console->setTile(2 * x + 1, 2 * y,     '#');
                console->setTile(2 * x,     2 * y + 1, '#');
                console->setTile(2 * x + 1, 2 * y + 1, '#');
            }
        }
    }

    for (Point &point : *shape->blocks)
    {
        int x = 2 * (shape->x + point.x);
        int y = 2 * (shape->y + point.y);
        console->setTile(x,     y,     '+');
        console->setTile(x + 1, y,     '+');
        console->setTile(x,     y + 1, '+');
        console->setTile(x + 1, y + 1, '+');
    }

    console->redraw();
}