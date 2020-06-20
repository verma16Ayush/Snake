#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>
#include <dos.h>

//define a structure to hold 2d position
struct  position
{
    int x;
    int y;
};
//declare position structs for fruit and head position
struct position fruitPos, headPos;

//a bool to know if the game has ended;
bool hasEnded = false;

// structure of ground matrix
const int nCols = 60;
const int nRows = 30;

//define move direction. wasd keymap.
char moveDir; 

// declare snake character array
char snake[50];
struct position snakeCoordinate[50];
int initSnakeSize = 4;

char board[30][60];

void HideCursor(bool); //hide the console cursor
void SetBoard(); // Initialise the playboard ground
void Delay(int); // delay code execution. determines the speed of game
void DrawBoard(); // Show the state of board
void Move(char);// move the snake
void SpawnSnake(); // self explanatory bro. also use to increase snake size
void GenFood();// gen food at random position
void Init(); // initialise everything for a fresh start
void Input(); // take user input (if any).

void Init()
{
    //seed the PRNG
    srand(time(0));

    //spawn a new snake
    SpawnSnake();

    //spawn food
    GenFood();
}
void GenFood()
{
    fruitPos.x = rand() % nCols;
    fruitPos.y = rand() % nRows;

    if(fruitPos.x == 0)
        fruitPos.x = 1;

    if(fruitPos.y == 0)
        fruitPos.y = 1;

}

void Input()
{
    if(kbhit())
    {
        moveDir = getch();
    }
}

void SpawnSnake()
{

    headPos.x = nCols / 2;
    headPos.y = nRows / 2;

}

void HideCursor(bool hideOrShow)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = hideOrShow;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void SetBoard()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if(i == 0 || i == nRows - 1)
            {
                board[i][j] = '~';
            }
            else if(j == 0 || j == nCols -1)
            {
                board[i][j] = '|';
            }
            else if(j == fruitPos.x && i == fruitPos.y)
            {
                board[i][j] = '*';
            }
            else if(i == headPos.y && j == headPos.x)
            {
                board[i][j] = 'o';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
}



void Delay(int milliSeconds) 
{  
    // Storing start time 
    clock_t startTime = clock(); 
  
    // looping till required time is not achieved 
    while (clock() < startTime + milliSeconds) 
        {}; 
} 

void DrawBoard()
{
    //clear screen every time you display the updated board
    system("cls");
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void Move(char locDir)
{
    
    switch (locDir)
    {
        case 'w':
            headPos.y--;
            break;
        
        case 's':
            headPos.y++;
            break;
        
        case 'a':
            headPos.x--;
            break;
        
        case 'd':
            headPos.x++;
            break;

        case 'x':
            hasEnded = true;
            break;
        
        default:
            break;
    }
    
}

int main()
{
    HideCursor(FALSE);
    Init();

    while(!hasEnded)
    {
        SetBoard();
        DrawBoard();
        Input();
        Move(moveDir);
    }

    return 0;
}






