#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h

#include <iostream>

enum PIECE
{
    Piece_BLANK = 95, // " _ "
    Piece_O = 79,     // " O "
    Piece_X = 88,     // " X "
};

enum STATUS
{
    NONE,
    TIE = 61, // " = "
    O = 79,   // " O "
    X = 88,   // " X "
};

class cSmallBoard
{
private:
    STATUS m_gameStatus; // Status of SmallBoard
public:
    PIECE m_board[3][3];                // 3x3 cell
    cSmallBoard();                     // Initialization method
    void InitBoard();                 // Initialization for SmallBoard
    bool Fill(int cell, PIECE m_turn); // Set pice for cell
    STATUS CheckWin();                // Check Win/Tie/None
    STATUS GetStatus();               // Get status of SmallBoard
};

#endif
