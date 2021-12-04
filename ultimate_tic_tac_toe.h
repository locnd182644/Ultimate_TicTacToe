#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.h"

class cLargeBoard
{
private:
    PIECE m_turn;         // Hold current player
    void InitStatuses(); // Initialise boards
    void ToggleTurn();   // Toggle in turn

public:
    bool m_mode;                  // Mode 0: with Friend; Mode 1: with Bot
    int m_boardNum = -1;         // Current board = 0
    cSmallBoard m_boards[3][3];    // 3x3 Small Board
    Status m_boardStatuses[3][3]; // Status of Small Board

    cLargeBoard();          // Initialization method
    char GetTurn();        // Get turn of current
    void Setturn(PIECE);   // Set turn for game
    void Move(int);  
    int GetBoardNum();     // Get board of current
    void SetBoardNum(int); // Set board of current
    bool BoardFinished();  // Check if small board is finished
    void SelectNewBoard(); // Select new small board
    Status CheckWin();     // Check Win/Tie/None
};

#endif
