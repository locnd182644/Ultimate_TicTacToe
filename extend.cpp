#include "extend.h"
#include <cstdlib> // Random

using namespace std;

int BotSelectCell(Large_Board boards)
{
    int current_board = boards._board_num;
    int temp;
    while (1)
    {
        while (1)
        {
            temp = rand() % 10;
            if (temp != 9)
                break;
        }
        if (boards._boards[current_board / 3][current_board % 3]._board[temp / 3][temp % 3] == Piece_BLANK)
            break;
    }
    return ++temp;
}

int BotSelectBoard(Large_Board boards)
{
    int current_board = boards._board_num;
    int temp;
    while (1)
    {
        while (1)
        {
            temp = rand() % 10;
            if (temp != 9)
                break;
        }
        if (boards._boards[current_board / 3][current_board % 3].GetStatus() == NONE)
            break;
    }
    return ++temp;
}

int EvaluateValue(Small_Board board)
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

int FindBestMove(Large_Board boards)
{
    int current_board = boards._board_num;
    int bestMove = 0;
    int moveVal;

    /* Fill X in each cell one by one. Then check win this turn */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards._boards[current_board / 3][current_board % 3]._board[i][j] == Piece_BLANK)
            {
                boards._boards[current_board / 3][current_board % 3]._board[i][j] = Piece_X;
                moveVal = EvaluateValue(boards._boards[current_board / 3][current_board % 3]);
                boards._boards[current_board / 3][current_board % 3]._board[i][j] = Piece_BLANK;
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
            if (boards._boards[current_board / 3][current_board % 3]._board[i][j] == Piece_BLANK)
            {
                boards._boards[current_board / 3][current_board % 3]._board[i][j] = Piece_O;
                moveVal = EvaluateValue(boards._boards[current_board / 3][current_board % 3]);
                boards._boards[current_board / 3][current_board % 3]._board[i][j] = Piece_BLANK;
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
