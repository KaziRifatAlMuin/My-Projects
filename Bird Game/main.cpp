#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

const int screenWidth = 80;
const int screenHeight = 20;
const char birdChar = '@';
const char coinChar = '*';
const char obstacleChar = '#';
const int maxObstacles = 5;
const int maxCoins = 5;
const int obstacleSpeed = 2;

int birdX = 10;
int birdY = screenHeight / 2;
int coinsCollected = 0;
int obstacleX[maxObstacles], obstacleY[maxObstacles];
int coinX[maxCoins], coinY[maxCoins];

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

void SetConsoleColor(int color)
{
    SetConsoleTextAttribute(console, color);
}

void DrawScreen()
{
    system("cls");
    for (int i = 0; i < screenHeight; i++)
    {
        for (int j = 0; j < screenWidth; j++)
        {
            if (i == birdY && j == birdX)
            {
                SetConsoleColor(9); // Bird color
                cout << birdChar;
            }
            else
            {
                bool isObstacle = false;
                for (int k = 0; k < maxObstacles; k++)
                {
                    if (i == obstacleY[k] && j == obstacleX[k])
                    {
                        SetConsoleColor(4); // Obstacle color
                        cout << obstacleChar;
                        isObstacle = true;
                    }
                }
                if (!isObstacle)
                {
                    bool isCoin = false;
                    for (int k = 0; k < maxCoins; k++)
                    {
                        if (i == coinY[k] && j == coinX[k])
                        {
                            SetConsoleColor(14); // Coin color
                            cout << coinChar;
                            isCoin = true;
                        }
                    }
                    if (!isCoin)
                    {
                        SetConsoleColor(7); // Default color
                        cout << " ";
                    }
                }
            }
        }
        cout << endl;
    }
    SetConsoleColor(7); // Reset color to default
    cout << "Coins collected: " << coinsCollected << endl;
}

void MoveObstacles()
{
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacleX[i] -= obstacleSpeed;
        if (obstacleX[i] < 0)
        {
            obstacleX[i] = screenWidth - 1;
            obstacleY[i] = rand() % screenHeight;
        }
    }
}

void MoveCoins()
{
    for (int i = 0; i < maxCoins; i++)
    {
        coinX[i] -= 1;
        if (coinX[i] < 0)
        {
            coinX[i] = screenWidth - 1;
            coinY[i] = rand() % screenHeight;
        }
    }
}

void CheckCollisions()
{
    for (int i = 0; i < maxObstacles; i++)
    {
        if (birdX == obstacleX[i] && birdY == obstacleY[i])
        {
            SetConsoleColor(12); // Collision color
            cout << "Game Over! Collision with obstacle." << endl;
            exit(0);
        }
    }

    for (int i = 0; i < maxCoins; i++)
    {
        if (birdX == coinX[i] && birdY == coinY[i])
        {
            coinsCollected++;
            coinX[i] = screenWidth - 1;
            coinY[i] = rand() % screenHeight;
        }
    }
}

int main()
{
    // Initialize obstacles and coins
    for (int i = 0; i < maxObstacles; i++)
    {
        obstacleX[i] = rand() % screenWidth;
        obstacleY[i] = rand() % screenHeight;
    }

    for (int i = 0; i < maxCoins; i++)
    {
        coinX[i] = rand() % screenWidth;
        coinY[i] = rand() % screenHeight;
    }

    while (true)
    {
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'w' && birdY > 0)
                birdY--;
            if (key == 's' && birdY < screenHeight - 1)
                birdY++;
        }

        MoveObstacles();
        MoveCoins();
        CheckCollisions();
        DrawScreen();

        Sleep(100); // Adjust speed
    }

    return 0;
}
