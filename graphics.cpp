#include <iostream>
#include <windows.h>
#include "graphics.h"
#include "ultimate_tic_tac_toe.h"

void Clear_Screen()
{
    system("cls");
}

void Goto_xy(int _x, int _y)
{
    HANDLE h;
    COORD Position;
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    Position.X = _x;
    Position.Y = _y;
    SetConsoleCursorPosition(h, Position);
}

void Information()
{
    int i;
    Clear_Screen();
    Goto_xy(50, 1);
    cout << " ___________________________________________________";
    for (i = 2; i < 15; i++)
    {
        Goto_xy(50, i);
        cout << "|                                                   |";
    }
    Goto_xy(50, i);
    cout << "|___________________________________________________|";
    Infor_LargeBoard();

    Goto_xy(70, 3);
    cout << "ULTIMATE TIC TAC TOE";
    Goto_xy(0, 0);
}

void Infor_LargeBoard()
{
    Goto_xy(50, 1);
    cout << "+---+---+---+";
    Goto_xy(50, 2);
    cout << "| "
         << "1"
         << " | "
         << "2"
         << " | "
         << "3"
         << " | ";
    Goto_xy(50, 3);
    cout << "+---+---+---+";
    Goto_xy(50, 4);
    cout << "| "
         << "4"
         << " | "
         << "5"
         << " | "
         << "6"
         << " | ";
    Goto_xy(50, 5);
    cout << "+---+---+---+";
    Goto_xy(50, 6);
    cout << "| "
         << "7"
         << " | "
         << "8"
         << " | "
         << "9"
         << " | ";
    Goto_xy(50, 7);
    cout << "+---+---+---+";
}
