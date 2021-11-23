#include <iostream>
#include "ultimate_tic_tac_toe.h"

using namespace std;

Large_Board::Large_Board()
{
    _turn = Piece_X;
    initStatuses();
}

void Large_Board::initStatuses()
{
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            _boardStatuses[x][y] = NONE;
}

char Large_Board::getTurn()
{
    return _turn == Piece_X ? 'X' : 'O';
}

void Large_Board::setTurn()
{
    _turn = _turn == Piece_X ? Piece_O : Piece_X;
}

int Large_Board::getBoardNum()
{
    return _board_num + 1;
}

void Large_Board::setBoardNum(int board_num)
{
    _board_num = board_num - 1;
}

bool Large_Board::boardFinished()
{
    if (_boardStatuses[_board_num / 3][_board_num % 3] != NONE)
        return true;
    return false;
}

void Large_Board::selectNewBoard()
{
    cout << "The game on the next board is finished, " << getTurn() << " select next board: ";
    cin >> _board_num;
    _board_num -= 1;
    if (boardFinished())
        selectNewBoard();
}

void Large_Board::move(int cell)
{
    if (_boards[_board_num / 3][_board_num % 3].move(cell, _turn))
    {
        _board_num = cell - 1;
    }
    else
    {
        // chosen cell is already occupied
        cout << "Position already occupied. Try again." << endl;
        cout << "cell: ";
        cin >> cell;
        move(cell); 
        // call the function again with new parameters
    }
}

void Large_Board::displayBoards()
{
    if (_board_num == -1)
        Information();
    else
    {
        Information();
        Draw_select();
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
                cout << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl
         << endl;
}

void Large_Board::Draw_select()
{
    int i;
    int _x = 6 + 8 * (_board_num % 3);
    int _y = 0 + 4 * (_board_num / 3);
    Goto_xy(_x, _y);
    cout << " _______ ";
    for (i = 1; i < 4; i++)
    {
        Goto_xy(_x, _y + i);
        cout << "|";
        Goto_xy(_x + 8, _y + i);
        cout << "|";
    }
    Goto_xy(_x, _y + i);
    cout << "|_______|";
}

Status Large_Board::update()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            _boardStatuses[x][y] = _boards[x][y].update();
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

    /* DIAGONALS */
    /* top-left to bottom-right */
    if (_boardStatuses[0][0] != NONE &&
        _boardStatuses[0][0] == _boardStatuses[1][1] &&
        _boardStatuses[1][1] == _boardStatuses[2][2])
        return getTurn() == 'X' ? X : O;

    /* top-right to bottom-left */
    if (_boardStatuses[0][2] != NONE &&
        _boardStatuses[0][2] == _boardStatuses[1][1] &&
        _boardStatuses[1][1] == _boardStatuses[2][0])
        return getTurn() == 'X' ? X : O;

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
            return getTurn() == 'X' ? X : O;
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
            return getTurn() == 'X' ? X : O;
    }

    // change player
    setTurn(); 
    return NONE;
}
