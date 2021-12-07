#include "mode.h"
#include "handle.h"
#include "graphics.h"

using namespace std;

/* Stack save Large Board to replay */
stack<cLargeBoard> g_hisBoard;

/* Random with checked condition : Cell must be Piece_BLANK */
int BotSelectCell(cLargeBoard *boards)
{
    int current_board = boards->m_boardNum;
    int temp;
    while (1)
    {
        temp = rand() % 9; // random 0 -> 8
        if (boards->m_boards[current_board / 3][current_board % 3]
                .m_board[temp / 3][temp % 3] == Piece_BLANK)
            break;
    }
    return ++temp;
}

/* Random with checked condition: The small board must be NONE*/
int BotSelectBoard(cLargeBoard *boards)
{
    int temp;
    while (1)
    {
        temp = rand() % 9; // random 0 -> 8
        if (boards->m_boards[temp / 3][temp % 3].GetStatus() == NONE)
            break;
    }
    return temp;
}

/* Evaluate score of current small board */
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

/* Find best move for bot */
int BestMove(cLargeBoard boards, int indexMove)
{
    int current_board = boards.m_boardNum;
    int x = -1, y = -1;
    int score = 0, bestScore = -999;

    /*  Bot thinks to fill O in each cell one by one.
        Then call back & check win and depth
        Return best score */
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] == Piece_BLANK)
            {
                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_O; // Fill by O Piece

                score = Minimax(boards.m_boards[current_board / 3][current_board % 3], indexMove - 1, false);

                boards.m_boards[current_board / 3][current_board % 3].m_board[i][j] = Piece_BLANK; // Fill by Blanks Piece again

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
    return x * 3 + y + 1; // Return best move
}

/* Mode play with Friend */
STATUS PlayWithFriend(PIECE piece)
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.Setturn(piece);  // set first turn
    currentBoard.m_mode = FRIEND; // mode with friend

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    m_boardNum = InputData();

    /*  Halfway exit */
    if (m_boardNum == 66) // user input 'r'
        return TIE;
    /**/

    currentBoard.SetBoardNum(m_boardNum);
    DrawSelect(currentBoard.GetBoardNum() - 1);

    int cell; // cell in small board

    while (1)
    {
        g_hisBoard.push(currentBoard); // push current board into vector list

        DrawBoards(currentBoard);
        GotoXY(xInput, yInput);
        cout << "Player " << currentBoard.GetTurn() << ": select cell";

        GotoXY(xInput, yInput + 1);
        cout << "Cell: ";
        cell = InputData();

        /*  Halfway exit */
        if (cell == 66) // user input 'r'
            return TIE;

        /* If cell = 0, replay */
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

        currentBoard.Move(cell); // fill cell into small board & mapping to board

        // DrawBoards(currentBoard);

        /* Check win large board */
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
        default:
            break;
        }

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }
}

/* Mode play with Bot Normal */
STATUS PlayWithBotNormal(PIECE piece)
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.Setturn(piece); // set first turn
    currentBoard.m_mode = BOT;   // mode with bot

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    /* Select board with both */
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // player import from keyboard

        /*  Halfway exit */
        if (m_boardNum == 66) // user input 'r'
            return TIE;
        /**/

    case O:
        m_boardNum = BotSelectBoard(&currentBoard); // bot automatically selects board
        break;
    }
    currentBoard.SetBoardNum(m_boardNum);

    int cell; // cell in small board

    while (1)
    {
        g_hisBoard.push(currentBoard); // push current board into vector list

        DrawBoards(currentBoard);
        switch (currentBoard.GetTurn())
        {
        case X:
            GotoXY(xInput, yInput);
            cout << "Player " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();

            /*  Halfway exit */
            if (cell == 66) // user input 'r'
                return TIE;
            /**/
            break;

        case O:
            GotoXY(xInput, yInput);
            cout << "Bot " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cell = BestMove(currentBoard, 2);
            cout << "Cell: " << cell;
            break;
        }

        /* If cell = 0, replay */
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

        currentBoard.Move(cell); // fill cell into small board & mapping to board

        // DrawBoards(currentBoard);

        /* Check win large board */
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

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }
}

/* Mode play with Bot Easy */
STATUS PlayWithBotEasy(PIECE piece)
{
    ClearScreen();

    cLargeBoard currentBoard;
    currentBoard.m_mode = BOT;   // mode with bot
    currentBoard.Setturn(piece); // set first turn

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    /* Select board with both */
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // player import from keyboard

        /*  Halfway exit */
        if (m_boardNum == 66) // user input 'r'
            return TIE;
        /**/

        break;

    case O:
        m_boardNum = BotSelectBoard(&currentBoard); // bot automatically selects board
        break;
    }

    currentBoard.SetBoardNum(m_boardNum);

    int cell; // cell in small board

    while (1)
    {
        g_hisBoard.push(currentBoard); // push current board into vector list

        DrawBoards(currentBoard);
        switch (currentBoard.GetTurn())
        {
        case X:
            GotoXY(xInput, yInput);
            cout << "Player " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();

            /*  Halfway exit */
            if (cell == 66) // user input 'r'
                return TIE;
            /**/

        case O:
            GotoXY(xInput, yInput);
            cout << "Bot " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cell = BotSelectCell(&currentBoard);
            cout << "Cell: " << cell;
            break;
        }

        /* If cell = 0 then replay */
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

        currentBoard.Move(cell); // fill cell into small board & mapping to board

        /* Check win large board */
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

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
            currentBoard.SelectNewBoard();
    }
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
