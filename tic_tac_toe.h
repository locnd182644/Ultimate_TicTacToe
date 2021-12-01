#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h

#include <iostream>

enum Piece
{
    Piece_BLANK = 95, // " _ "
    Piece_O = 79,     // " O "
    Piece_X = 88,     // " X "
};

enum Status
{
    NONE,
    TIE = 61, // " = "
    O = 79,   // " O "
    X = 88,   // " X "
};

class SmallBoard
{
private:
    Status _gameStatus; // Status of SmallBoard
public:
    Piece board[3][3]; // 3x3 cell
    SmallBoard();
    void InitBoard();                 // Initialization for SmallBoard
    bool Fill(int cell, Piece _turn); // Set pice for cell
    Status CheckWin();                // Check Win/Tie/None
    Status GetStatus();               // Get status of SmallBoard
};

#endif
