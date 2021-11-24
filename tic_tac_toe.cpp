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
    for(int x = 0; x < 3; ++x)
        for(int y = 0; y < 3; ++y)
            _board[x][y] = Piece_BLANK;
}

Status Small_Board::GetStatus()
{
    return _gameStatus;
}

int Small_Board::Move(int cell, Piece _turn)
{
    /* player grid is display from 1 
     * so 1 must be subtracted for the 
     * correct indice */
    cell = cell - 1;
    if(_board[cell/3][cell%3] == Piece_BLANK) {
        _board[cell/3][cell%3] = _turn;
        return 1;
    }
    return 0;  // cell already occupied
}

Status Small_Board::Update()
{ 
    bool tie = true;
    /* check for a tie */
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(_board[i][j] == Piece_BLANK)
                tie = false;

    if(tie) {
        _gameStatus = TIE;
        return TIE;
    }

    /* top-left to bottom-right */
    if(_board[0][0] != Piece_BLANK && 
       _board[0][0] == _board[1][1] && 
       _board[1][1] == _board[2][2]) {
        _gameStatus = _board[0][0] == Piece_X ? X : O;
        return _gameStatus; // return winner
    }        
    
    /* top-right to bottom-left */
    if(_board[0][2] != Piece_BLANK && 
       _board[0][2] == _board[1][1] && 
       _board[1][1] == _board[2][0]) {
        _gameStatus = _board[0][2] == Piece_X ? X : O;
        return _gameStatus; // return winner
    }        

    /* COLUMNS */
    for(int column = 0; column < 3; column++)
    {
        if(_board[0][column] == _board[1][column] \
                && _board[0][column] != Piece_BLANK \
                && _board[1][column] == _board[2][column]) {
            _gameStatus = _board[0][column] == Piece_X ? X : O;
            return _gameStatus; // return winner
        }
    }
    
    /* ROWS */
    for(int row = 0; row < 3; row++)
    {
        if(_board[row][0] != Piece_BLANK
            && _board[row][0] == _board[row][1] \
            && _board[row][1] == _board[row][2]) {
            _gameStatus = _board[row][0] == Piece_X ? X : O;
            return _gameStatus; // return winner
        }
    } 
    return NONE; // no one has won yet
}
