#include "handle.h"
#include "mode.h"
#include "graphics.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

CLargeBoard::CLargeBoard()
{
    InitStatuses(); // initial status
}

void CLargeBoard::InitStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            m_boardStatuses[x][y] = NONE;
}

/* Get current turn */
char CLargeBoard::GetTurn()
{
    return m_turn == Piece_X ? 'X' : 'O';
}

/* Set current turn by turn parameters */
void CLargeBoard::Setturn(ePiece turn)
{
    m_turn = turn;
}

/* Toggle switch turn */
void CLargeBoard::ToggleTurn()
{
    m_turn = m_turn == Piece_X ? Piece_O : Piece_X;
}

/* Get current board number */
int CLargeBoard::GetBoardNum()
{
    return m_boardNum + 1;
}

/* Set current board number by board_nu parameters*/
void CLargeBoard::SetBoardNum(int board_nu)
{
    m_boardNum = board_nu - 1;
}

/* Check board's status none or not */
bool CLargeBoard::BoardFinished()
{
    if (m_boardStatuses[m_boardNum / 3][m_boardNum % 3] != NONE)
        return true;
    return false;
}

/* Select new Board to play */
void CLargeBoard::SelectNewBoard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_boardStatuses[i][j] == NONE)
                DrawSelect(3 * i + j); // choose a small board in the next turn
        }
    }

    /* Auto choose board for 2 mode */
    if (m_mode == BotEasy || m_mode == BotNormal || m_mode == BotHard && m_turn == Piece_O)
    {
        m_boardNum = BotSelectBoard(this);
    }
    else
    {
        GotoXY(xInput, yInput);
        cout << "The game on the next board is finished";
        GotoXY(xInput, yInput + 1);
        cout << GetTurn() << " select next board: ";

        m_boardNum = InputData(); // input from keyboard
                                  /*  Halfway exit */
        if (m_boardNum == 66)     // user input 'r'
            return;
        /**/
        m_boardNum -= 1;

        if (BoardFinished())
            SelectNewBoard(); // call Recursive Function
    }
}

void CLargeBoard::Move(int cell)
{
    if (m_boards[m_boardNum / 3][m_boardNum % 3].Fill(cell, m_turn)) // convert 1d index to 2d
    {
        m_boardNum = cell - 1; // mapping cell to board
    }
    else
    {
        GotoXY(xInput, yInput + 1);
        /* Chosen cell is already occupied */
        cout << "Position already occupied. Try again." << endl;
        GotoXY(xInput, yInput + 2);
        cout << "Cell: ";
        cell = InputData();
        Move(cell); // call the function again with new parameters
    }
}

/* Check win the large board */
eStatus CLargeBoard::CheckWin()
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            m_boardStatuses[x][y] = m_boards[x][y].CheckWin();
        }
    }

    bool tie = true;
    /* Check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_boardStatuses[i][j] == NONE)
                tie = false;

    if (tie)
        return TIE;

    /* top-left to bottom-right */
    if (m_boardStatuses[0][0] != NONE &&
        m_boardStatuses[0][0] == m_boardStatuses[1][1] &&
        m_boardStatuses[1][1] == m_boardStatuses[2][2])
        return GetTurn() == 'X' ? X : O;

    /* top-right to bottom-left */
    if (m_boardStatuses[0][2] != NONE &&
        m_boardStatuses[0][2] == m_boardStatuses[1][1] &&
        m_boardStatuses[1][1] == m_boardStatuses[2][0])
        return GetTurn() == 'X' ? X : O;

    /* COLUMNS */
    for (int row = 0; row < 3; row++)
    {
        if (m_boardStatuses[row][0] != NONE &&
            m_boardStatuses[row][0] == m_boardStatuses[row][1] &&
            m_boardStatuses[row][1] == m_boardStatuses[row][2])
            return GetTurn() == 'X' ? X : O;
    }

    /* ROWS */
    for (int column = 0; column < 3; column++)
    {
        if (m_boardStatuses[0][column] != NONE &&
            m_boardStatuses[0][column] == m_boardStatuses[1][column] &&
            m_boardStatuses[1][column] == m_boardStatuses[2][column])
            return GetTurn() == 'X' ? X : O;
    }

    return NONE;
}
