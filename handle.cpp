#include "handle.h"
#include "stack"
#include "graphics.h"

using namespace std;

// Pointer to player in the vector list
extern cPlayerInfor *pPlayer[2];

/* Allows input from the keypad integers from 0 to 9 or 'r' */
int InputData()
{
    char data;
    while (1)
    {
        cin >> data;
        /*
            Ascii '0' = 48
            Ascii '9' = 57
            Ascii 'r' = 114
        */
        if ((int)data <= 57 && (int)data >= 48 || (int)data == 114)
            break;
        GotoXY(7, 22);
        cout << "Re-Enter: ";
    }

    return (int)data - 48; // return 0 -> 9 or 66
}

/* Set & returns the first player */
PIECE SelectFirstPlay(MODE mode)
{
    ClearScreen();

    int option;
    switch (mode)
    {
    /* Play with friend */
    case FRIEND:
        cout << "*** NOTE: ' " << pPlayer[0]->m_name << " ' is X\n";
        cout << "          ' " << pPlayer[1]->m_name << " ' is O\n\n";
        SetColorText(green);
        cout << "Choose to play first: \n";
        SetColorText(white);
        cout << "1. " << pPlayer[0]->m_name << endl;
        cout << "2. " << pPlayer[1]->m_name << endl
             << endl;
        cout << "Option: ";
        while (1)
        {
            option = InputData();
            if (option == 1)
            {
                return Piece_X;
            }
            if (option == 2)
            {
                return Piece_O;
            }
        }

    /* Play with Bot */
    case BOT:
        cout << "*** NOTE: Bot is always O\n\n";
        SetColorText(green);
        cout << "Choose to play first: \n";
        SetColorText(white);
        cout << "1. Bot\n";
        cout << "2. Player\n\n";
        cout << "Option: ";
        while (1)
        {
            option = InputData();
            if (option == 1)
            {
                return Piece_O;
            }
            if (option == 2)
            {
                return Piece_X;
            }
        }
    }
}

/* Random with checked condition : Cell must be Piece_BLANK */
int BotSelectCell(cLargeBoard *pBoards)
{
    int currentBoard = pBoards->m_boardNum;
    int temp;
    while (1)
    {
        temp = rand() % 9; // random 0 -> 8
        if (pBoards->m_boards[currentBoard / 3][currentBoard % 3]
                .m_board[temp / 3][temp % 3] == Piece_BLANK)
            break;
    }
    return ++temp;
}

/* Random with checked condition: The small board must be NONE*/
int BotSelectBoard(cLargeBoard *pBoards)
{
    int temp;
    while (1)
    {
        temp = rand() % 9; // random 0 -> 8
        if (pBoards->m_boards[temp / 3][temp % 3].GetStatus() == NONE)
            break;
    }
    return temp;
}

/* Evaluate score of current small board */
int Minimax(cSmallBoard boards, int depth, bool isBOT)
{
    int score = 0;
    int bestScore = 0;

    switch (boards.CheckWin())
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
                if (boards.m_board[i][j] == Piece_BLANK)
                {
                    boards.m_board[i][j] = Piece_O;
                    score = Minimax(boards, depth - 1, false);
                    boards.m_board[i][j] = Piece_BLANK;
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
                if (boards.m_board[i][j] == Piece_BLANK)
                {
                    boards.m_board[i][j] = Piece_X;
                    score = Minimax(boards, depth - 1, true);
                    boards.m_board[i][j] = Piece_BLANK;
                    bestScore = min(score, bestScore);
                }
            }
        }
        return bestScore;
    }
}

/* Find best move for bot */
int BestMove(cLargeBoard boards, int indexMove)
{
    int currentBoardNum = boards.m_boardNum;
    int x = -1, y = -1;
    int score = 0, bestScore = -999;

    /*  Bot thinks to fill O in each cell one by one.
        Then call back & check win and depth
        Return best score */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.m_boards[currentBoardNum / 3][currentBoardNum % 3].m_board[i][j] == Piece_BLANK)
            {
                boards.m_boards[currentBoardNum / 3][currentBoardNum % 3].m_board[i][j] = Piece_O; // Fill by O Piece

                score = Minimax(boards.m_boards[currentBoardNum / 3][currentBoardNum % 3], indexMove - 1, false);

                boards.m_boards[currentBoardNum / 3][currentBoardNum % 3].m_board[i][j] = Piece_BLANK; // Fill by Blanks Piece again

                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y + 1; // Return best move
}

/*  The number of moves in current small board */
int MoveNum(cLargeBoard boards)
{
    int tempMoveNum = 0;
    int currentBoardNum = boards.m_boardNum;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.m_boards[currentBoardNum / 3][currentBoardNum % 3].m_board[i][j] != Piece_BLANK)
                tempMoveNum++;
        }
    }
    return tempMoveNum;
}
