#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 20;
int snakeX, snakeY, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

bool gameOver;

char screen[height][width];

void Setup()
{
    dir = STOP;
    snakeX = width / 2;
    snakeY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    gameOver = false;
}

void Draw()
{
    system("cls");

    // Fill the screen array with spaces
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screen[i][j] = ' ';
        }
    }

    for (int i = 0; i < nTail; i++) {
        screen[tailY[i]][tailX[i]] = 'o';
    }

    screen[snakeY][snakeX] = 'O';
    screen[fruitY][fruitX] = 'F';

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "#";
            cout << screen[i][j];
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score:" << score << endl;
}

void Input()
{
    if (_kbhit()) {
        switch (_getch()) {
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
            dir = STOP;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = snakeX;
    tailY[0] = snakeY;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir) {
    case LEFT:
        snakeX--;
        break;
    case RIGHT:
        snakeX++;
        break;
    case UP:
        snakeY--;
        break;
    case DOWN:
        snakeY++;
        break;
    default:
        break;
    }

    if (snakeX >= width) snakeX = 0; else if (snakeX < 0) snakeX = width - 1;
    if (snakeY >= height) snakeY = 0; else if (snakeY < 0) snakeY = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == snakeX && tailY[i] == snakeY)
            gameOver = true;

    if (snakeX == fruitX && snakeY == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(10); //sleep(10);
    }
    cout << "Game Over!" << endl;
    return 0;
}
