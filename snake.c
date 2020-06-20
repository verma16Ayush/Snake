#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

//height and width of play area
int width = 40; 
int height = 20;

// variables to store x and y poosition of snake head and fruit
int headPosX, headPosY, fruitPosX, fruitPosY, score;

//if the game has ended
bool hasEnded = false;

//store the move direction of the snake. wasd keymap. x to quit.
char moveDir;

void Draw(); //draw the play board
void Setup(); // setup everyhting for a fresh start
void Input(); // get player input if any
void Move(); // make the snake do snaky stuff
void HideCursor(bool); // hide the console cursor. makes stuff look bad.
void SpawnSnake(); // spawn a snaky bad boi
void SpawnFood(); // spawn delicious food bois

void HideCursor(bool hideOrShow)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = hideOrShow;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void Setup()
{
    //seed the PRNG
    srand(time(0));
    
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
    fruitPosX = rand() % width;
    fruitPosY = rand() % height;

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
                    printf(" ");
                }
                
            }
            
        }
        printf("\n");
        
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
        Move();
    }
    scanf("%d");
    return 0;
}