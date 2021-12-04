#include "handle.h"
#include "mode.h"
#include "graphics.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

cLargeBoard::cLargeBoard()
{
    m_turn = Piece_X; // The first turn is X 
	
    InitStatuses(); // Initial status 
}

void cLargeBoard::InitStatuses()
{
    /*
     * Initialise board statuses to NONE
     */
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            m_boardStatuses[x][y] = NONE;
}

/* Get current turn */
char cLargeBoard::GetTurn()
{
    return m_turn == Piece_X ? 'X' : 'O';
}

/* Set current turn by turn parameters */
void cLargeBoard::Setturn(PIECE turn)
{
    m_turn = turn;
}

/* Toggle switch turn */
void cLargeBoard::ToggleTurn()
{
    m_turn = m_turn == Piece_X ? Piece_O : Piece_X;
}

/* Get current board number */
int cLargeBoard::GetBoardNum()
{
    return m_boardNum + 1;
}

/* Set current board number by board_nu parameters*/
void cLargeBoard::SetBoardNum(int board_nu)
{
    m_boardNum = board_nu - 1;
}

/* Check board's status none or not */
bool cLargeBoard::BoardFinished()
{
    if (m_boardStatuses[m_boardNum / 3][m_boardNum % 3] != NONE)
        return true;
    return false;
}

/* Select new Board to play */
void cLargeBoard::SelectNewBoard()
{
	
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_boardStatuses[i][j] == NONE)
                DrawSelect(3 * i + j); // Choose a small board in the next turn
        }
    }

	/* Auto choose board for 2 mode */
    if (m_mode == 1 && m_turn == Piece_O)
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
        m_boardNum -= 1;
		
        if (BoardFinished())
            SelectNewBoard();   // call Recursive Function

    }
}

void cLargeBoard::Move(int cell)
{
    // Convert 1d index to 2d
    if (m_boards[m_boardNum / 3][m_boardNum % 3].Fill(cell, m_turn))
    {
		// Mapping cell to board
        m_boardNum = cell - 1;
    }
    else
    {
        GotoXY(xInput, yInput + 1);
        // Chosen cell is already occupied
        cout << "Position already occupied. Try again." << endl;
        GotoXY(xInput, yInput + 2);
        cout << "Cell: ";
        cell = InputData();
        Move(cell); // Call the function again with new parameters
    }
}


/* Check win the large board */
STATUS cLargeBoard::CheckWin()
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

    ToggleTurn(); // Change player

    return NONE;
}
