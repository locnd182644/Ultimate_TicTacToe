#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h  

enum Piece {Piece_BLANK = 95, Piece_O = 79, Piece_X = 88};
enum Status {NONE, TIE, O = 79 , X = 88};

class Small_Board
{
public:
    Small_Board();
    void initBoard();
    int move(int cell, Piece _turn);
    Status update();
    Status getStatus();
    Piece _board[3][3];

private:
    Status _gameStatus;
};

#endif
