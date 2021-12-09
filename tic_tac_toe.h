#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h

#include <iostream>

enum ePiece
{
    Piece_BLANK = 95, // " _ "
    Piece_O = 79,     // " O "
    Piece_X = 88,     // " X "
};

enum eStatus
{
    NONE,
    TIE = 61, // " = "
    O = 79,   // " O "
    X = 88,   // " X "
};

enum eMode
{
    Friend,
    BotEasy,
    BotNormal,
    BotHard,
};

enum eSort
{
    INCREASE,
    DECREASE
};

class CSmallBoard
{
private:
    eStatus m_gameStatus; // Status of SmallBoard
public:
    ePiece m_board[3][3];   // 3x3 cell
    CSmallBoard();          // Initialization method
    void InitBoard();       // Initialization for SmallBoard
    bool Fill(int, ePiece); // Set pice for cell
    eStatus CheckWin();     // Check Win/Tie/None
    eStatus GetStatus();    // Get status of SmallBoard
};

#endif
