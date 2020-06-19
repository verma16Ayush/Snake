#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>


bool hasEnded = 0;
int x = 0;
struct  position
{
    int x;
    int y;
};

const int nCols = 60;
const int nRows = 30;

char board[30][60];

void InitBoard()
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if((i == 0 || i == nRows - 1) ||( j == 0 || j == nCols -1))
            {
                board[i][j] = '|';
            }
            else
            {
                board[i][j] = ' ';
            }
        }
    }
}

void ShowBoard(struct position fruitPos)
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            if(j == fruitPos.x && i == fruitPos.y)
            {
                board[i][j] = '0';
            }
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    //caching current time for seeding the random function
    int s = time(0);

    //seed the random number generator
    srand(s);

    //print seed value for debugging purposes
    printf("%d", s);
    printf("\n");

    //initialising the board
    InitBoard();

    //determine fruitposition randomly
    struct position fruitPos;
    fruitPos.x = rand() % nCols - 1;
    fruitPos.y = rand() % nRows - 1;

    //printing fruit position for debugging purposes
    printf("%d \t %d", fruitPos.x, fruitPos.y);
    printf("\n");

    // show board using the created method
    ShowBoard(fruitPos);
    scanf("%d");
    return 0;
}






