#include "handle.h"
#include "graphics.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

LargeBoard::LargeBoard()
{
    _turn = Piece_X;
    InitStatuses();
}

void LargeBoard::InitStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            boardStatuses[x][y] = NONE;
}

char LargeBoard::GetTurn()
{
    return _turn == Piece_X ? 'X' : 'O';
}

void LargeBoard::Setturn(Piece turn)
{
    _turn = turn;
}

void LargeBoard::ToggleTurn()
{
    _turn = _turn == Piece_X ? Piece_O : Piece_X;
}

int LargeBoard::GetBoardNum()
{
    return board_num + 1;
}

void LargeBoard::SetBoardNum(int board_no)
{
    board_num = board_no - 1;
}

bool LargeBoard::BoardFinished()
{
    if (boardStatuses[board_num / 3][board_num % 3] != NONE)
        return true;
    return false;
}

void LargeBoard::SelectNewBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boardStatuses[i][j] == NONE)
                Draw_select(3 * i + j);
        }
    }

    if (mode == true && _turn == Piece_O)
    {
        board_num = BotSelectBoard(this);
    }
    else
    {
        Goto_xy(xInput, yInput);
        cout << "The game on the next board is finished";
        Goto_xy(xInput, yInput + 1);
        cout << GetTurn() << " select next board: ";
        board_num = InputData();
        board_num -= 1;
        if (BoardFinished())
            SelectNewBoard();
    }
}

void LargeBoard::Move(int cell)
{
    // Convert 1d index to 2d
    if (boards[board_num / 3][board_num % 3].Fill(cell, _turn))
    {
        // Minus 1 for zero indexing and convert 2d index to 1d :D
        board_num = cell - 1;
    }
    else
    {
        Goto_xy(xInput, yInput + 1);
        // Chosen cell is already occupied
        cout << "Position already occupied. Try again." << endl;
        Goto_xy(xInput, yInput + 2);
        cout << "Cell: ";
        cin >> cell;
        Move(cell); // Call the function again with new parameters
    }
}

void LargeBoard::DrawBoards()
{
    Clear_Screen();
    cout << "\n\n";
    for (int w = 0; w < 3; w++)
    {
        for (int x = 0; x < 3; x++)
        {
            cout << "\t";
            for (int y = 0; y < 3; y++)
            {
                for (int z = 0; z < 3; z++)
                {
                    Piece player = boards[w][y].board[x][z];
                    cout << (char)player << " ";
                }
                cout << "     ";
            }
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
    if (board_num == -1)
        Information(this);
    else
    {
        Information(this);
        if (boardStatuses[board_num / 3][board_num % 3] == NONE)
            Draw_select(board_num);
    }
}

Status LargeBoard::CheckWin()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            boardStatuses[x][y] = boards[x][y].CheckWin();
        }
    }

    bool tie = true;
    /* Check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (boardStatuses[i][j] == NONE)
                tie = false;

    if (tie)
        return TIE;

    /* top-left to bottom-right */
    if (boardStatuses[0][0] != NONE &&
        boardStatuses[0][0] == boardStatuses[1][1] &&
        boardStatuses[1][1] == boardStatuses[2][2])
        return GetTurn() == 'X' ? X : O;

    /* top-right to bottom-left */
    if (boardStatuses[0][2] != NONE &&
        boardStatuses[0][2] == boardStatuses[1][1] &&
        boardStatuses[1][1] == boardStatuses[2][0])
        return GetTurn() == 'X' ? X : O;

    /* COLUMNS */
    for (int row = 0; row < 3; row++)
    {
        if (boardStatuses[row][0] != NONE &&
            boardStatuses[row][0] == boardStatuses[row][1] &&
            boardStatuses[row][1] == boardStatuses[row][2])
            return GetTurn() == 'X' ? X : O;
    }

    /* ROWS */
    for (int column = 0; column < 3; column++)
    {
        if (boardStatuses[0][column] != NONE &&
            boardStatuses[0][column] == boardStatuses[1][column] &&
            boardStatuses[1][column] == boardStatuses[2][column])
            return GetTurn() == 'X' ? X : O;
    }

    ToggleTurn(); // Change player

    return NONE;
}
