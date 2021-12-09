#include "mode.h"
#include "handle.h"
#include "graphics.h"

using namespace std;

/* Stack save Large Board to replay */
extern stack<CLargeBoard> g_hisBoard;

/* Mode play with Friend */
eStatus PlayWithFriend(ePiece piece)
{
    ClearScreen();

    CLargeBoard currentBoard;
    currentBoard.Setturn(piece);  // set first turn
    currentBoard.m_mode = Friend; // mode with friend

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    m_boardNum = InputData();

    /*  Halfway exit & Lost */
    if (m_boardNum == 66) // user input 'r'
        return currentBoard.GetTurn() == Piece_X ? O : X;
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

        /*  Halfway exit & Lost */
        if (cell == 66) // user input 'r'
            return currentBoard.GetTurn() == Piece_X ? O : X;
        /**/

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

        /* Check win large board */
        int status = currentBoard.CheckWin();
        GotoXY(xInput, yInput + 2);
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

        currentBoard.ToggleTurn(); // change player

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
        {
            DrawBoards(currentBoard);
            currentBoard.SelectNewBoard();
        }
    }
}

/* Mode play with Bot Easy */
eStatus PlayWithBotEasy(ePiece piece)
{
    ClearScreen();

    CLargeBoard currentBoard;
    currentBoard.m_mode = BotEasy; // mode with bot easy
    currentBoard.Setturn(piece);   // set first turn

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    /* Select board with both */
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // player import from keyboard

        /*  Halfway exit & Lost */
        if (m_boardNum == 66) // user input 'r'
            return currentBoard.GetTurn() == Piece_X ? O : X;
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

            /*  Halfway exit & Lost */
            if (cell == 66) // user input 'r'
                return currentBoard.GetTurn() == Piece_X ? O : X;
            /**/
            break;

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
        GotoXY(xInput, yInput + 2);
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

        currentBoard.ToggleTurn(); // change player

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
        {
            DrawBoards(currentBoard);
            currentBoard.SelectNewBoard();
        }
    }
}

/* Mode play with Bot Normal */
eStatus PlayWithBotNormal(ePiece piece)
{
    ClearScreen();

    CLargeBoard currentBoard;
    currentBoard.Setturn(piece);     // set first turn
    currentBoard.m_mode = BotNormal; // mode with bot normal

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    /* Select board with both */
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // player import from keyboard

        /*  Halfway exit & Lost */
        if (m_boardNum == 66) // user input 'r'
            return currentBoard.GetTurn() == Piece_X ? O : X;
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

            /*  Halfway exit & Lost */
            if (cell == 66) // user input 'r'
                return currentBoard.GetTurn() == Piece_X ? O : X;
            /**/

            break;

        case O:
            /*  Bot premeditate 2 move
                Bot can win and prevent in current small board */
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

        /* Check win large board */
        int status = currentBoard.CheckWin();

        if (status != NONE)
            DrawBoards(currentBoard);
        GotoXY(xInput, yInput + 2);
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

        currentBoard.ToggleTurn(); // change player

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
        {
            DrawBoards(currentBoard);
            currentBoard.SelectNewBoard();
        }
    }
}

/* Mode play with Bot Hard */
eStatus PlayWithBotHard(ePiece piece)
{
    ClearScreen();

    CLargeBoard currentBoard;
    currentBoard.Setturn(piece);   // set first turn
    currentBoard.m_mode = BotHard; // mode with bot hard

    DrawBoards(currentBoard);

    int m_boardNum;
    GotoXY(xInput, yInput);
    cout << "Enter the board number to start with: ";

    /* Select board with both */
    switch (currentBoard.GetTurn())
    {
    case X:
        m_boardNum = InputData(); // player import from keyboard

        /*  Halfway exit & Lost */
        if (m_boardNum == 66) // user input 'r'
            return currentBoard.GetTurn() == Piece_X ? O : X;
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

            /*  Halfway exit & Lost */
            if (cell == 66) // user input 'r'
                return currentBoard.GetTurn() == Piece_X ? O : X;
            /**/
            
            break;

        case O:
            /*  Bot can find a way to win in current small board */
            GotoXY(xInput, yInput);
            cout << "Bot " << currentBoard.GetTurn() << ": select cell";
            GotoXY(xInput, yInput + 1);
            cell = BestMove(currentBoard, MoveNum(currentBoard));
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

        /* Check win large board */
        int status = currentBoard.CheckWin();

        if (status != NONE)
            DrawBoards(currentBoard);
        GotoXY(xInput, yInput + 2);
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

        currentBoard.ToggleTurn(); // change player

        /* Check board's status none or not to select new board */
        if (currentBoard.BoardFinished())
        {
            DrawBoards(currentBoard);
            currentBoard.SelectNewBoard();
        }
    }
}

/* Mode re-watch the latest match */
void RecordGame()
{
    CLargeBoard currBoards; // current Board

    stack<CLargeBoard> temp;

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
