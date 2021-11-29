#include "extend.h"
#include <iostream>
#include <cstdlib> // Random
#include "graphics.h"

using namespace std;

int BotSelectCell(LargeBoard boards)
{
    int current_board = boards.board_num;
    int temp;
    while (1)
    {
        while (1)
        {
            temp = rand() % 10;
            if (temp != 9)
                break;
        }
        if (boards.boards[current_board / 3][current_board % 3].board[temp / 3][temp % 3] == Piece_BLANK)
            break;
    }
    return ++temp;
}

int BotSelectBoard(LargeBoard boards)
{
    int current_board = boards.board_num;
    int temp;
    while (1)
    {
        while (1)
        {
            temp = rand() % 10;
            if (temp != 9)
                break;
        }
        if (boards.boards[current_board / 3][current_board % 3].GetStatus() == NONE)
            break;
    }
    return ++temp;
}

int EvaluateValue(SmallBoard board)
{
    switch (board.CheckWin())
    {
    case X:
        return -10;
    case O:
        return 10;
    default:
        return 0;
    }
}

int FindBestMove(LargeBoard boards)
{
    int current_board = boards.board_num;
    int bestMove = 0;
    int moveVal;

    /* Fill X in each cell one by one. Then check win this turn */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.boards[current_board / 3][current_board % 3].board[i][j] == Piece_BLANK)
            {
                boards.boards[current_board / 3][current_board % 3].board[i][j] = Piece_X;
                moveVal = EvaluateValue(boards.boards[current_board / 3][current_board % 3]);
                boards.boards[current_board / 3][current_board % 3].board[i][j] = Piece_BLANK;
                if (moveVal == -10)
                {
                    bestMove = 3 * i + j + 1;
                }
            }
        }
    }

    /**     Win more priority Prevent    **/

    /* Fill O in each cell one by one. Then check win this turn */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.boards[current_board / 3][current_board % 3].board[i][j] == Piece_BLANK)
            {
                boards.boards[current_board / 3][current_board % 3].board[i][j] = Piece_O;
                moveVal = EvaluateValue(boards.boards[current_board / 3][current_board % 3]);
                boards.boards[current_board / 3][current_board % 3].board[i][j] = Piece_BLANK;
                if (moveVal == 10)
                {
                    bestMove = 3 * i + j + 1;
                }
            }
        }
    }

    if (bestMove == 0)
    {
        return BotSelectCell(boards);
    }
    return bestMove;
}

int InputData()
{
    char data;
    while (1)
    {
        cin >> data;
        if ((int)data <= 57 && (int)data >= 48)
            break;
        Goto_xy(7, 22);
        cout << "Re-Enter: ";
    }
    return (int)data - 48;
}