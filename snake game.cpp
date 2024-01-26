#include <conio.h> 
#include <iostream> 
#include <windows.h> 
using namespace std;

const int width = 80;
const int height = 20;


int x, y;
int fruitX, fruitY;
int playerScore;
int tailX[100], tailY[100];
int tailLen;
enum snakesWay { Stop = 0, Left, Right, Up, Down };
snakesWay sDir;
bool gameOver;

void GameInit()
{
    gameOver = false;
    sDir = Stop;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    playerScore = 0;
}

void GameRender(string playerName)
{
    system("cls"); // Clear the console 

    // Creating top walls with '#' 
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            // Creating side walls with '#' 
            if (j == 0 || j == width)
                cout << "#";

            // Creating snake's head with '@' 
            if (i == y && j == x) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                cout << "@";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            // Creating the sanke's food with '*' 
            else if (i == fruitY && j == fruitX) {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                cout << "*";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            }
            // Creating snake's tail with 'O' 
            else {
                bool prTail = false;
                for (int k = 0; k < tailLen; k++) {
                    if (tailX[k] == j
                        && tailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    // Creating bottom walls with '#' 
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    // Display player's score 
    cout << playerName << "'s Score: " << playerScore
        << endl;
}

// Function for updating the game state 
void UpdateGame()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLen; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
    case Left:
        x--;
        break;
    case Right:
        x++;
        break;
    case Up:
        y--;
        break;
    case Down:
        y++;
        break;
    }

    // Checks for snake's collision with the wall (|) 
    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    // Checks for collision with the tail (o) 
    for (int i = 0; i < tailLen; i++) {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // Checks for snake's collision with the food (#) 
    if (x == fruitX && y == fruitY) {
        playerScore += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLen++;
    }
}

// Function to set the game difficulty level 
int SetDifficulty()
{
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: hard "
        "\nNOTE: if not chosen or pressed any other "
        "key, the difficulty will be automatically set "
        "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 50;
        break;
    case '2':
        dfc = 100;
        break;
    case '3':
        dfc = 150;
        break;
    default:
        dfc = 100;
    }
    return dfc;
}

// Function to handle user UserInput 
void UserInput()
{
    // Checks if a key is pressed or not 
    if (_kbhit()) {
        // Getting the pressed key 
        switch (_getch()) {
        case 'a':
            sDir = Left;
            break;
        case 'd':
            sDir = Right;
            break;
        case 'w':
            sDir = Up;
            break;
        case 's':
            sDir = Down;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// Main function / game looping function 
int main()
{
    string playerName;
    cout << "enter your name: ";
    cin >> playerName;
    int dfc = SetDifficulty();

    GameInit();
    while (!gameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        // creating a delay for according to the chosen 
        // difficulty 
        Sleep(dfc);
    }

    return 0;
}