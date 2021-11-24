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
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
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

void Draw_select(int _board_num)
{
    int i;
    int _x = 6 + 16 * (_board_num % 3);  
    int _y = 0 + 6 * (_board_num / 3);
    Goto_xy(_x, _y);
    cout << " _______ ";
    for (i = 1; i < 4; i++)
    {
        Goto_xy(_x, _y + i);
        cout << "|";
        Goto_xy(_x + 8, _y + i);
        cout << "|";
    }
    Goto_xy(_x, _y + i);
    cout << "|_______|";
}

void Set_colorText(Colors _color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, _color);
}