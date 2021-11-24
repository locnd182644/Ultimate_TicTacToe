#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.cpp"
#include "graphics.cpp"

class Large_Board
{
public:
    Large_Board();
    void DrawBoards();
    char GetTurn();
    void Move(int);
    int GetBoardNum();
    void SetBoardNum(int);
    bool BoardFinished();
    void SelectNewBoard();
    Status Update();

private:
    void InitStatuses();
    void SetTurn();
    
    int _board_num = -1;   // current board - 1
    Piece _turn;     // hold current player
    Small_Board _boards[3][3];
    Status _boardStatuses[3][3]; 
};

#endif


