#ifndef _tic_tac_toe_h
#define _tic_tac_toe_h

enum Piece
{
    Piece_BLANK = 95, // " _ "
    Piece_O = 79,     // " O "
    Piece_X = 88,     // " X "
};

enum Status
{
    NONE,
    TIE = 61, // " = "
    O = 79,   // " O "
    X = 88,   // " X "
};

class Small_Board
{
private:
    Status _gameStatus;               // Status of SmallBoard
public:
    Piece _board[3][3];
    Small_Board();
    void InitBoard();                 // Initialization for Small_Board
    bool Fill(int cell, Piece _turn); // Set pice for cell
    Status CheckWin();                // Check Win/Tie/None
    Status GetStatus();               // Get status of Small_Board
};

#endif
