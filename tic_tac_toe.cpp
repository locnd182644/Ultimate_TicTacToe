#include <iostream>
#include "tic_tac_toe.h"

using namespace std;

SmallBoard::SmallBoard()
{
    InitBoard();
    _gameStatus = NONE;
}

void SmallBoard::InitBoard()
{
    /* For all BLANK */
    for (int x = 0; x < 3; ++x)
        for (int y = 0; y < 3; ++y)
            board[x][y] = Piece_BLANK;
}

Status SmallBoard::GetStatus()
{
    return _gameStatus;
}

bool SmallBoard::Fill(int cell, Piece _turn)
{
    /* Player grid is display from 1 
     * So 1 must be subtracted for the 
     * Correct index */
    cell = cell - 1;
    if (board[cell / 3][cell % 3] == Piece_BLANK)
    {
        board[cell / 3][cell % 3] = _turn;
        return true;
    }
    return false; // Cell already occupied
}

Status SmallBoard::CheckWin()
{
    bool tie = true;
    /* Check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == Piece_BLANK)
                tie = false;

    if (tie)
    {
        _gameStatus = TIE;
        return TIE;
    }

    /* Top-left to bottom-right */
    if (board[0][0] != Piece_BLANK &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
    {
        _gameStatus = board[0][0] == Piece_X ? X : O;
        return _gameStatus; // Return winner
    }

    /* Top-right to bottom-left */
    if (board[0][2] != Piece_BLANK &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
    {
        _gameStatus = board[0][2] == Piece_X ? X : O;
        return _gameStatus; // Return winner
    }

    /* COLUMNS */
    for (int column = 0; column < 3; column++)
    {
        if (board[0][column] == board[1][column] &&
            board[0][column] != Piece_BLANK &&
            board[1][column] == board[2][column])
        {
            _gameStatus = board[0][column] == Piece_X ? X : O;
            return _gameStatus; // Return winner
        }
    }

    /* ROWS */
    for (int row = 0; row < 3; row++)
    {
        if (board[row][0] != Piece_BLANK &&
            board[row][0] == board[row][1] &&
            board[row][1] == board[row][2])
        {
            _gameStatus = board[row][0] == Piece_X ? X : O;
            return _gameStatus; // Return winner
        }
    }
    return NONE; // No one has won yet
}
