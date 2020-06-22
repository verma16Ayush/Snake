#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <process.h>
 
#define UP    72
#define DOWN  80
#define LEFT  75
#define RIGHT 77
 
struct coordinate {
    int X;
    int Y;
    int direction;
};
 
typedef struct coordinate coordinate;
 
coordinate head, apple, sBody;
 
int body[500];
int gameOver = 0;
int appleEaten = 0;
int life = 3;

void setXY(int, int);
void boarderDraw();
void spawnSnake();
void move();
void goToXY(int, int);
void setXY(int, int);
void up();
void down();
void left();
void right();
void food();
void eat();
void printBody();
void endGame();
void HideCursor(bool);


void HideCursor(bool hideOrShow)
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = hideOrShow;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main() {
    HideCursor(FALSE);
    setXY(2, 2);
    printf("Remaining Lives");
    apple.X = 0;
    apple.Y = 0;
    boarderDraw();
    spawnSnake();
    move();
}
 
void boarderDraw() {
    setXY(2, 2);
    printf("Remaining Lives: ");
    setXY(19, 2);
    printf("%d", life);
    int i;
    for (i = 5; i < 81; i++) {
        setXY(i, 5);
        printf("~");
        setXY(i, 30);
        printf("~");
    }
    for (i = 5; i < 31; i++) {
        setXY(5, i);
        printf("|");
        setXY(80, i);
        printf("|");
    }
}
 
void spawnSnake() {
    int x = 81 / 2;
    int y = 31 / 2;
    head.X = x;
    head.Y = y;
    head.direction = RIGHT;
    setXY(x, y);
    printf(">");
}
 
void move() {
    endGame();
    boarderDraw();
    food();
    printBody();
    char input;
    while (!kbhit()) {
        int localDir;
        localDir = head.direction;
        if (localDir == LEFT) {
            endGame();
            boarderDraw();
            system("cls");
            head.X--;
            boarderDraw();
            food();
            setXY(head.X, head.Y);
            printf("<");
            eat();
            printBody();
        }
        else if (localDir == RIGHT) {
            endGame();
            boarderDraw();
            system("cls");
            head.X++;
            boarderDraw();
            food();
            setXY(head.X, head.Y);
            printf(">");
            eat();
            printBody();
        } else if (localDir == UP) {
            endGame();
            boarderDraw();
            system("cls");
            head.Y--;
            boarderDraw();
            food();
            setXY(head.X, head.Y);
            printf("^");
            eat();
            printBody();
        } else {
            endGame();
            boarderDraw();
            system("cls");
            head.Y++;
            boarderDraw();
            food();
            setXY(head.X, head.Y);
            printf("v");
            eat();
            printBody();
        }
    }
    if (kbhit()) 
    {
        endGame();
        while (gameOver == 0) 
        {
            input = getch();    //Change INPUT to desired direction.         
            if (input == UP) 
            {
                up();
            }
            if (input == DOWN) 
            {
                down();
            }
            if (input == LEFT) 
            {
                left();
            }
            if (input == RIGHT) 
            {
                right();
            } 
            else if (gameOver == 1) 
            {
                system("cls");
            } 
            
            else if (input == 27) 
            {
                gameOver = 1;
                system("cls");
                exit(0);
            }
        }
    }
}
 
void goToXY(int x, int y) 
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
 
void setXY(int x, int y) 
{
    COORD c;
    fflush(stdout);
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
 
void up() 
{
    eat();
    if (head.direction != DOWN) 
    {
        head.direction = UP;
        head.Y--;
        system("cls");
        boarderDraw();
        setXY(head.X, head.Y);
        printf("^");
        endGame();
        move();
        food();
        printBody();
    } 

    else 
    {
        endGame();
        move();
        food();
    }
}
 
void down() 
{
    eat();
    if (head.direction != UP) 
    {
        head.direction = DOWN;
        head.Y++;
        system("cls");
        boarderDraw();
        setXY(head.X, head.Y);
        printf("v");
        endGame();
        move();
        food();
        printBody();
    } 
    
    else 
    {
        endGame();
        move();
        food();
    }
}
 
void left() 
{
    eat();

    if (head.direction != RIGHT) 
    {
        head.direction = LEFT;
        head.X--;
        system("cls");
        boarderDraw();
        setXY(head.X, head.Y);
        printf("<");
        endGame();
        move();
        food();
        printBody();
    } 
    
    else 
    {
        endGame();
        move();
        food();
    }
}
 
void right() 
{
    eat();
    if (head.direction != LEFT) 
    {
        head.direction = RIGHT;
        head.X++;
        system("cls");
        boarderDraw();
        setXY(head.X, head.Y);
        printf(">");
        endGame();
        move();
        food();
        printBody();
    } 
    else
    {
        endGame();
        move();
        food();
    }
}
 
void food() 
{
    if (apple.X == 0 && apple.Y == 0) 
    {
        int rx = ((rand() % 74 + 5));
        int ry = ((rand() % 24 + 5));
        apple.X = rx;
        apple.Y = ry;
        setXY(apple.X, apple.Y);
        printf("A");
    } else {
        setXY(apple.X, apple.Y);
        printf("A");
    }
}
 
void eat() 
{
    if (head.X == apple.X && head.Y == apple.Y) 
    {
        appleEaten++;
        apple.X = 0;
        apple.Y = 0;
        body[appleEaten] = 0;
    }
/*  for(int i=0;i<appleEaten;i++)            
    {                
        setXY(head.X, (head.Y));                
        printf("%d", body[i]);                
        food();                
        move();            
    }*/
}
 
void printBody() 
{
    if (head.direction == RIGHT) 
    {

        for (int i = 1; i <= appleEaten; i++) 
        {
            sBody.X = (head.X - i);
            sBody.Y = (head.Y);
            setXY(sBody.X, sBody.Y);
            printf("%d", body[i]);
        }
    } 
    else if (head.direction == LEFT) 
    {
        for (int i = 1; i <= appleEaten; i++) 
        {
            sBody.X = (head.X + i);
            sBody.Y = (head.Y);
            setXY(sBody.X, sBody.Y);
            printf("%d", body[i]);
        }
    } 
    else if(head.direction == UP) 
    {
        for (int i = 1; i <= appleEaten; i++) 
        {
            sBody.X = (head.X);
            sBody.Y = (head.Y + i);
            setXY(sBody.X, sBody.Y);
            printf("%d", body[i]);
        }
    }
    else if (head.direction == DOWN) 
    {
        for (int i = 1; i <= appleEaten; i++) 
        {
            sBody.X = (head.X);
            sBody.Y = (head.Y - i);
            setXY(sBody.X, sBody.Y);
            printf("%d", body[i]);
        }
    }
}
 
void endGame() 
{
    if (head.X <= 5 || head.X >= 81 || head.Y <= 5 || head.Y >= 30) 
    {
        life--;
        system("cls");
        appleEaten = 0;
        main();
    } 
    else 
    {
        gameOver = 0;
    }
    if (life == 0) 
    {
        gameOver = 1;
        system("cls");
        exit(0);
    }
}