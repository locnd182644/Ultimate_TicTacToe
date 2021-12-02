#include <windows.h>
#include <stack>
#include "handle.h"
#include "graphics.h"
#include "player_infor.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

#define SleepTime1000 1000

vector<cPlayerInfor> g_players;

/* Stack save Large Board to replay */
stack<LargeBoard> hisboard;

void Start(void);
void Rules(void);
int Play_with_Friend(void);
int Play_with_BotEasy(void);
int Play_with_BotNormal(void);
void Record_Game(void);
void Enter_name(void);

int main()
{
    fstream filein;
    filein.open("Infor_Player.txt", ios::in);
    ReadInforListPlayer(filein, g_players);
    Start();
    int choice1, choice2;
    while (1)
    {
        Clear_Screen();
        cPlayerInfor *pPlayer;
        string name;
        cout << "Choose Options\n\n1. Start New Game\n2. Information of player\n3. How To Play\n4. Quit\n\n";
        cout << "Option: ";
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            cout << "Input your name: ";
            fflush(stdin); // lam sach bo nho dem
            getline(cin, name);

            // Refer current Player
            pPlayer = &g_players[iSeachPlayer(g_players, name)];

            while (1)
            {

                Clear_Screen();
                cout << "____NEW GAME____\n\n";
                cout << "1. Play with friend \n";
                cout << "2. Play with Bot Easy\n";
                cout << "3. Play with Bot Normal\n";
                cout << "4. Play with Bot Hard\n";
                cout << "5. Watch the game again\n";
                cout << "6. Return\n\n";
                cout << "Option: ";
                cin >> choice2;
                switch (choice2)
                {
                case 1:
                    Enter_name();
                    Play_with_Friend();
                    break;
                case 2:
                    switch (Play_with_BotEasy())
                    {
                    case X:
                        pPlayer->m_win++;
                        break;
                    case O:
                        pPlayer->m_lose++;
                        break;
                    case TIE:
                        pPlayer->m_tie++;
                        break;
                    }
                    break;
                case 3:
                    switch (Play_with_BotNormal())
                    {
                    case X:
                        pPlayer->m_win++;
                        break;
                    case O:
                        pPlayer->m_lose++;
                        break;
                    case TIE:
                        pPlayer->m_tie++;
                        break;
                    }
                    break;
                case 5:
                    Record_Game();
                    break;
                }
                if (choice2 == 6)
                    break;
            }

            break;

        case 2:
            Clear_Screen();
            ExportInforListPlayer(g_players);
            break;

        case 3:
            Clear_Screen();
            Rules();
            break;

        case 4:
            return 0;
        }
    }
}
void Start()
{
    Clear_Screen();
    Goto_xy(33, 9);
    cout << "*******************************";

    Goto_xy(39, 11);
    Set_colorText(green);
    cout << "ULTIMATE TIC TAC TOE";

    Goto_xy(41, 13);
    cout << ">>>        <<<";

    Goto_xy(45, 13);
    Set_colorText(yellow);
    cout << "TEAM 5";
    Goto_xy(35, 14);
    Set_colorText(red);
    cout << "HN21_CPLU.HUST_LITE_CPP_01";
    Set_colorText(white);

    Goto_xy(33, 16);
    cout << "*******************************" << endl;

    Goto_xy(36, 19);
    cout << "Press any key to continue";
    _getch();
}
void Rules()
{
    Set_colorText(green);
    cout << "            HOW TO PLAY GAME\n\n";
    Set_colorText(white);
    cout << "          1.Each turn, you mark one of the small squares.\n\n";
    cout << "          2.When you get three in a row on a small board, you have won that board.\n\n";
    cout << "          3.To win the game, you need to win three small boards in a row.\n\n";
    cout << "*** Note: You do not get to pick which of the nine boards to play on.\n";
    cout << "          That is determined by the previous Move of your opponent.\n";
    cout << "          Whichever square he picks, that is the board you must play in next.\n\n\n";
    cout << "          Press any key to continue....";
    _getch();
}
int Play_with_Friend()
{
    Clear_Screen();

    LargeBoard currentboard;
    currentboard.mode = 0;

    currentboard.DrawBoards();

    int board_num;
    Goto_xy(xInput, yInput);
    cout << "Enter the board number to start with: ";
    board_num = InputData();
    currentboard.SetBoardNum(board_num);
    Draw_select(currentboard.GetBoardNum() - 1);
    int cell;
    while (1)
    {
        hisboard.push(currentboard);
        currentboard.DrawBoards();
        Goto_xy(xInput, yInput);
        cout << "Player " << currentboard.GetTurn() << ": select cell";

        Goto_xy(xInput, yInput + 1);
        cout << "Cell: ";
        cell = InputData();

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (hisboard.empty())
                    break;
                currentboard = hisboard.top();
                hisboard.pop();
            }
            continue;
        }
        currentboard.Move(cell);
        int status = currentboard.CheckWin();
        currentboard.DrawBoards();

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

        if (currentboard.BoardFinished())
            currentboard.SelectNewBoard();
    }

    Sleep(SleepTime1000); // Screen pause for 1 seconds

    // Exit halfway
    return TIE;
}
int Play_with_BotNormal()
{
    Clear_Screen();

    LargeBoard currentboard;
    currentboard.mode = 1; // Mode with bot

    currentboard.DrawBoards();

    int board_num;
    Goto_xy(xInput, yInput);
    cout << "Enter the board number to start with: ";
    board_num = InputData();
    if (board_num == 66) // User input 'r'
        return TIE;
    currentboard.SetBoardNum(board_num);
    int cell;

    while (1)
    {
        hisboard.push(currentboard);
        currentboard.DrawBoards();
        switch (currentboard.GetTurn())
        {
        case X:
            Goto_xy(xInput, yInput);
            cout << "Player " << currentboard.GetTurn() << ": select cell";
            Goto_xy(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();
            if (cell == 66) // User input 'r'
                return TIE;
            break;

        case O:
            Goto_xy(xInput, yInput);
            cout << "Bot " << currentboard.GetTurn() << ": select cell";
            Goto_xy(xInput, yInput);
            cell = FindBestMove(currentboard);
            cout << "Cell: " << cell;
            break;
        }

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (hisboard.empty())
                    break;
                currentboard = hisboard.top();
                hisboard.pop();
            }
            continue;
        }

        currentboard.Move(cell);
        int status = currentboard.CheckWin();
        currentboard.DrawBoards();

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
        if (currentboard.BoardFinished())
            currentboard.SelectNewBoard();
    }

    Sleep(SleepTime1000); // Screen pause for 1 seconds

    // Exit halfway
    return TIE;
}
int Play_with_BotEasy()
{
    Clear_Screen();

    LargeBoard currentboard;
    currentboard.mode = 1; // Mode with bot

    currentboard.DrawBoards();

    int board_num;
    Goto_xy(xInput, yInput);
    cout << "Enter the board number to start with: ";
    board_num = InputData();
    if (board_num == 66) // User input 'r'
        return TIE;
    currentboard.SetBoardNum(board_num);
    int cell;

    while (1)
    {
        hisboard.push(currentboard);
        currentboard.DrawBoards();
        switch (currentboard.GetTurn())
        {
        case X:
            Goto_xy(xInput, yInput);
            cout << "Player " << currentboard.GetTurn() << ": select cell";
            Goto_xy(xInput, yInput + 1);
            cout << "Cell: ";
            cell = InputData();
            if (cell == 66) // User input 'r'
                return TIE;
            break;

        case O:
            Goto_xy(xInput, yInput);
            cout << "Bot " << currentboard.GetTurn() << ": select cell";
            Goto_xy(xInput, yInput + 1);
            cell = BotSelectCell(&currentboard);
            cout << "Cell: " << cell;
            break;
        }

        // If cell = 0 then replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (hisboard.empty())
                    break;
                currentboard = hisboard.top();
                hisboard.pop();
            }
            continue;
        }

        currentboard.Move(cell);
        int status = currentboard.CheckWin();

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
        if (currentboard.BoardFinished())
            currentboard.SelectNewBoard();
    }

    Sleep(SleepTime1000); // Screen pause for 1 seconds

    // Exit halfway
    return TIE;
}

void Enter_name()
{
}

void Record_Game()
{
    LargeBoard currboards; // Current Board

    stack<LargeBoard> temp;

    for (; !hisboard.empty(); hisboard.pop())
    {
        currboards = hisboard.top();
        temp.push(currboards);
    }

    for (; !temp.empty(); temp.pop())
    {
        currboards = temp.top();
        currboards.DrawBoards();
        Sleep(500);
    }

    Sleep(SleepTime1000); // Screen pause for 1 seconds
}
