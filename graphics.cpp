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

void Information(LargeBoard *boards)
{
    int i;
    Goto_xy(xBoardInfor, yBoardInfor);
    cout << " ____________________________________________________";
    for (i = yBoardInfor + 1; i < hBoardInfor; i++)
    {
        Goto_xy(xBoardInfor, i);
        cout << "|                                                    |";
    }
    Goto_xy(xBoardInfor, i);
    cout << "|____________________________________________________|";
    Infor_LargeBoard(boards);

    Goto_xy(xBoardInfor + 23, yBoardInfor + 2);
    Set_colorText(yellow);
    cout << "ULTIMATE TIC TAC TOE";

    Goto_xy(xBoardInfor + 2, hBoardInfor - 4);
    Set_colorText(green);
    cout << "* NOTE *";
    Set_colorText(white);

    Goto_xy(xBoardInfor + 1, hBoardInfor - 3);
    cout << "- Only 1 character from the keyboard is allowed";
    Goto_xy(xBoardInfor + 1, hBoardInfor - 2);
    cout << "- Input: Cell = '0' - Go back to your previous turn";
    Goto_xy(xBoardInfor + 1, hBoardInfor - 1);
    cout << "         Cell = 'r' - Exit Game";

    Goto_xy(0, 0);
}

void Infor_LargeBoard(LargeBoard *boards)
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
        Goto_xy(xBoardInfor - 1, yBoardInfor + 2 * i);
        cout << "+---+---+---+";
        Goto_xy(xBoardInfor - 1, yBoardInfor + 1 + 2 * i);
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            if (temp[3 * i + j] == X || temp[3 * i + j] == O || temp[3 * i + j] == TIE)
            {
                Set_colorText(yellow);
                cout << temp[3 * i + j];
                Set_colorText(white);
                cout << " | ";
            }
            else
            {
                Set_colorText(green);
                cout << temp[3 * i + j];
                Set_colorText(white);
                cout << " | ";
            }
        }
    }
    Goto_xy(xBoardInfor - 1, yBoardInfor + 6);
    cout << "+---+---+---+";
}

void Draw_select(int board_num)
{
    Set_colorText(yellow);
    int i;
    int _x = 6 + 11 * (board_num % 3);
    int _y = 1 + 5 * (board_num / 3);
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
    Set_colorText(white);
}

void Set_colorText(Colors _color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, _color);
}
