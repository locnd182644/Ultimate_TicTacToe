#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h  

enum Piece {Piece_BLANK = 95, Piece_O = 79, Piece_X = 88};
enum Status {NONE, TIE = 61, O = 79 , X = 88};

class Small_Board
{
public:
    Small_Board();
    void InitBoard();
    int Move(int cell, Piece _turn);
    Status Update();
    Status GetStatus();
    Piece _board[3][3];

private:
    Status _gameStatus;
};

#endif
