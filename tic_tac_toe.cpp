#include <iostream>
#include "tic_tac_toe.h"

using namespace std;

Small_Board::Small_Board()
{
    InitBoard();
    _gameStatus = NONE;
}

void Small_Board::InitBoard()
{
    /* For all BLANK */
    for (int x = 0; x < 3; ++x)
        for (int y = 0; y < 3; ++y)
            _board[x][y] = Piece_BLANK;
}

Status Small_Board::GetStatus()
{
    return _gameStatus;
}

bool Small_Board::Fill(int cell, Piece _turn)
{
    /* Player grid is display from 1 
     * So 1 must be subtracted for the 
     * Correct index */
    cell = cell - 1;
    if (_board[cell / 3][cell % 3] == Piece_BLANK)
    {
        _board[cell / 3][cell % 3] = _turn;
        return true;
    }
    return false; // Cell already occupied
}

Status Small_Board::CheckWin()
{
    bool tie = true;
    /* Check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (_board[i][j] == Piece_BLANK)
                tie = false;

    if (tie)
    {
        _gameStatus = TIE;
        return TIE;
    }

    /* Top-left to bottom-right */
    if (_board[0][0] != Piece_BLANK &&
        _board[0][0] == _board[1][1] &&
        _board[1][1] == _board[2][2])
    {
        _gameStatus = _board[0][0] == Piece_X ? X : O;
        return _gameStatus; // Return winner
    }

    /* Top-right to bottom-left */
    if (_board[0][2] != Piece_BLANK &&
        _board[0][2] == _board[1][1] &&
        _board[1][1] == _board[2][0])
    {
        _gameStatus = _board[0][2] == Piece_X ? X : O;
        return _gameStatus; // Return winner
    }

    /* COLUMNS */
    for (int column = 0; column < 3; column++)
    {
        if (_board[0][column] == _board[1][column] &&
            _board[0][column] != Piece_BLANK &&
            _board[1][column] == _board[2][column])
        {
            _gameStatus = _board[0][column] == Piece_X ? X : O;
            return _gameStatus; // Return winner
        }
    }

    /* ROWS */
    for (int row = 0; row < 3; row++)
    {
        if (_board[row][0] != Piece_BLANK &&
            _board[row][0] == _board[row][1] &&
            _board[row][1] == _board[row][2])
        {
            _gameStatus = _board[row][0] == Piece_X ? X : O;
            return _gameStatus; // Return winner
        }
    }
    return NONE; // No one has won yet
}
