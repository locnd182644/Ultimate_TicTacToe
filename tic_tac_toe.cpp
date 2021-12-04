#include "tic_tac_toe.h"

using namespace std;

cSmallBoard::cSmallBoard()
{
    InitBoard();
	
	/* Set Initial status by NONE */
    m_gameStatus = NONE;
}

void cSmallBoard::InitBoard()
{
    /* For all BLANK */
    for (int x = 0; x < 3; ++x)
        for (int y = 0; y < 3; ++y)
            m_board[x][y] = Piece_BLANK;
}

/* Get status of small board */
Status cSmallBoard::GetStatus()
{
    return m_gameStatus;
}

/* Fill in cell */
bool cSmallBoard::Fill(int cell, PIECE m_turn)
{
    /* Player grid is display from 1 
     * So 1 must be subtracted for the 
     * Correct index */
    cell = cell - 1;
    if (m_board[cell / 3][cell % 3] == Piece_BLANK)
    {
        m_board[cell / 3][cell % 3] = m_turn;
        return true;
    }
    return false; // Cell already occupied
}

/* Check win */
Status cSmallBoard::CheckWin()
{
    bool tie = true;
    /* Check for a tie */
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (m_board[i][j] == Piece_BLANK)
                tie = false;
			
	/* No tie until all are taken */
    if (tie)
    {
        m_gameStatus = TIE;
        return TIE;
    }

    /* Top-left to bottom-right */
    if (m_board[0][0] != Piece_BLANK &&
        m_board[0][0] == m_board[1][1] &&
        m_board[1][1] == m_board[2][2])
    {
        m_gameStatus = m_board[0][0] == Piece_X ? X : O;
        return m_gameStatus; // Return winner
    }

    /* Top-right to bottom-left */
    if (m_board[0][2] != Piece_BLANK &&
        m_board[0][2] == m_board[1][1] &&
        m_board[1][1] == m_board[2][0])
    {
        m_gameStatus = m_board[0][2] == Piece_X ? X : O;
        return m_gameStatus; // Return winner
    }

    /* COLUMNS */
    for (int column = 0; column < 3; column++)
    {
        if (m_board[0][column] == m_board[1][column] &&
            m_board[0][column] != Piece_BLANK &&
            m_board[1][column] == m_board[2][column])
        {
            m_gameStatus = m_board[0][column] == Piece_X ? X : O;
            return m_gameStatus; // Return winner
        }
    }

    /* ROWS */
    for (int row = 0; row < 3; row++)
    {
        if (m_board[row][0] != Piece_BLANK &&
            m_board[row][0] == m_board[row][1] &&
            m_board[row][1] == m_board[row][2])
        {
            m_gameStatus = m_board[row][0] == Piece_X ? X : O;
            return m_gameStatus; // Return winner
        }
    }
    return NONE; // No one has won yet
}
