#include <iostream>
#include "ultimate_tic_tac_toe.h"

using namespace std;

Large_Board::Large_Board()
{
    _turn = Piece_X;
    InitStatuses();
}

void Large_Board::InitStatuses()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            _boardStatuses[x][y] = NONE;
}

char Large_Board::GetTurn()
{
    return _turn == Piece_X ? Piece_X : Piece_O;
}

void Large_Board::SetTurn()
{
    _turn = _turn == Piece_X ? Piece_O : Piece_X;
}

int Large_Board::GetBoardNum()
{
    return _board_num + 1;
}

void Large_Board::SetBoardNum(int board_num)
{
    _board_num = board_num - 1;
}

bool Large_Board::BoardFinished()
{
    if (_boardStatuses[_board_num / 3][_board_num % 3] != NONE)
        return true;
    return false;
}

void Large_Board::SelectNewBoard()
{
    for (int i = 0; i < 9; i++)
    {
        if(_boardStatuses[i / 3][i % 3] == NONE ) 
            Draw_select(i);
    }
    Goto_xy(0, 20);
    cout << "The game on the next board is finished\n"
         << GetTurn() << " select next board: ";
    cin >> _board_num;
    _board_num -= 1;    
    if (BoardFinished())
        SelectNewBoard();
}

void Large_Board::Move(int cell)
{
    if (_boards[_board_num / 3][_board_num % 3].Move(cell, _turn))
    {
        _board_num = cell - 1;
    }
    else
    {
        // chosen cell is already occupied
        cout << "Position already occupied. Try again :(" << endl;
        cout << "cell: ";
        cin >> cell;
        Move(cell);
        // call the function again with new parameters
    }
}

void Large_Board::DrawBoards()
{
    if (_board_num == -1)
        Information();
    else
    {
        Information();
        if(_boardStatuses[_board_num / 3][_board_num % 3] == NONE)
            Draw_select(_board_num);
    }

    Goto_xy(0, 0);

    cout << endl;
    for (int w = 0; w < 3; w++)
    {
        for (int x = 0; x < 3; x++)
        {
            cout << "\t";
            for (int y = 0; y < 3; y++)
            {
                for (int z = 0; z < 3; z++)
                {
                    Piece player = _boards[w][y]._board[x][z];
                    cout << (char)player << " ";
                }
                cout << "\t\t";
            }
            cout << endl;   
        }
        cout << endl;
        cout << endl;
        cout << endl;
    }
    cout << endl
         << endl;
}

Status Large_Board::Update()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            _boardStatuses[x][y] = _boards[x][y].Update();
        }
    }

    bool tie = true;
    /* check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (_boardStatuses[i][j] == NONE)
                tie = false;

    if (tie)
        return TIE;

    /* top-left to bottom-right */
    if (_boardStatuses[0][0] != NONE &&
        _boardStatuses[0][0] == _boardStatuses[1][1] &&
        _boardStatuses[1][1] == _boardStatuses[2][2])
        return GetTurn() == 'X' ? X : O;

    /* top-right to bottom-left */
    if (_boardStatuses[0][2] != NONE &&
        _boardStatuses[0][2] == _boardStatuses[1][1] &&
        _boardStatuses[1][1] == _boardStatuses[2][0])
        return GetTurn() == 'X' ? X : O;

    bool match;
    /* COLUMNS */
    for (int row = 0; row < 3; row++)
    {
        match = true;
        for (int column = 0; column < 3 - 1; column++)
        {
            if (_boardStatuses[column][row] == NONE || _boardStatuses[column][row] != _boardStatuses[column + 1][row])
            {
                match = false;
                break;
            }
        }
        if (match)
            return GetTurn() == 'X' ? X : O;
    }
    match = true; // match is false set it true for next check

    /* ROWS */
    for (int row = 0; row < 3; row++)
    {
        match = true;
        for (int column = 0; column < 3 - 1; column++)
        {
            if (_boardStatuses[row][column] == NONE || _boardStatuses[row][column] != _boardStatuses[row][column + 1])
            {
                match = false;
                break;
            }
        }
        if (match)
            return GetTurn() == 'X' ? X : O;
    }

    // change player
    SetTurn();
    return NONE;
}
