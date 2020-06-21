#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

//height and width of play area
int width = 40; 
int height = 20;

int snakeX[100], snakeY[100];

//size of snake
int snakeSize = 0;

// variables to store x and y poosition of snake head and fruit
int headPosX, headPosY, fruitPosX, fruitPosY, score;

//if the game has ended
bool hasEnded = false;

//store the move direction of the snake. wasd keymap. x to quit.
char moveDir;

void Draw(); //draw the play board.
void Setup(); // setup everyhting for a fresh start.
void Input(); // get player input if any.
void Move(); // make the snake do snaky stuff.
void HideCursor(bool); // hide the console cursor. makes stuff look bad.
void SpawnSnake(); // spawn a snaky bad boi.
void SpawnFood(); // spawn delicious food bois.
void GameplayCode(); // handles the main gameplay logic of win / lose / reward checking.
void Delay(int); // Delay code execution.
void Bend(); // handles the bending logic of snake, seemed logical to keep it in another method.

void HideCursor(bool hideOrShow)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = hideOrShow;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void Delay(int milliSeconds) 
{  
    // Storing start time 
    clock_t startTime = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < startTime + milliSeconds) 
        {}; 
} 

void Setup()
{
    //seed the PRNG
    srand(time(0));

    //reset the snake size
    snakeSize = 1;
    
    //spawn a brand new snake
    SpawnSnake();

    //spawn some dellicious food bois
    SpawnFood();
}

void SpawnSnake()
{
    headPosX = width / 2;
    headPosY = height / 2;
}

void SpawnFood()
{
    fruitPosX = rand() % width - 1;
    fruitPosY = rand() % height - 1;

    if(fruitPosX == 0)
        fruitPosX = 1;
    
    if(fruitPosY == 0)
        fruitPosY = 1;
}

void Input()
{
    if(kbhit())
    {
        moveDir = getch();
    }
}

void Move()
{
    TestMethod();

    switch (moveDir)
    {
    case 'w':
        headPosY--;
        break;
    case 's':
        headPosY++;
        break;
    case 'a':
        headPosX--;
        break;
    case 'd':
        headPosX++;
        break;
    case 'x':
        hasEnded = true;
        break;
    default:
        break;
    }
}

void Draw()
{
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if(i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                printf("!");
            }
            else
            {
                if(i == headPosY && j == headPosX)
                {
                    printf("o");
                }

                else if(i == fruitPosY && j == fruitPosX)
                {
                    printf("*");
                }
                else
                {
                    int flag = 0;
                    for (int k = 0; k < snakeSize; k++)
                    {
                        if(i == snakeY[k] && j == snakeX[k])
                        {
                            printf("o");
                            flag = 1;
                        }
                    }

                    if(flag == 0)
                    {
                        printf(" ");
                    }
                }
                
            }
            
        }
        printf("\n");
    }
    printf("\nScore: %d       size: %d", score, snakeSize);
    
}

void Bend()
{
    int prevX = snakeX[0];
    int prevY = snakeY[0];

    int prev2X, prev2Y;

    snakeX[0] = headPosX;
    snakeY[0] = headPosY;

    for (int i = 1; i < snakeSize; i++)
    {
        prev2X = snakeX[i];
        prev2Y = snakeY[i];

        snakeX[i] = prevX;
        snakeY[i] = prevY;

        prevX = prev2X;
        prevY = prev2Y;
    }
    
}

void GameplayCode()
{
    if(headPosX == fruitPosX && headPosY == fruitPosY)
    {
        score += 10;
        SpawnFood();
        snakeSize += 1;
    }

    else if(headPosX >= width - 1 || headPosY >= height - 1 || headPosX <= 0 || headPosY <= 0)
    {
        hasEnded = true;
    }
}

int main()
{
    HideCursor(false);
    Setup();
    while(!hasEnded)
    {
        Draw();
        Input();
        GameplayCode();
        Move();
        Delay(10);
    }
    scanf("%d");
    return 0;
}