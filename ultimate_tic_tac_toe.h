#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.h"

class CLargeBoard
{
private:
    ePiece m_turn;       // Hold current player
    void InitStatuses(); // Initialise boards

public:
    void ToggleTurn();             // Toggle in turn
    eMode m_mode;                  // m_mode = 0: with Friend; m_mode = 1: with Bot
    int m_boardNum = -1;           // Current board = 0
    CSmallBoard m_boards[3][3];    // 3x3 Small Board
    eStatus m_boardStatuses[3][3]; // Status of Small Board

    CLargeBoard();        // Initialization method
    char GetTurn();       // Get turn of current
    void Setturn(ePiece); // Set turn for game
    void Move(int);
    int GetBoardNum();     // Get board of current
    void SetBoardNum(int); // Set board of current
    bool BoardFinished();  // Check if small board is finished
    void SelectNewBoard(); // Select new small board
    eStatus CheckWin();    // Check Win/Tie/None
};

#endif
