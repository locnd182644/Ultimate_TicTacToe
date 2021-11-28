#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.h"
#include "graphics.h"

class Large_Board
{
private:
    void InitStatuses();
    void SetTurn();

public:
    Piece _turn;         // Hold current player
    int _board_num = -1; // Current board = 0
    Small_Board _boards[3][3];
    Status _boardStatuses[3][3];
    Large_Board();
    void DrawBoards();     // Draw large boad
    char GetTurn();        //
    void Move(int);        //
    int GetBoardNum();     //
    void SetBoardNum(int); //
    bool BoardFinished();  //
    void SelectNewBoard(); //
    Status CheckWin();     //
    bool mode;             // Mode 0: with Friend; Mode 1: with Bot
};

#endif
