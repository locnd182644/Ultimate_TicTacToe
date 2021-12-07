#include "test.h"

void Display(cSmallBoard _board)
{
    cout << "+---+---+---+" << endl;
    cout << "| " << (char)_board.m_board[0][0] << " | " << (char)_board.m_board[0][1] << " | " << (char)_board.m_board[0][2] << " | " << endl;
    cout << "+---+---+---+" << endl;
    cout << "| " << (char)_board.m_board[1][0] << " | " << (char)_board.m_board[1][1] << " | " << (char)_board.m_board[1][2] << " | " << endl;
    cout << "+---+---+---+" << endl;
    cout << "| " << (char)_board.m_board[2][0] << " | " << (char)_board.m_board[2][1] << " | " << (char)_board.m_board[2][2] << " | " << endl;
    cout << "+---+---+---+" << endl;
}

int Minimax(cSmallBoard board, int depth, bool isBOT)
{
    int score = 0;
    int bestScore = 0;

    switch (board.CheckWin())
    {
    case O:
        return 10;
    case X:
        return -10;
    }

    if (depth == 0)
        return 0;

    // Turn of Bot       /* Maximizing */
    if (isBOT == true)
    {
        bestScore = -999;
        /*  Try to fill O in each cell one by one.
            Then call back & check win and depth */
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board.m_board[i][j] == Piece_BLANK)
                {
                    board.m_board[i][j] = Piece_O;
                    score = Minimax(board, depth - 1, false);
                    board.m_board[i][j] = Piece_BLANK;
                    bestScore = max(score, bestScore);
                }
            }
        }
        return bestScore;
    }

    else // Turn of Player      /* Minimizing */
    {
        bestScore = 999;
        /*  Try to fill X in each cell one by one.
            Then call back & check win and depth */
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board.m_board[i][j] == Piece_BLANK)
                {
                    board.m_board[i][j] = Piece_X;
                    score = Minimax(board, depth - 1, true);
                    board.m_board[i][j] = Piece_BLANK;
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

int RandomMove()
{
    return rand() % 9 + 1;
}

int BestMove(cSmallBoard board, int indexMove)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;

    /*  Bot thinks to fill O in each cell one by one.
        Then call back & check win and depth
        Return best score */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board.m_board[i][j] == Piece_BLANK)
            {
                board.m_board[i][j] = Piece_O;

                score = Minimax(board, indexMove - 1, false);

                board.m_board[i][j] = Piece_BLANK;

                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    cout << " Score Best: " << bestScore << endl;
    return x * 3 + y + 1;
}

void Test()
{
    int cell;
    int indexMove = 0;
    PIECE turn = Piece_O;
    cSmallBoard testBoard;

    // Set match
    // testBoard.m_board[0][1] = Piece_X;
    // testBoard.m_board[1][2] = Piece_X;
    // testBoard.m_board[2][2] = Piece_X;
    // testBoard.m_board[2][0] = Piece_O;
    // testBoard.m_board[2][1] = Piece_O;

    while (1)
    {
        do
        {
            cout << "Import cell: ";
            switch (turn)
            {
            case Piece_X:
                cell = InputData();
                break;

            case Piece_O:
                cell = BestMove(testBoard, 2);
                break;
            }
        } while (!testBoard.Fill(cell, turn));
        indexMove++;
        turn = turn == Piece_X ? Piece_O : Piece_X;
        Display(testBoard);
        switch (testBoard.CheckWin())
        {
        case X:
            cout << " X win\n";
            return;

        case O:
            cout << "O Win\n";
            return;
        }
    }
}
