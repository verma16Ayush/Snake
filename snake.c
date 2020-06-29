// snake game
// run this file to play


// in case the entire play area is not visible 
// do not maximize the console window instead drag borders to resize it.
// maximizing the windo overrides the hide cursor method and makes the game look messy


#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

//height and width of play area
int width = 40; 
int height = 20;

//store coordinates of snake compoents or whatev
int snakeX[100], snakeY[100];

//size of snake
int snakeSize = 1;

//store the delay netween each frame and hence controls the game speed
int delayBwFrames = 250;

// variables to store x and y poosition of snake head and fruit
int headPosX, headPosY, fruitPosX, fruitPosY;

//store the score and highest score for that session
int score = 0, highScore = 0;

//if the game has ended
bool hasEnded = false;

//store the move direction of the snake. wasd keymap. x to quit.
char moveDir = '.';

void MainMenu(); // self explanatory
void Draw(); //draw the play board.
void Setup(); // setup everyhting for a fresh start.
void Input(); // get player input if any.
void Move(); // make the snake do snaky stuff.
void GameLoop();// the main game loop
void HideCursor(bool); // hide the console cursor. makes stuff look bad.
void SpawnSnake(); // spawn a snaky bad boi.
void SpawnFood(); // spawn delicious food bois.
void GameplayCode(); // handles the main gameplay logic of win / lose / reward checking.
void Delay(int); // Delay code execution.
void Bend(); // handles the bending logic of snake, seemed logical to keep it in another method.
void SetConsoleColor(); // set the console text color to green
void GameOver(); // handles game over process


void SetConsoleColor()
{
    printf("\033[1;34m");
}

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

void MainMenu()
{
    printf("WELCOME TO THE SNAKE GAME!\n\n");
    printf("Use WASD keys to control the snake\n");
    printf("Y/y: Put me in coach!\n");
    printf("Anything else: I'm too afraid of console snakes\n");
    printf("$> ");
    char yes;
    scanf("%c", &yes);
    switch (yes)
    {
    case 'y':
    case 'Y':
        break;
    default:
        exit(0);
        break;
    }
}

void Setup()
{
    //seed the PRNG
    srand(time(0));

    //reset hasEnded flag
    hasEnded = false;

    //set console color
    SetConsoleColor();

    //hide cursor
    HideCursor(false);

    //reset the snake size
    snakeSize = 1;

    //reset the game speed
    delayBwFrames = 250;

    //reset score
    score = 0;
    
    //spawn a brand new snake
    SpawnSnake();

    //spawn some dellicious food bois
    SpawnFood();

    //Reset the move direction back to none
    moveDir = '.';
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

    if(fruitPosX <= 0)
        fruitPosX = 1;
    
    if(fruitPosY <= 0)
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
    Bend();

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
    printf("\nScore: %d", score);
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
    //when snake eats the food
    if(headPosX == fruitPosX && headPosY == fruitPosY)
    {
        score += 10;
        SpawnFood();
        snakeSize += 1;
        delayBwFrames -= 10;

        if(score > highScore)
        {
            highScore = score;
        }
    }

    //when snake goes out of game bounds
    else if(headPosX >= width - 1 || headPosY >= height - 1 || headPosX <= 0 || headPosY <= 0)
    {
        hasEnded = true;
    }

    //when snake touches its own body
    //TODO: write code

    for (int i = 1; i < snakeSize; i++)
    {
        if(headPosX == snakeX[i] && headPosY == snakeY[i])
        {
            hasEnded = 1;
        }
    }
    
}

void GameOver()
{
    system("cls");
    printf("YOUR GAME HAS ENDED!\n");
    printf("YOUR SCORE: %d\n", score);

    if(highScore == score)
    {
        printf("NEW HIGH SCORE SET!!\n");
    }
    printf("Do you want to play again\nenter y for yes, any other key to exit:\n");
    char ch = getch();
    if(ch == 'y' || ch == 'Y')
   {
        Setup();
        GameLoop();
   }
    else
        exit(0);

}

void GameLoop()
{
    while(!hasEnded)
    {
        Draw();
        Input();
        GameplayCode();
        Move();
        if(delayBwFrames >= 0)
        {
            Delay(delayBwFrames);
        }
    }

     if(hasEnded)
        {
            GameOver();
        }
}

int main()
{
    system("cls");
    Setup();
    MainMenu();
    GameLoop();
    return 0;
}