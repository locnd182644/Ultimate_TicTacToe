#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.h"

class LargeBoard
{
private:
    Piece _turn;         // Hold current player
    void InitStatuses(); // Initialise boards
    void ToggleTurn();   // Toggle in turn

public:
    bool mode;                  // Mode 0: with Friend; Mode 1: with Bot
    int board_num = -1;         // Current board = 0
    SmallBoard boards[3][3];    // 3x3 Small Board
    Status boardStatuses[3][3]; // Status of Small Board

    LargeBoard();          // Initialization function
    void DrawBoards();     // Draw large boad
    char GetTurn();        // Get turn of current
    void Setturn(Piece);   // Set turn for game
    void Move(int);        // Move
    int GetBoardNum();     // Get board of current
    void SetBoardNum(int); // Set board of current
    bool BoardFinished();  // Check if small board is finished
    void SelectNewBoard(); // Select new small board
    Status CheckWin();     // Check Win/Tie/None
};

#endif
