// Snake_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

enum Directions
{
    UP,DOWN,LEFT,RIGHT
};
struct Position
{
    int ri, ci;
};
struct Snake
{
    Position* Ps;
    int size;
    int score;
    char sym;
    Directions Dir;
    string PNames;
    int LEFTKEY, RIGHTKEY, UPKEY, DOWNKEY;
};
struct food
{
    Position fp;
    bool isAlive;
    int score;
    char sym;
};

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}
void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void generateFood(food& f, int h, int w, Snake& S);

bool SinglePlayer(Position P)
{
    for (int i = 43; i < 46; i++)
    {
        for (int j = 60; j < 77; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool MultiPlayer(Position P)
{
    for (int i = 43; i < 46; i++)
    {
        for (int j = 90; j < 107; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool DuniyaGolHai(Position P)
{
    for (int i = 43; i < 46; i++)
    {
        for (int j = 75; j < 92; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool LevelByLevel(Position P)
{
    for (int i = 48; i < 51; i++)
    {
        for (int j = 75; j < 92; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool CustomLevel(Position P)
{
    for (int i = 53; i < 56; i++)
    {
        for (int j = 75; j < 92; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool Easy(Position P)
{
    for (int i = 43; i < 46; i++)
    {
        for (int j = 75; j < 84; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool Medium(Position P)
{
    for (int i = 48; i < 51; i++)
    {
        for (int j = 75; j < 84; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}
bool Hard(Position P)
{
    for (int i = 53; i < 56; i++)
    {
        for (int j = 75; j < 84; j++)
        {
            if (P.ri == i && P.ci == j)
                return true;
        }
    }
    return false;
}





void PrintBoundary(char sym)
{
    SetClr(4);
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if ((i == 0 || i == 59) || (j == 0 || j == 99))
            {
                cout << sym;
            }
            else
                cout << " ";
        }
        cout << endl;
    }
    SetClr(15);
}
void PrintBoundary1(char sym)
{
    SetClr(4);
    for (int i = 0; i < 60; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            if (((i <= 25 || (i >= 35 && i <= 60)) && (j == 0 || j == 99) || ((i==25 || i==35) && (j>=35 && j<=75))) || (i == 0 || i == 59))
            {
                if ((i == 0 && ((j >= 25 && j <= 35) || (j >= 75 && j <= 85))) || (i == 59 && ((j >= 25 && j <= 35) || (j >= 75 && j <= 85))))
                    cout << " ";
                else
                    cout << sym;
            }
            else
                cout << " ";
        }
        cout << endl;
    }
    SetClr(15);
}
void init(Snake& S, int h, int w, food& f, food& f2)
{
    S.Ps = new Position[3];

    S.Ps[0].ri = h / 2;
    S.Ps[0].ci = w / 2;

    S.Ps[1].ri = h / 2;
    S.Ps[1].ci = w / 2 - 1;

    S.Ps[2].ri = h / 2;
    S.Ps[2].ci = w / 2 - 2;

    S.size = 3;
    S.score = 0;
    S.sym = -37;
    system("cls");
    gotoRowCol(40, 71);
    cout << "Player's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S.PNames;
    S.Dir = RIGHT;
    S.RIGHTKEY = 77, S.LEFTKEY = 75, S.UPKEY = 72, S.DOWNKEY = 80;
    generateFood(f, h, w, S);
    f.sym = '*';
    generateFood(f2, h, w, S);
    f2.score = 3;
    f2.sym = '*';
}
void init2P(Snake& S, Snake& S2, int h, int w, food& f, food& f2)
{
    S.Ps = new Position[3]{};
    S2.Ps = new Position[3]{};

    S.Ps[0].ri = h / 2 - 2;
    S.Ps[0].ci = w / 2 - 2;

    S.Ps[1].ri = h / 2 - 2;
    S.Ps[1].ci = w / 2 - 1 - 2;

    S.Ps[2].ri = h / 2 - 2;
    S.Ps[2].ci = w / 2 - 2 - 2;

    S2.Ps[0].ri = h / 2 + 2;
    S2.Ps[0].ci = w / 2 + 2;

    S2.Ps[1].ri = h / 2 + 2;
    S2.Ps[1].ci = w / 2 - 1 + 2;

    S2.Ps[2].ri = h / 2 + 2;
    S2.Ps[2].ci = w / 2 - 2 + 2;

    S.size = 3;
   
        S.score = 0;
    S.sym = -37;
    system("cls");
    gotoRowCol(40, 71);
    cout << "Player 1's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S.PNames;
    S.Dir = RIGHT;
    S.RIGHTKEY = 77, S.LEFTKEY = 75, S.UPKEY = 72, S.DOWNKEY = 80;

    S2.size = 3;
   
        S2.score = 0;
    S2.sym = -37;
    gotoRowCol(40, 71);
    cout << "Player 2's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S2.PNames;
    S2.Dir = RIGHT;
    S2.RIGHTKEY = 100, S2.LEFTKEY = 97, S2.UPKEY = 119, S2.DOWNKEY = 115;
    generateFood(f, h, w, S);
    f.sym = '*';
    generateFood(f2, h, w, S);
    f2.score = 3;
    f2.sym = '*';
}
void init3P(Snake& S, Snake& S2, Snake& S3, int h, int w, food& f, food& f2)
{
    S.Ps = new Position[3]{};
    S2.Ps = new Position[3]{};
    S3.Ps = new Position[3]{};
    S.Ps[0].ri = h / 2;
    S.Ps[0].ci = w / 2 - 2;

    S.Ps[1].ri = h / 2;
    S.Ps[1].ci = w / 2 - 1 - 2;

    S.Ps[2].ri = h / 2;
    S.Ps[2].ci = w / 2 - 2 - 2;

    S2.Ps[0].ri = h / 2 + 2;
    S2.Ps[0].ci = w / 2 + 2;

    S2.Ps[1].ri = h / 2 + 2;
    S2.Ps[1].ci = w / 2 - 1 + 2;

    S2.Ps[2].ri = h / 2 + 2;
    S2.Ps[2].ci = w / 2 - 2 + 2;


    S3.Ps[0].ri = h / 2 - 2;
    S3.Ps[0].ci = w / 2 - 2;

    S3.Ps[1].ri = h / 2 - 2;
    S3.Ps[1].ci = w / 2 - 1 - 2;

    S3.Ps[2].ri = h / 2 - 2;
    S3.Ps[2].ci = w / 2 - 2 - 2;

    S.size = 3;
    
        S.score = 0;
    S.sym = -37;
    system("cls");
    gotoRowCol(40, 71);
    cout << "PLayer 1's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S.PNames;
    S.Dir = RIGHT;
    S.RIGHTKEY = 77, S.LEFTKEY = 75, S.UPKEY = 72, S.DOWNKEY = 80;

    S2.size = 3;
    
        S2.score = 0;
    S2.sym = -37;
    gotoRowCol(40, 71);
    cout << "Player 2's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S2.PNames;
    S2.Dir = RIGHT;
    S2.RIGHTKEY = 100, S2.LEFTKEY = 97, S2.UPKEY = 119, S2.DOWNKEY = 115;

    S3.size = 3;
    if (S3.score == 0)
        S3.score = 0;
    S3.sym = -37;
    S3.score = 0;
    gotoRowCol(40, 71);
    cout << "Player 3's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S3.PNames;
    S3.Dir = RIGHT;
    S3.RIGHTKEY = 108, S3.LEFTKEY = 106, S3.UPKEY = 105, S3.DOWNKEY = 107;
    generateFood(f, h, w, S);
    f.sym = '*';
    generateFood(f2, h, w, S);
    f2.score = 3;
    f2.sym = '*';
}
void init4P(Snake& S, Snake& S2, Snake& S3, Snake& S4, int h, int w, food& f, food& f2)
{
    S.Ps = new Position[3]{};
    S2.Ps = new Position[3]{};
    S3.Ps = new Position[3]{};
    S4.Ps = new Position[3]{};

    S.Ps[0].ri = h / 2-1;
    S.Ps[0].ci = w / 2;

    S.Ps[1].ri = h / 2-1;
    S.Ps[1].ci = w / 2 - 1;

    S.Ps[2].ri = h / 2-1;
    S.Ps[2].ci = w / 2 - 2;

    S2.Ps[0].ri = h / 2 + 2;
    S2.Ps[0].ci = w / 2;

    S2.Ps[1].ri = h / 2 + 2;
    S2.Ps[1].ci = w / 2 - 1;

    S2.Ps[2].ri = h / 2 + 2;
    S2.Ps[2].ci = w / 2 - 2;


    S3.Ps[0].ri = h / 2 - 2;
    S3.Ps[0].ci = w / 2;

    S3.Ps[1].ri = h / 2 - 2;
    S3.Ps[1].ci = w / 2-1;

    S3.Ps[2].ri = h / 2 - 2;
    S3.Ps[2].ci = w / 2 - 2;

    S4.Ps[0].ri = h / 2 + 1;
    S4.Ps[0].ci = w / 2 ;

    S4.Ps[1].ri = h / 2 + 1;
    S4.Ps[1].ci = w / 2 - 1;

    S4.Ps[2].ri = h / 2 + 1;
    S4.Ps[2].ci = w / 2 - 2;

    S.size = 3;
    
        S.score = 0;
    S.sym = -37;
    system("cls");
    gotoRowCol(40, 71);
    cout << "PLayer 1's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> S.PNames;
    S.Dir = RIGHT;
    S.RIGHTKEY = 77, S.LEFTKEY = 75, S.UPKEY = 72, S.DOWNKEY = 80;

    S2.size = 3;
   
        S2.score = 0;
    S2.sym = -37;
    gotoRowCol(40, 71);
    cout << "Player 2's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cout << " ";
    gotoRowCol(42, 71);
    cin >> S2.PNames;
    S2.Dir = RIGHT;
    S2.RIGHTKEY = 100, S2.LEFTKEY = 97, S2.UPKEY = 119, S2.DOWNKEY = 115;

    S3.size = 3;
  
        S3.score = 0;
    S3.sym = -37;
    gotoRowCol(40, 71);
    cout << "Player 3's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cout << " ";
    gotoRowCol(42, 71);
    cin >> S3.PNames;
    S3.Dir = RIGHT;
    S3.RIGHTKEY = 108, S3.LEFTKEY = 106, S3.UPKEY = 105, S3.DOWNKEY = 107;


    S4.size = 3;
   
        S4.score = 0;
    S4.sym = -37;
    gotoRowCol(40, 71);
    cout << "Player 4's name:";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cout << " ";
    gotoRowCol(42, 71);
    cin >> S4.PNames;
    S4.Dir = RIGHT;
    S4.RIGHTKEY = 104, S4.LEFTKEY = 102, S4.UPKEY = 116, S4.DOWNKEY = 103;
    generateFood(f, h, w, S);
    f.sym = '*';
    generateFood(f2, h, w, S);
    f2.score = 3;
    f2.sym = '*';
}
void displaySnake(const Snake& S, int n)
{
    for (int i = 0; i < S.size; i++)
    {
        if (i == 0)
        {
            SetClr(4);
        }
        else
            SetClr(n);
        gotoRowCol(S.Ps[i].ri, S.Ps[i].ci);
        cout << S.sym;
    }
}
void eraseSnake(const Snake& S)
{
    for (int i = 0; i < S.size; i++)
    {
        gotoRowCol(S.Ps[i].ri, S.Ps[i].ci);
        cout << " ";
    }
}
void MoveSnake(Snake& S, int h, int w)
{
    for (int i = S.size - 1; i > 0; i--)
    {
        S.Ps[i] = S.Ps[i - 1];
    }

    switch (S.Dir)
    {
    case UP:
        S.Ps[0].ri--;
        if (S.Ps[0].ri == -1)
        {            
            S.Ps[0].ri = h - 1;
        }
        break;
    case DOWN:
        S.Ps[0].ri++;
        if (S.Ps[0].ri == h)
        {           
            S.Ps[0].ri = 0;
        }
        break;
    case LEFT:
        S.Ps[0].ci--;
        if (S.Ps[0].ci == -1)
        {
            S.Ps[0].ci = w - 1;
        }
        break;
    case RIGHT:
        S.Ps[0].ci++;
        if (S.Ps[0].ci == w)
        {                      
            S.Ps[0].ci = 0;
        }
        break;
    }
}
void MoveSnake1(Snake& S, int h, int w)
{
    for (int i = S.size - 1; i > 0; i--)
    {
        S.Ps[i] = S.Ps[i - 1];
    }

    switch (S.Dir)
    {
    case UP:
        S.Ps[0].ri--;
        if (S.Ps[0].ri == -1)
        {
           
            break;
            //S.Ps[0].ri = h - 1;
        }
        break;
    case DOWN:
        S.Ps[0].ri++;
        if (S.Ps[0].ri == h)
        {
          
            break;
            //S.Ps[0].ri = 0;
        }
        break;
    case LEFT:
        S.Ps[0].ci--;
        if (S.Ps[0].ci == -1)
        {
           
            break;
            //S.Ps[0].ci = w - 1;
        }
        break;
    case RIGHT:
        S.Ps[0].ci++;
        if (S.Ps[0].ci == w)
        {
           
            break;
            //S.Ps[0].ci = 0;
        }
        break;
    }
}
void MoveSnake2(Snake& S, int h, int w)
{
    for (int i = S.size - 1; i > 0; i--)
    {
        S.Ps[i] = S.Ps[i - 1];
    }

    switch (S.Dir)
    {
    case UP:
        S.Ps[0].ri--;
        if (S.Ps[0].ri == -1 && ((S.Ps[0].ci>=25 && S.Ps[0].ci<=35) || (S.Ps[0].ci>=75 && S.Ps[0].ci<=85)))
        {
            S.Ps[0].ri = h - 1;
        }
        break;
    case DOWN:
        S.Ps[0].ri++;
        if (S.Ps[0].ri == h && ((S.Ps[0].ci >= 25 && S.Ps[0].ci <= 35) || (S.Ps[0].ci >= 75 && S.Ps[0].ci <= 85)))
        {
            S.Ps[0].ri = 0;
        }
        break;
    case LEFT:
        S.Ps[0].ci--;
        if ((S.Ps[0].ri > 25 && S.Ps[0].ri < 35) && S.Ps[0].ci == -1 )
        {                    
            S.Ps[0].ci = w - 1;
        }
        break;
    case RIGHT:
        S.Ps[0].ci++;
        if ((S.Ps[0].ri > 25 && S.Ps[0].ri < 35) && S.Ps[0].ci == w)
        {
            S.Ps[0].ci = 0;
        }
        break;
    }
}
void changeDir(Snake& S, char key)
{
    if (key == S.RIGHTKEY)
    {
        if (S.Dir != LEFT)
            S.Dir = RIGHT;
    }
    if (key == S.LEFTKEY)
    {
        if (S.Dir != RIGHT)
            S.Dir = LEFT;
    }
    if (key == S.UPKEY)
    {
        if (S.Dir != DOWN)
            S.Dir = UP;
    }
    if (key == S.DOWNKEY)
    {
        if (S.Dir != UP)
            S.Dir = DOWN;
    }

}
bool isLegalCoordinate(Position p, Snake& S)
{
    for (int i = 0; i < S.size; i++)
    {
        if ((S.Ps[i].ri == p.ri && S.Ps[i].ci == p.ci)||(p.ri==0 || p.ci==100 || p.ri==60 || p.ci==0))
        {
            return false;
        }
    }
    return true;
}
bool isLegalCoordinate2(Position p, Snake& S)
{
    for (int i = 0; i < S.size; i++)
    {
        if ((S.Ps[i].ri == p.ri && S.Ps[i].ci == p.ci) || (p.ri == 0 || p.ci == 100 || p.ri == 60 || p.ci == 0) || ((p.ri == 25 || p.ri == 35) && (p.ci>=35 && p.ci<=75)))
        {
            return false;
        }
    }
    return true;
}
void generateFood(food& f, int h, int w, Snake& S)
{
    srand(time(0));
    do
    {
        f.fp.ri = rand() % h - 1;
        f.fp.ci = rand() % w - 1;
    } while (!isLegalCoordinate(f.fp, S));
    f.isAlive = true;
    f.score = 1;
}
void displayFood(food f)
{
    gotoRowCol(f.fp.ri, f.fp.ci);
    cout << f.sym;
}
bool FoodIsEaten(Snake& S, food f)
{
    return S.Ps[0].ri == f.fp.ri && S.Ps[0].ci == f.fp.ci;
}
void expandSnake(Snake& S)
{
    Position* Hp = new Position[S.size + 1];
    for (int i = 0; i < S.size; i++)
    {
        Hp[i] = S.Ps[i];
    }
    Hp[S.size] = S.Ps[S.size - 1];
    S.size++;
    delete[] S.Ps;
    S.Ps = Hp; 
}
bool GameOver(Snake& S)
{
    for (int i = 1; i < S.size; i++)
    {
        if (S.Ps[0].ri == S.Ps[i].ri && S.Ps[0].ci == S.Ps[i].ci)
        {
            for (int k = 0; k < S.size; k++)
            {
                S.Ps[k].ri == 65;
                S.Ps[k].ci == 100 - k;
            }
            return true;
        }
    }
    return false;
}
bool GameOver1(Snake& S)
{
    if (S.Ps[0].ri == 0 || S.Ps[0].ci == 0 || S.Ps[0].ri == 59 || S.Ps[0].ci == 99)
    {
        for (int k = 0; k < S.size; k++)
        {
            S.Ps[k].ri == 65;
            S.Ps[k].ci == 100 - k;
        }
        return true;
    }
    for (int i = 1; i < S.size; i++)
    {
        if (S.Ps[0].ri == S.Ps[i].ri && S.Ps[0].ci == S.Ps[i].ci)
        {
            for (int k = 0; k < S.size; k++)
            {
                S.Ps[k].ri == 65;
                S.Ps[k].ci == 100 - k;
            }
            return true;
        }
    }
    return false;
}
bool GameOver2(Snake& S)     
{
    if (((S.Ps[0].ci == 0 || S.Ps[0].ci == 99) && (S.Ps[0].ri > 0 && S.Ps[0].ri <= 25)) || (((S.Ps[0].ci == 0 || S.Ps[0].ci == 99) && (S.Ps[0].ri >= 35 && S.Ps[0].ri < 59)) /*|| S.Ps[0].ri == 0 || S.Ps[0].ri == 59*/) || ((S.Ps[0].ri == 25 || S.Ps[0].ri == 35) && (S.Ps[0].ci >= 35 && S.Ps[0].ci <= 75)))
    {
        for (int k = 0; k < S.size; k++)
        {
            S.Ps[k].ri == 65;
            S.Ps[k].ci == 100 - k;
        }
        return true;
    }
    else if ((S.Ps[0].ri == 0 || S.Ps[0].ri == 59) && ((S.Ps[0].ci >= 0 && S.Ps[0].ci < 25) || (S.Ps[0].ci > 35 && S.Ps[0].ci < 75) || (S.Ps[0].ci > 85 && S.Ps[0].ci <= 99)))
    {
        for (int k = 0; k < S.size; k++)
        {
            S.Ps[k].ri == 65;
            S.Ps[k].ci == 100 - k;
        }
        return true;
    }
    for (int i = 1; i < S.size; i++)
    {
        if (S.Ps[0].ri == S.Ps[i].ri && S.Ps[0].ci == S.Ps[i].ci)
        {
            for (int k = 0; k < S.size; k++)
            {
                S.Ps[k].ri == 65;
                S.Ps[k].ci == 100 - k;
            }
            return true;
        }
    }
    return false;
}


int Level2(Snake& S, int a, int s)
{

    system("cls");
    char sym = -37;
    char ch;
    int h = 60, w = 100;
    //Snake S;
    food f;
    food f2;
    init(S, h, w, f, f2);
    system("cls");
    PrintBoundary1(sym);
    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        cout << "Score: " << S.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
        }

        displaySnake(S,15);
        Sleep(s);
        eraseSnake(S);
        MoveSnake2(S, h, w);
        if (GameOver2(S))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...!!";
            gotoRowCol(61, 0);
            return 0;
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);
        }
    }
}
int Level1(Snake& S, int a, int s)
{

    system("cls");
    char sym = -37;
    PrintBoundary(sym);
    char ch;
    int h=60, w=100;
    //Snake S;
    food f;
    food f2;
    init(S, h, w, f,f2);
    system("cls");
    PrintBoundary(sym);
    displayFood(f);
    while (true)
    {
        
        gotoRowCol(0, 101);
        cout << "Score: " << S.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
        }

        displaySnake(S,15);
        Sleep(s);
        eraseSnake(S);
        MoveSnake1(S, h ,w);
        if (GameOver1(S))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...!!";
            gotoRowCol(61, 0);
            return 0;
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);
           
        }
    }
}
int Level0(Snake& S, int a, int s)
{
    system("cls");
    char sym = -37;
    char ch;
    int h = 60, w = 100;
    //Snake S;
    food f;
    food f2;
    init(S, h, w, f, f2);
    system("cls");
    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        cout << "Score: " << S.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
        }

        displaySnake(S,15);
        Sleep(s);
        eraseSnake(S);
        MoveSnake(S, h, w);
        if (GameOver(S))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...!!";
            gotoRowCol(61, 0);
            return 0;
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);
           
        }
    }
}

int Level0P(Snake& S, Snake& S2, int a, int s)
{
    system("cls");
    char sym = -37;
    char ch;
    int h = 60, w = 100, x = 0, y = 0;
    //Snake S;
    food f;
    food f2;
    init2P(S, S2, h, w, f, f2);
    system("cls");
    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Score: " << S2.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch >= 'a' && ch <= 'z')
            {
                changeDir(S2, ch);
            }
        }
        if (!GameOver(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        SetClr(15);
        Sleep(s);
        if (!GameOver(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver(S))
            MoveSnake(S, h, w);
        if (!GameOver(S2))
            MoveSnake(S2, h, w);
        if (GameOver(S) && x <= 1)
        {
            x++;
            gotoRowCol(30, 120);
            cout << "S1 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S2) && y <= 1)
        {
            y++;
            gotoRowCol(30, 120);
            cout << "S2 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
             if (S.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
             if (S2.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (GameOver(S) && GameOver(S2))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level1P(Snake& S, Snake& S2, int a, int s)
{
    int x = 0, y = 0;
    system("cls");
    char sym = -37;
    PrintBoundary(sym);
    char ch;
    int h = 60, w = 100;
    //Snake S;
    food f;
    food f2;
    init2P(S, S2, h, w, f,f2);
    system("cls");
    PrintBoundary(sym);
    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        cout <<S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout <<S2.score << "'s Score: " << S.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else
            {
                changeDir(S2, ch);
            }
        }

        if (!GameOver1(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver1(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        SetClr(15);
        Sleep(s);
        if (!GameOver1(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver1(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver1(S))
            MoveSnake1(S, h, w);
        if (!GameOver1(S2))
            MoveSnake1(S2, h, w);
        if (GameOver1(S) && x <= 1)
        {
            x++;
            gotoRowCol(30, 120);
            cout << "S1 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S2) && y <= 1)
        {
            y++;
            gotoRowCol(30, 120);
            cout << "S2 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
             if (S.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
             if (S2.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (GameOver1(S) && GameOver1(S2))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level2P(Snake& S, Snake& S2, int a, int s)
{
    int x = 0, y = 0;
    system("cls");
    char sym = -37;
    PrintBoundary1(sym);
    char ch;
    int h = 60, w = 100;
    //Snake S;
    food f;
    food f2;
    init2P(S, S2, h, w, f, f2);
    system("cls");
    PrintBoundary(sym);
    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else
                changeDir(S2, ch);
        }

        if (!GameOver2(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver2(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        SetClr(15);
        Sleep(s);
        if (!GameOver2(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver2(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver2(S))
            MoveSnake2(S, h, w);
        if (!GameOver2(S2))
            MoveSnake2(S2, h, w);
        if (GameOver2(S) && x <= 1)
        {
            x++;
            gotoRowCol(30, 120);
            cout << "S1 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S2) && y <= 1)
        {
            y++;
            gotoRowCol(30, 120);
            cout << "S2 Game Over...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
             if (S.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
             if (S2.score > 5 && a == 2)
             {
                 break;
             }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (GameOver2(S) && GameOver2(S2))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}

int Level0P3(Snake& S, Snake& S2, Snake& S3, int a, int s)
{
    food f; food f2;
    int x = 0, y = 0, z = 0;
    char ch;
    int h = 60, w = 100;
    init3P(S, S2, S3, h, w, f, f2);
    system("cls");
    system("cls");
    char sym = -37;
    //PrintBoundary1(sym);
    //Snake S;
   

    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if(ch=='w'||ch=='a'||ch=='s'||ch=='d')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
        }

        if (!GameOver(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        if (!GameOver(S3))
        {
            SetClr(3);
            displaySnake(S3,3);
        }
        SetClr(15);
        Sleep(50);

///////////////////////////////////////////////

        if (!GameOver(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver(S3) && z <= 1)
            eraseSnake(S3);

///////////////////////////////////////////////

        if (!GameOver(S))
            MoveSnake(S, h, w);
        if (!GameOver(S2))
            MoveSnake(S2, h, w);
        if (!GameOver(S3))
            MoveSnake(S3, h, w);

///////////////////////////////////////////////

        if (GameOver(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
//////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }

//////////////////////////////////////////////////////

        if (GameOver(S) && GameOver(S2) && GameOver(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level1P3(Snake& S, Snake& S2, Snake& S3, int a, int s)
{
    food f; food f2;
    char ch;
    int h = 60, w = 100;
    int x = 0, y = 0, z = 0;
    init3P(S, S2, S3, h, w, f, f2);
    system("cls");
    system("cls");
    char sym = -37;
    PrintBoundary(sym);
   
    //Snake S;
   

    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
        }

        if (!GameOver1(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver1(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        if (!GameOver1(S3))
        {
            SetClr(3);
            displaySnake(S3,3);
        }
        SetClr(15);
        Sleep(50);

        ///////////////////////////////////////////////

        if (!GameOver1(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver1(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver1(S3) && z <= 1)
            eraseSnake(S3);

        ///////////////////////////////////////////////

        if (!GameOver1(S))
            MoveSnake1(S, h, w);
        if (!GameOver1(S2))
            MoveSnake1(S2, h, w);
        if (!GameOver1(S3))
            MoveSnake1(S3, h, w);

        ///////////////////////////////////////////////

        if (GameOver1(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        //////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }

        //////////////////////////////////////////////////////

        if (GameOver1(S) && GameOver1(S2) && GameOver1(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...All Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level2P3(Snake& S, Snake& S2, Snake& S3, int a, int s)
{
    food f; food f2;
    char ch;
    int h = 60, w = 100;
    int x = 0, y = 0, z = 0;
    init3P(S, S2, S3, h, w, f, f2);
    system("cls");
    char sym = -37;
    PrintBoundary1(sym);
    
    //Snake S;

    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
        }

        if (!GameOver2(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver2(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        if (!GameOver2(S3))
        {
            SetClr(3);
            displaySnake(S3,3);
        }
        SetClr(15);
        Sleep(50);

        ///////////////////////////////////////////////

        if (!GameOver2(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver2(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver2(S3) && z <= 1)
            eraseSnake(S3);

        ///////////////////////////////////////////////

        if (!GameOver2(S))
            MoveSnake2(S, h, w);
        if (!GameOver2(S2))
            MoveSnake2(S2, h, w);
        if (!GameOver2(S3))
            MoveSnake2(S3, h, w);

        ///////////////////////////////////////////////

        if (GameOver2(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        //////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }

        //////////////////////////////////////////////////////

        if (GameOver2(S) && GameOver2(S2) && GameOver2(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...All Players Died...!!";
            break;
        }
    }
    return 0;
}

int Level0P4(Snake& S, Snake& S2, Snake& S3, Snake S4, int a, int s)
{
    food f; food f2;
    int x = 0, y = 0, z = 0, q = 0;
    char ch;
    int h = 60, w = 100;
    init4P(S, S2, S3, S4, h, w, f, f2);
    system("cls");
    system("cls");
    char sym = -37;
    //PrintBoundary1(sym);
    //Snake S;


    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        gotoRowCol(9, 101);
        cout << S4.PNames << "'s Scoree: " << S4.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
            else if (ch == 't' || ch == 'f' || ch == 'g' || ch == 'h')
                changeDir(S4, ch);
        }

        if (!GameOver(S))
        {
            SetClr(1);
            displaySnake(S,1);
        }
        if (!GameOver(S2))
        {
            SetClr(2);
            displaySnake(S2,2);
        }
        if (!GameOver(S3))
        {
            SetClr(3);
            displaySnake(S3,3);
        }
        if (!GameOver(S4))
        {
            SetClr(15);
            displaySnake(S4,15);
        }
        SetClr(15);
        Sleep(50);

        ///////////////////////////////////////////////

        if (!GameOver(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver(S3) && z <= 1)
            eraseSnake(S3);
        if (!GameOver(S4) && q <= 1)
            eraseSnake(S4);

        ///////////////////////////////////////////////

        if (!GameOver(S))
            MoveSnake(S, h, w);
        if (!GameOver(S2))
            MoveSnake(S2, h, w);
        if (!GameOver(S3))
            MoveSnake(S3, h, w);
        if (!GameOver(S4))
            MoveSnake(S4, h, w);

        ///////////////////////////////////////////////

        if (GameOver(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver(S4) && q <= 1)
        {
            q++;
            gotoRowCol(9, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        //////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }
        if (FoodIsEaten(S4, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S4.score++;
            if (S4.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S4);

        }

        //////////////////////////////////////////////////////

        if (GameOver(S) && GameOver(S2) && GameOver(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level1P4(Snake& S, Snake& S2, Snake& S3, Snake S4, int a, int s)
{
    food f; food f2;
    int x = 0, y = 0, z = 0, q = 0;
    char ch;
    int h = 60, w = 100;
    init4P(S, S2, S3, S4, h, w, f, f2);
    system("cls");
    system("cls");
    char sym = -37;
    PrintBoundary(sym);
    //Snake S;


    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        gotoRowCol(9, 101);
        cout << S4.PNames << "'s Scoree: " << S3.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
            else if (ch == 't' || ch == 'f' || ch == 'g' || ch == 'h')
                changeDir(S4, ch);
        }

        if (!GameOver1(S))
        {
            SetClr(1);
            displaySnake(S, 1);
        }
        if (!GameOver1(S2))
        {
            SetClr(2);
            displaySnake(S2, 2);
        }
        if (!GameOver1(S3))
        {
            SetClr(3);
            displaySnake(S3, 3);
        }
        if (!GameOver1(S4))
        {
            SetClr(15);
            displaySnake(S4, 15);
        }
        SetClr(15);
        Sleep(50);

        ///////////////////////////////////////////////

        if (!GameOver1(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver1(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver1(S3) && z <= 1)
            eraseSnake(S3);
        if (!GameOver1(S4) && q <= 1)
            eraseSnake(S4);

        ///////////////////////////////////////////////

        if (!GameOver1(S))
            MoveSnake1(S, h, w);
        if (!GameOver1(S2))
            MoveSnake1(S2, h, w);
        if (!GameOver1(S3))
            MoveSnake1(S3, h, w);
        if (!GameOver1(S4))
            MoveSnake1(S4, h, w);

        ///////////////////////////////////////////////

        if (GameOver1(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver1(S4) && q <= 1)
        {
            q++;
            gotoRowCol(9, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        //////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }
        if (FoodIsEaten(S4, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S4.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S4);

        }

        //////////////////////////////////////////////////////

        if (GameOver1(S) && GameOver1(S2) && GameOver1(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}
int Level2P4(Snake& S, Snake& S2, Snake& S3, Snake S4, int a, int s)
{
    food f; food f2;
    int x = 0, y = 0, z = 0, q = 0;
    char ch;
    int h = 60, w = 100;
    init4P(S, S2, S3, S4, h, w, f, f2);
    system("cls");
    char sym = -37;
    PrintBoundary1(sym);
    //Snake S;


    displayFood(f);
    while (true)
    {

        gotoRowCol(0, 101);
        gotoRowCol(0, 101);
        cout << S.PNames << "'s Score: " << S.score;
        gotoRowCol(3, 101);
        cout << S2.PNames << "'s Scoree: " << S2.score;
        gotoRowCol(6, 101);
        cout << S3.PNames << "'s Scoree: " << S3.score;
        gotoRowCol(9, 101);
        cout << S4.PNames << "'s Scoree: " << S3.score;
        if (_kbhit())
        {
            ch = _getch();
            if (ch == -32)
            {
                ch = _getch();
                changeDir(S, ch);
            }
            else if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd')
                changeDir(S2, ch);
            else if (ch == 'i' || ch == 'j' || ch == 'k' || ch == 'l')
                changeDir(S3, ch);
            else if (ch == 't' || ch == 'f' || ch == 'g' || ch == 'h')
                changeDir(S4, ch);
        }

        if (!GameOver2(S))
        {
            SetClr(1);
            displaySnake(S, 1);
        }
        if (!GameOver2(S2))
        {
            SetClr(2);
            displaySnake(S2, 2);
        }
        if (!GameOver2(S3))
        {
            SetClr(3);
            displaySnake(S3, 3);
        }
        if (!GameOver2(S4))
        {
            SetClr(15);
            displaySnake(S4, 15);
        }
        SetClr(15);
        Sleep(50);

        ///////////////////////////////////////////////

        if (!GameOver2(S) && x <= 1)
            eraseSnake(S);
        if (!GameOver2(S2) && y <= 1)
            eraseSnake(S2);
        if (!GameOver2(S3) && z <= 1)
            eraseSnake(S3);
        if (!GameOver2(S4) && q <= 1)
            eraseSnake(S4);

        ///////////////////////////////////////////////

        if (!GameOver2(S))
            MoveSnake2(S, h, w);
        if (!GameOver2(S2))
            MoveSnake2(S2, h, w);
        if (!GameOver2(S3))
            MoveSnake2(S3, h, w);
        if (!GameOver2(S4))
            MoveSnake2(S4, h, w);

        ///////////////////////////////////////////////

        if (GameOver2(S) && x <= 1)
        {
            x++;
            gotoRowCol(0, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S2) && y <= 1)
        {
            y++;
            gotoRowCol(3, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S3) && z <= 1)
        {
            z++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        else if (GameOver2(S4) && q <= 1)
        {
            q++;
            gotoRowCol(6, 115);
            cout << "Snake is dead...!!";
            gotoRowCol(61, 0);
            /*return 0;*/
        }
        //////////////////////////////////////////////////

        if (FoodIsEaten(S, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S.score++;
            if (S.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S);

        }
        if (FoodIsEaten(S2, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S2.score++;
            if (S2.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S2);

        }
        if (FoodIsEaten(S3, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S3.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S3);

        }
        if (FoodIsEaten(S4, f))
        {
            PlaySound(TEXT("coin"), NULL, SND_SYNC);
            S4.score++;
            if (S3.score > 5 && a == 2)
            {
                break;
            }
            generateFood(f, h, w, S);
            displayFood(f);
            expandSnake(S4);

        }

        //////////////////////////////////////////////////////

        if (GameOver2(S) && GameOver2(S2) && GameOver2(S3))
        {
            gotoRowCol(30, 120);
            cout << "Game Over...Both Players Died...!!";
            break;
        }
    }
    return 0;
}


int main03(int x, Snake& S, Snake& S2, Snake& S3, Snake& S4, int a, int s)
{
    system("cls");
    int y;
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    SetClr(15);
    gotoRowCol(40, 71);
    cout << "Enter Level number (1-3):";
    gotoRowCol(43, 71);
    cout << "________________________";
    gotoRowCol(42, 71);
    cin >> y;
    switch (y)
    {
    case 1:
        if (x == 1)
        {
            Level0(S, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 2)
        {
            Level0P(S,S2,a,s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 3)
        {
            Level0P3(S, S2, S3, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 4)
        {
            Level0P4(S, S2, S3, S4, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
    case 2:
        if (x == 1)
        {
            Level1(S, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 2)
        {
            Level1P(S, S2, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 3)
        {
            Level1P3(S, S2, S3, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 4)
        {
            Level1P4(S, S2, S3, S4, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
    case 3:
        if (x == 1)
        {
            Level2(S, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 2)
        {
            Level2P(S, S2, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 3)
        {
            Level2P3(S, S2, S3, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        else if (x == 4)
        {
            Level2P4(S, S2, S3, S4, a, s);
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
    }
    return 0;
}
int main1(int x)
{
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    Snake S;
    Snake S2;
    Snake S3;
    Snake S4;
    Position P1;
    Position P2;
    int a, s;
    gotoRowCol(30, 71);
    cout << "____Select Game Level____";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 77);
    cout << "Duniya Gol Hai";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Level By Level";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Custom Level";
    do
    {
        getRowColbyLeftClick(P1.ri, P1.ci);
        if (DuniyaGolHai(P1))
        {
            a = 1;
        }
        if (LevelByLevel(P1))
        {
            a = 2;
        }
        if (CustomLevel(P1))
        {
            a = 3;
        }
    } while (!DuniyaGolHai(P1) && !LevelByLevel(P1) && !CustomLevel(P1));


    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    gotoRowCol(30, 71);
    cout << "____Select Game Difficulty____";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    gotoRowCol(44, 77);
    SetClr(15);
    cout << "Easy";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Medium";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    gotoRowCol(54, 77);
    SetClr(15);
    cout << "Hard";
    do
    {
        getRowColbyLeftClick(P2.ri, P2.ci);
        if (Easy(P2))
        {
            s = 100;
        }
        if (Medium(P2))
        {
            s = 50;
        }
        if (Hard(P2))
        {
            s = 10;
        }
    } while (!Easy(P2) && !Medium(P2) && !Hard(P2));



    switch (a)
    {
    case 1:
        Level0(S, a, s);
        PlaySound(TEXT("game_over"), NULL, SND_SYNC);
        break;
    case 2:
        Level0(S, a, s);
        if (GameOver(S))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level1(S, a, s);
        if (GameOver1(S))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level2(S, a, s);
        if (GameOver2(S))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
    case 3:
        main03(x,S,S2,S3,S4,a,s);
        break;
    }
    return 0;
}
int main2(int x)
{
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    Snake S;
    Snake S2;
    Snake S3;
    Snake S4;
    Position P;
    Position P2;
    int a, s;
    gotoRowCol(30, 71);
    cout << "____Select Game Level____";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 77);
    cout << "Duniya Gol Hai";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Level By Level";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Custom Level";
    do
    {
        getRowColbyLeftClick(P.ri, P.ci);
        if (DuniyaGolHai(P))
        {
            a = 1;
        }
        if (LevelByLevel(P))
        {
            a = 2;
        }
        if (CustomLevel(P))
        {
            a = 3;
        }
    } while (!DuniyaGolHai(P) && !LevelByLevel(P) && !CustomLevel(P));


    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    gotoRowCol(30, 71);
    cout << "____Select Game Difficulty____";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    gotoRowCol(44, 77);
    SetClr(15);
    cout << "Easy";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Medium";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Hard";
    do
    {
        getRowColbyLeftClick(P2.ri, P2.ci);
        if (Easy(P2))
        {
            s = 100;
        }
        if (Medium(P2))
        {
            s = 50;
        }
        if (Hard(P2))
        {
            s = 10;
        }
    } while (!Easy(P2) && !Medium(P2) && !Hard(P2));

    if (s == 1)
    {
        s = 100;
    }
    else if (s == 2)
    {
        s = 50;
    }
    else if (s == 3)
    {
        s = 10;
    }
    switch (a)
    {
    case 1:
        Level0P(S, S2, a, s);
        PlaySound(TEXT("game_over"), NULL, SND_SYNC);
        break;
    case 2:
        Level0P(S, S2, a, s);
        if (GameOver(S) && GameOver(S2))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level1P(S, S2, a, s);
        if (GameOver1(S) && GameOver1(S2))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level2P(S, S2, a, s);
        if (GameOver2(S) && GameOver2(S2))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        break;
    case 3:
        main03(x, S, S2,S3,S4, a, s);
    }
    return 0;
}
int main3(int x)
{
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    Snake S;
    Snake S2;
    Snake S3;
    Snake S4;
    Position P;
    Position P2;
    int a, s;
    gotoRowCol(30, 71);
    cout << "____Select Game Level____";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 77);
    cout << "Duniya Gol Hai";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Level By Level";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Custom Level";
    do
    {
        getRowColbyLeftClick(P.ri, P.ci);
        if (DuniyaGolHai(P))
        {
            a = 1;
        }
        if (LevelByLevel(P))
        {
            a = 2;
        }
        if (CustomLevel(P))
        {
            a = 3;
        }
    } while (!DuniyaGolHai(P) && !LevelByLevel(P) && !CustomLevel(P));


    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    gotoRowCol(30, 71);
    cout << "____Select Game Difficulty____";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    gotoRowCol(44, 77);
    SetClr(15);
    cout << "Easy";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Medium";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Hard";
    do
    {
        getRowColbyLeftClick(P2.ri, P2.ci);
        if (Easy(P2))
        {
            s = 100;
        }
        if (Medium(P2))
        {
            s = 50;
        }
        if (Hard(P2))
        {
            s = 10;
        }
    } while (!Easy(P2) && !Medium(P2) && !Hard(P2));

    if (s == 1)
    {
        s = 100;
    }
    else if (s == 2)
    {
        s = 50;
    }
    else if (s == 3)
    {
        s = 10;
    }
    switch (a)
    {
    case 1:
        Level0P3(S, S2, S3, a, s);
        PlaySound(TEXT("game_over"), NULL, SND_SYNC);
        break;
    case 2:
        Level0P3(S, S2, S3, a, s);
        if (GameOver(S) && GameOver(S2) && GameOver(S3))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level1P3(S, S2, S3, a, s);
        if (GameOver1(S) && GameOver1(S2) && GameOver(S3))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level2P3(S, S2, S3, a, s);
        if (GameOver2(S) && GameOver2(S2) && GameOver(S3))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        break;
    case 3:
        main03(x, S, S2,S3,S4, a, s);
    }
    return 0;
}
int main4(int x)
{
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    Snake S;
    Snake S2;
    Snake S3;
    Snake S4;
    Position P;
    Position P2;
    int a, s;
    gotoRowCol(30, 71);
    cout << "____Select Game Level____";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 77);
    cout << "Duniya Gol Hai";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Level By Level";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Custom Level";
    do
    {
        getRowColbyLeftClick(P.ri, P.ci);
        if (DuniyaGolHai(P))
        {
            a = 1;
        }
        if (LevelByLevel(P))
        {
            a = 2;
        }
        if (CustomLevel(P))
        {
            a = 3;
        }
    } while (!DuniyaGolHai(P) && !LevelByLevel(P) && !CustomLevel(P));


    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    gotoRowCol(30, 71);
    cout << "____Select Game Difficulty____";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(43 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    gotoRowCol(44, 77);
    SetClr(15);
    cout << "Easy";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(48 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(49, 77);
    cout << "Medium";
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 8)
            {
                SetClr(4);
                gotoRowCol(53 + i, 75 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(54, 77);
    cout << "Hard";
    do
    {
        getRowColbyLeftClick(P2.ri, P2.ci);
        if (Easy(P2))
        {
            s = 100;
        }
        if (Medium(P2))
        {
            s = 50;
        }
        if (Hard(P2))
        {
            s = 10;
        }
    } while (!Easy(P2) && !Medium(P2) && !Hard(P2));

    if (s == 1)
    {
        s = 100;
    }
    else if (s == 2)
    {
        s = 50;
    }
    else if (s == 3)
    {
        s = 10;
    }
    switch (a)
    {
    case 1:
        Level0P4(S, S2, S3, S4, a, s);
        PlaySound(TEXT("game_over"), NULL, SND_SYNC);
        break;
    case 2:
        Level0P4(S, S2, S3, S4, a, s);
        if (GameOver(S) && GameOver(S2) && GameOver(S3) && GameOver(S4))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level1P4(S, S2, S3, S4, a, s);
        if (GameOver1(S) && GameOver1(S2) && GameOver(S3) && GameOver1(S4))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        Level2P4(S, S2, S3, S4, a, s);
        if (GameOver2(S) && GameOver2(S2) && GameOver(S3) && GameOver2(S4))
        {
            PlaySound(TEXT("game_over"), NULL, SND_SYNC);
            break;
        }
        break;
    case 3:
        main03(x, S, S2, S3, S4, a, s);
    }
    return 0;
}


void main01(int x)
{
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    int a;
    SetClr(15);
    gotoRowCol(40, 71);
    cout << "Enter number of players:";
    gotoRowCol(43, 71);
    cout << "________________________";
    do
    {
        
        gotoRowCol(42, 71);
        cin >> a;
        gotoRowCol(45, 71);
        cout << "                          ";
        if (a >= 2)
        {
            switch (a)
            {
            case 2:
                main2(x);
                break;
            case 3:
                main3(x);
                break;
            case 4:
                main4(x);
            }
        }
        else
        {
            gotoRowCol(42, 71);
            cout << " ";
            gotoRowCol(45, 71);
            cout << "____invalid input____";
        }
    } while (a < 2);
}
void main0()
{
    int x;
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    SetClr(15);
    gotoRowCol(30, 71);
    cout << "____Choose game mode____";
    //single Player multi-Player
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 60 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 62);
    cout << "Single Player";

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            if (i == 0 || i == 2 || j == 0 || j == 16)
            {
                SetClr(4);
                gotoRowCol(43 + i, 90 + j);
                cout << char(-37);
            }
        }
    }
    SetClr(15);
    gotoRowCol(44, 92);
    cout << "Multi-Player";
    Position P;
    do
    {
        getRowColbyLeftClick(P.ri, P.ci);
        if (SinglePlayer(P))
        {
            x = 1;
            main1(x);
        }
        if (MultiPlayer(P))
        {
            x = 2;
            main01(x);
        }
    } while (SinglePlayer(P) || MultiPlayer(P));
}
int main()
{
    Position a;
    getRowColbyLeftClick(a.ri, a.ci);
    system("cls");
    for (int i = 0; i < 87; i++)
    {
        for (int j = 0; j < 168; j++)
        {
            if (i == 0 || i == 86 || j == 0 || j == 167)
            {
                SetClr(4);
                cout << '/';
            }
            else
                cout << " ";
        }
    }
    gotoRowCol(15, 50 + 10);
    cout << "//////";
    gotoRowCol(16, 50 + 10);
    cout << "//";
    gotoRowCol(17, 50 + 10);
    cout << "//";
    gotoRowCol(18, 50 + 10);
    cout << "//////";
    gotoRowCol(19, 54 + 10);
    cout << "//";
    gotoRowCol(20, 54 + 10);
    cout << "//";
    gotoRowCol(21, 50 + 10);
    cout << "//////";

    gotoRowCol(15, 58 + 10);
    cout << "///      //";
    gotoRowCol(16, 58 + 10);
    cout << "// /     //";
    gotoRowCol(17, 58 + 10);
    cout << "//  /    //";
    gotoRowCol(18, 58 + 10);
    cout << "//   /   //";
    gotoRowCol(19, 58 + 10);
    cout << "//    /  //";
    gotoRowCol(20, 58 + 10);
    cout << "//     / //";
    gotoRowCol(21, 58 + 10);
    cout << "//      ///";

    gotoRowCol(15, 71 + 10);
    cout << "//////";
    gotoRowCol(16, 71 + 10);
    cout << "//  //";
    gotoRowCol(17, 71 + 10);
    cout << "//  //";
    gotoRowCol(18, 71 + 10);
    cout << "//////";
    gotoRowCol(19, 71 + 10);
    cout << "//  //";
    gotoRowCol(20, 71 + 10);
    cout << "//  //";
    gotoRowCol(21, 71 + 10);
    cout << "//  //";

    gotoRowCol(15, 79 + 10);
    cout << "//   //";
    gotoRowCol(16, 79 + 10);
    cout << "//  //";
    gotoRowCol(17, 79 + 10);
    cout << "// //";
    gotoRowCol(18, 79 + 10);
    cout << "////";
    gotoRowCol(19, 79 + 10);
    cout << "// //";
    gotoRowCol(20, 79 + 10);
    cout << "//  //";
    gotoRowCol(21, 79 + 10);
    cout << "//   //";

    gotoRowCol(15, 88 + 10);
    cout << "//////";
    gotoRowCol(16, 88 + 10);
    cout << "//";
    gotoRowCol(17, 88 + 10);
    cout << "//";
    gotoRowCol(18, 88 + 10);
    cout << "//////";
    gotoRowCol(19, 88 + 10);
    cout << "//";
    gotoRowCol(20, 88 + 10);
    cout << "//";
    gotoRowCol(21, 88 + 10);
    cout << "//////";

    /////////////////////////////

    gotoRowCol(24, 63);
    cout << "////////";
    gotoRowCol(25, 63);
    cout << "//";
    gotoRowCol(26, 63);
    cout << "//";
    gotoRowCol(27, 63);
    cout << "//  ////";
    gotoRowCol(28, 63);
    cout << "//    //";
    gotoRowCol(29, 63);
    cout << "//    //";
    gotoRowCol(30, 63);
    cout << "////////";

    gotoRowCol(24, 73);
    cout << "//////";
    gotoRowCol(25, 73);
    cout << "//  //";
    gotoRowCol(26, 73);
    cout << "//  //";
    gotoRowCol(27, 73);
    cout << "//////";
    gotoRowCol(28, 73);
    cout << "//  //";
    gotoRowCol(29, 73);
    cout << "//  //";
    gotoRowCol(30, 73);
    cout << "//  //";

    gotoRowCol(24, 81);
    cout << "//\\      ///";
    gotoRowCol(25, 81);
    cout << "// \\    / //";
    gotoRowCol(26, 81);
    cout << "//  \\  /  //";
    gotoRowCol(27, 81);
    cout << "//   \\/   //";
    gotoRowCol(28, 81);
    cout << "//        //";
    gotoRowCol(29, 81);
    cout << "//        //";
    gotoRowCol(30, 81);
    cout << "//        //";

    gotoRowCol(24, 95);
    cout << "//////";
    gotoRowCol(25, 95);
    cout << "//";
    gotoRowCol(26, 95);
    cout << "//";
    gotoRowCol(27, 95);
    cout << "//////";
    gotoRowCol(28, 95);
    cout << "//";
    gotoRowCol(29, 95);
    cout << "//";
    gotoRowCol(30, 95);
    cout << "//////";

    while (true)
    {
        PlaySound(TEXT("Start"), NULL, SND_SYNC);

        gotoRowCol(40, 70);
        cout << "Press enter to continue...";
        if (_kbhit)
        {

            char ch = _getch();

            if (ch == 13)
            {
                main0();
                gotoRowCol(87, 0);
                break;
            }
        }
        gotoRowCol(40, 70);
        cout << "                             ";
        Sleep(500);
    }
    return _getch();
}