#include <iostream>
#include <windows.h>
#include "graphics.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

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

void Information(LargeBoard* boards)
{
    int i;
    Clear_Screen();
    Goto_xy(coord_X_Infor, 1);
    cout << " ____________________________________________________";
    for (i = 2; i < 15; i++)
    {
        Goto_xy(coord_X_Infor, i);
        cout << "|                                                    |";
    }
    Goto_xy(coord_X_Infor, i);
    cout << "|____________________________________________________|";
    Infor_LargeBoard(boards);

    Goto_xy(coord_X_Infor + 23, 3);
    cout << "ULTIMATE TIC TAC TOE";

    Goto_xy(coord_X_Infor + 2, 10);
    cout << "* NOTE *";
    Goto_xy(coord_X_Infor + 1, 12);
    cout << "- Only 1 character from the keyboard is allowed";
    Goto_xy(coord_X_Infor + 1, 13);
    cout << "- Input: Cell = '0' - Go back to your previous turn";
    Goto_xy(coord_X_Infor + 1, 14);
    cout << "         Cell = 'r' - Exit Game";

    Goto_xy(0, 0);
}

void Infor_LargeBoard(LargeBoard* boards)
{
    char temp[9];
    for (int i = 0; i < 9; i++)
    {
        if (boards->boardStatuses[i / 3][i % 3] == NONE)
            temp[i] = i + 1 + 48;
        else
            temp[i] = boards->boardStatuses[i / 3][i % 3];
    }

    for (int i = 0; i < 3; i++)
    {
        Goto_xy(coord_X_Infor, 1 + 2 * i);
        cout << "+---+---+---+";
        Goto_xy(coord_X_Infor, 2 + 2 * i);
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            Set_colorText(green);
            cout << temp[3 * i + j ];
            Set_colorText(white);
            cout << " | ";
        }
    }
    Goto_xy(coord_X_Infor, 7);
    cout << "+---+---+---+";
}

void Draw_select(int board_num)
{
    int i;
    int _x = 6 + 16 * (board_num % 3);
    int _y = 0 + 6 * (board_num / 3);
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
