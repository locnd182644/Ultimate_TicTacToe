#include <iostream>
#include "extend.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

Large_Board::Large_Board()
{
    _turn = Piece_X;
    InitStatuses();
}

void Large_Board::InitStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            _boardStatuses[x][y] = NONE;
}

char Large_Board::GetTurn()
{
    return _turn == Piece_X ? 'X' : 'O';
}

void Large_Board::SetTurn()
{
    _turn = _turn == Piece_X ? Piece_O : Piece_X;
}

int Large_Board::GetBoardNum()
{
    return _board_num + 1;
}

void Large_Board::SetBoardNum(int board_no)
{
    _board_num = board_no - 1;
}

bool Large_Board::BoardFinished()
{
    if (_boardStatuses[_board_num / 3][_board_num % 3] != NONE)
        return true;
    return false;
}

void Large_Board::SelectNewBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (_boardStatuses[i][j] == NONE)
                Draw_select(3 * i + j);
        }
    }

    if(mode)

    Goto_xy(7, 21);
    cout << "The game on the next board is finished";
    Goto_xy(7, 22);
    cout << GetTurn() << " select next board: ";
    cin >> _board_num;
    _board_num -= 1;
    if (BoardFinished())
        SelectNewBoard();
}

void Large_Board::Move(int cell)
{
    // Convert 1d index to 2d
    if (_boards[_board_num / 3][_board_num % 3].Fill(cell, _turn))
    {
        // Minus 1 for zero indexing and convert 2d index to 1d :D
        _board_num = cell - 1;
    }
    else
    {
        // Chosen cell is already occupied
        cout << "Position already occupied. Try again." << endl;
        cout << "Cell: ";
        cin >> cell;
        Move(cell); // Call the function again with new parameters
    }
}

void Large_Board::DrawBoards()
{
    if (_board_num == -1)
        Information();
    else
    {
        Information();
        if (_boardStatuses[_board_num / 3][_board_num % 3] == NONE)
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

Status Large_Board::CheckWin()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            _boardStatuses[x][y] = _boards[x][y].CheckWin();
        }
    }

    bool tie = true;
    /* Check for a tie */
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

    /* COLUMNS */
    for (int row = 0; row < 3; row++)
    {
        if (_boardStatuses[row][0] != NONE &&
            _boardStatuses[row][0] == _boardStatuses[row][1] &&
            _boardStatuses[row][1] == _boardStatuses[row][2])
            return GetTurn() == 'X' ? X : O;
    }

    /* ROWS */
    for (int column = 0; column < 3; column++)
    {
        if (_boardStatuses[0][column] != NONE &&
            _boardStatuses[0][column] == _boardStatuses[1][column] &&
            _boardStatuses[1][column] == _boardStatuses[2][column])
            return GetTurn() == 'X' ? X : O;
    }

    SetTurn(); // Change player

    return NONE;
}
