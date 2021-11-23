#ifndef _ultimate_tic_tac_toe_h
#define _ultimate_tic_tac_toe_h

#include "tic_tac_toe.cpp"
#include "graphics.cpp"

class Large_Board
{
public:
    Large_Board();
    void displayBoards();
    void Draw_select();
    char getTurn();
    void move(int);
    int getBoardNum();
    void setBoardNum(int);
    bool boardFinished();
    void selectNewBoard();
    Status update();

private:
    void initStatuses();
    void setTurn();
    
    int _board_num = -1;   // current board - 1
    Piece _turn;     // hold current player
    Small_Board _boards[3][3];
    Status _boardStatuses[3][3]; 
};

#endif


