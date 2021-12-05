#include "mode.h"
#include "handle.h"
#include "graphics.h"

using namespace std;

/* Stack save Large Board to replay */
stack<cLargeBoard> g_hisBoard;

/* Random with checked condition */
int BotSelectCell(cLargeBoard *boards)
{
    int current_board = boards->m_boardNum;
    int temp;
    while (1)
    {
        temp = rand() % 9;
        if (boards->m_boards[current_board / 3][current_board % 3]
                .m_board[temp / 3][temp % 3] == Piece_BLANK)
            break;
    }
    return ++temp;
}

/* Random with checked condition */
int BotSelectBoard(cLargeBoard *boards)
{
    int temp;
    while (1)
    {
        while (1)
        {
            temp = rand() % 10;
            if (temp != 9)
                break;
        }
        if (boards->m_boards[temp / 3][temp % 3].GetStatus() == NONE)
            break;
    }
    return temp;
}

/* Evaluate score of current small board */
int EvaluateValue(cSmallBoard board)
{
    switch (board.CheckWin())
    {
    case X:
        return -10;
    case O:
        return 10;
    default:
        return 0;
    }
}

/* Find best move for bot */
int FindBestMove(cLargeBoard boards)
{
    int current_board = boards.m_boardNum;
    int bestMove = 0;
    int moveVal;

    /* Bot fill X in each cell one by one. Then check win this turn */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] == Piece_BLANK)
            {
                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_X;
                moveVal = EvaluateValue(boards.m_boards[current_board / 3][current_board % 3]);
                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_BLANK;
                if (moveVal == -10)
                {
                    bestMove = 3 * i + j + 1;
                }
            }
        }
    }

    /**     Prioritise win rather than preventing    **/

    /* Bot fill O in each cell one by one. Then check win this turn */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] == Piece_BLANK)
            {
                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_O;
                moveVal = EvaluateValue(boards.m_boards[current_board / 3][current_board % 3]);
                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_BLANK;
                if (moveVal == 10)
                {
                    bestMove = 3 * i + j + 1;
                }
            }
        }
    }

    if (bestMove == 0)
    {
        return BotSelectCell(&boards);
    }

    return bestMove;
}

/* Mode play with Friend */
STATUS PlayWithFriend()
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.m_mode = 0;

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    m_boardNum = InputData();
    if (m_boardNum == 66) // User input 'r'
        return TIE;

    currentBoard.SetBoardNum(m_boardNum);
    DrawSelect(currentBoard.GetBoardNum() - 1);
    int cell;
    while (1)
    {
        g_hisBoard.push(currentBoard);
        DrawBoards(currentBoard);
        GotoXY(xInput, yInput);
        cout << "Player " << currentBoard.GetTurn() << ": select cell";

        GotoXY(xInput, yInput + 1);
        cout << "Cell: ";
        cell = InputData();
        if (m_boardNum == 66) // User input 'r'
            return TIE;

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_hisBoard.empty())
                    break;
                currentBoard = g_hisBoard.top();
                g_hisBoard.pop();
            }
            continue;
        }
        currentBoard.Move(cell);
        int status = currentBoard.CheckWin();
        DrawBoards(currentBoard);

        switch (status)
        {
        case X:
            cout << "X has won!" << endl;
            return X;
        case O:
            cout << "O has won!" << endl;
            return O;
        case TIE:
            cout << "Game over. Tie" << endl;
            return TIE;
        default:
            break;
        }

        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }

    // Halfway exit
    return TIE;
}

/* Mode play with Bot Normal */
STATUS PlayWithBotNormal(PIECE piece)
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.Setturn(piece); // set first turn
    currentBoard.m_mode = 1;     // mode with bot

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // Player import from keyboard
        if (m_boardNum == 66)     // user input 'r'
            return TIE;
        break;

    case O:
        m_boardNum = BotSelectBoard(&currentBoard); // bot automatically selects board
        break;
    }
    currentBoard.SetBoardNum(m_boardNum);

    int cell;

    while (1)
    {
        g_hisBoard.push(currentBoard);
        DrawBoards(currentBoard);
        switch (currentBoard.GetTurn())
        {
        case X:
            GotoXY(xInput, yInput);
            cout << "Player " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();
            if (cell == 66) // user input 'r'
                return TIE;
            break;

        case O:
            GotoXY(xInput, yInput);
            cout << "Bot " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput);
            cell = FindBestMove(currentBoard);
            cout << "Cell: " << cell;
            break;
        }

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_hisBoard.empty())
                    break;
                currentBoard = g_hisBoard.top();
                g_hisBoard.pop();
            }
            continue;
        }

        currentBoard.Move(cell);
        int status = currentBoard.CheckWin();
        DrawBoards(currentBoard);

        switch (status)
        {
        case X:
            cout << "X has won!" << endl;
            return X;
        case O:
            cout << "O has won!" << endl;
            return O;
        case TIE:
            cout << "Game over. Tie" << endl;
            return TIE;
        case NONE:
            break;
        }
        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }

    // Halfway exit
    return TIE;
}

/* Mode play with Bot Easy */
STATUS PlayWithBotEasy(PIECE piece)
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.m_mode = 1; // mode with bot
    currentBoard.Setturn(piece);

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";
    m_boardNum = InputData();
    if (m_boardNum == 66) // user input 'r'
        return TIE;
    currentBoard.SetBoardNum(m_boardNum);
    int cell;

    while (1)
    {
        g_hisBoard.push(currentBoard);
        DrawBoards(currentBoard);
        switch (currentBoard.GetTurn())
        {
        case X:
            GotoXY(xInput, yInput);
            cout << "Player " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();
            if (cell == 66) // user input 'r'
                return TIE;
            break;

        case O:
            GotoXY(xInput, yInput);
            cout << "Bot " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cell = BotSelectCell(&currentBoard);
            cout << "Cell: " << cell;
            break;
        }

        // If cell = 0 then replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (g_hisBoard.empty())
                    break;
                currentBoard = g_hisBoard.top();
                g_hisBoard.pop();
            }
            continue;
        }

        currentBoard.Move(cell);
        int status = currentBoard.CheckWin();

        switch (status)
        {
        case X:
            cout << "X has won!" << endl;
            return X;
        case O:
            cout << "O has won!" << endl;
            return O;
        case TIE:
            cout << "Game over. Tie" << endl;
            return TIE;
        case NONE:
            break;
        }
        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }

    // Halfway exit
    return TIE;
}

/* Re-watch the latest match */
void RecordGame()
{
    cLargeBoard currBoards; // current Board

    stack<cLargeBoard> temp;

    for (; !g_hisBoard.empty(); g_hisBoard.pop())
    {
        currBoards = g_hisBoard.top();
        temp.push(currBoards);
    }

    for (; !temp.empty(); temp.pop())
    {
        currBoards = temp.top();
        DrawBoards(currBoards);
        Sleep(SleepTime500); // screen pause 500 ms per turn
    }
}
