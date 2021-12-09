#include <windows.h>
#include "graphics.h"
#include "player_infor.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

/* Pointer to player in the vector list */
extern CPlayerInfor *pPlayer[2];

/* Clear Screen */
void ClearScreen()
{
    system("cls");
}

/* Set coordinate of a text pointer */
void GotoXY(int _x, int _y)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = _x;
    Position.Y = _y;
    SetConsoleCursorPosition(h, Position);
}

/* Set color for text  */
void SetColorText(eColors color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
}

/* Display information board */
void Information(CLargeBoard boards)
{
    int i;
    GotoXY(xBoardInfor, yBoardInfor);
    cout << " ____________________________________________________";
    for (i = yBoardInfor + 1; i < hBoardInfor; i++)
    {
        GotoXY(xBoardInfor, i);
        cout << "|                                                    |";
    }
    GotoXY(xBoardInfor, i);
    cout << "|____________________________________________________|";
    InforStatusLargeBoard(boards);

    GotoXY(xBoardInfor + 23, yBoardInfor + 2);
    SetColorText(yellow);
    cout << "ULTIMATE TIC TAC TOE";

    DisplayBoardsMode(boards);
    DisplayCurrPlayer(boards);

    GotoXY(xBoardInfor + 2, hBoardInfor - 4);
    SetColorText(green);
    cout << "* NOTE *";
    SetColorText(white);

    GotoXY(xBoardInfor + 1, hBoardInfor - 3);
    cout << "- Only 1 character from the keyboard is allowed";
    GotoXY(xBoardInfor + 1, hBoardInfor - 2);
    cout << "- Input: Cell = '0' - Go back to your previous turn";
    GotoXY(xBoardInfor + 1, hBoardInfor - 1);
    cout << "         Cell = 'r' - Exit Game & Lost";

    GotoXY(0, 0);
}

/* Display Large Board Status */
void InforStatusLargeBoard(CLargeBoard boards)
{
    char temp[9]; // ASCII of '1' -> '9' or 'X' or 'O' or '='
    for (int i = 0; i < 9; i++)
    {
        if (boards.m_boardStatuses[i / 3][i % 3] == NONE)
            temp[i] = i + 1 + 48;
        else
            temp[i] = boards.m_boardStatuses[i / 3][i % 3];
    }

    for (int i = 0; i < 3; i++)
    {
        GotoXY(xBoardInfor - 1, yBoardInfor + 2 * i);
        cout << "+---+---+---+";
        GotoXY(xBoardInfor - 1, yBoardInfor + 1 + 2 * i);
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            if (temp[3 * i + j] == X || temp[3 * i + j] == O || temp[3 * i + j] == TIE)
            {
                SetColorText(yellow);
                cout << temp[3 * i + j];
                SetColorText(white);
                cout << " | ";
            }
            else
            {
                SetColorText(green);
                cout << temp[3 * i + j];
                SetColorText(white);
                cout << " | ";
            }
        }
    }
    GotoXY(xBoardInfor - 1, yBoardInfor + 6);
    cout << "+---+---+---+";
}

/* Display specify the current table */
void DrawSelect(int _boardNum)
{
    SetColorText(yellow);
    int i;
    int _x = 6 + 11 * (_boardNum % 3);
    int _y = 1 + 5 * (_boardNum / 3);
    GotoXY(_x, _y);
    cout << " _______ ";
    for (i = 1; i < 4; i++)
    {
        GotoXY(_x, _y + i);
        cout << "|";
        GotoXY(_x + 8, _y + i);
        cout << "|";
    }
    GotoXY(_x, _y + i);
    cout << "|_______|";
    SetColorText(white);
}

/* Display interface a Large Board */
void DrawBoards(CLargeBoard boards)
{
    int tempBoardNum = boards.m_boardNum;
    ClearScreen();
    cout << "\n\n";
    for (int w = 0; w < 3; w++)
    {
        for (int x = 0; x < 3; x++)
        {
            cout << "\t";
            for (int y = 0; y < 3; y++)
            {
                for (int z = 0; z < 3; z++)
                {
                    ePiece player = boards.m_boards[w][y].m_board[x][z];
                    cout << (char)player << " ";
                }
                cout << "     ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }

    /* Display board graphic before	being taken or finish match */
    if (tempBoardNum == -1 || boards.CheckWin() != NONE)
        Information(boards);

    /* Display board graphic after being taken */
    else
    {
        Information(boards);
        if (boards.m_boardStatuses[tempBoardNum / 3][tempBoardNum % 3] == NONE)
            DrawSelect(tempBoardNum);
    }
}

/*  Display name of current player */
void DisplayCurrPlayer(CLargeBoard boards)
{
    SetColorText(green);
    GotoXY(xBoardInfor + 2, hBoardInfor - 5);
    cout << "* Current Turn: ";
    SetColorText(white);
    switch (boards.m_mode)
    {
    case Friend:
        switch (boards.GetTurn())
        {
        case X:
            cout << pPlayer[0]->m_name;
            break;

        case O:
            cout << pPlayer[1]->m_name;
            break;
        }
        break;

    default:
        switch (boards.GetTurn())
        {
        case X:
            cout << pPlayer[0]->m_name;
            break;
        case O:
            cout << "BOT";
            break;
        }
        break;
    }
}

/* Display mode of large board */
void DisplayBoardsMode(CLargeBoard boards)
{
    SetColorText(green);
    GotoXY(xBoardInfor + 2, hBoardInfor - 6);
    cout << "* Play with: ";
    SetColorText(white);
    switch (boards.m_mode)
    {
    case Friend:
        cout << "FRIEND";
        break;

    case BotEasy:
        cout << "BOT EASY";
        break;
    case BotNormal:
        cout << "BOT NORMAL";
        break;
    case BotHard:
        cout << "BOT HARD";
        break;
    }
}
