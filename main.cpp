#include <iostream>
#include <conio.h>
#include <string>
#include "extend.h"
#include <stack>
#include <windows.h>
#include "ultimate_tic_tac_toe.h"

using namespace std;

static string player[2];

/* Stack save Large Board to replay */
stack<Large_Board> his_board;

void Start(void);
void Rules(void);
int Play_with_Friend(void);
int Play_with_BotEasy(void);
void Record_Game(void);
void Enter_name(void);

int main()
{
    Start();
    int choice_1, choice_2, choice_3;
    while (1)
    {
        Clear_Screen();
        cout << "Choose Options\n\n1.Start New Game\n2.How To Play\n3.Quit\n\n";
        cout << "Option: ";
        cin >> choice_1;
        switch (choice_1)
        {
        case 1:
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
                cin >> choice_2;
                switch (choice_2)
                {
                case 1:
                    Play_with_Friend();
                    Sleep(2000); // Screen pause for 2 seconds
                    break;
                case 3:
                    Play_with_BotEasy();
                    Sleep(2000); // Screen pause for 2 seconds
                    break;
                case 5:
                    Record_Game();
                    Sleep(2000); // Screen pause for 2 seconds
                    break;
                }
                case 6:
                break;
            }
            break;

        case 2:
            Rules();
            break;

        case 3:
            break;
        }
    }

    return 0;
}
void Start()
{
    Clear_Screen();
    Goto_xy(33, 9);
    cout << "*******************************";

    Goto_xy(39, 11);
    cout << "ULTIMATE TIC TAC TOE";

    Goto_xy(41, 13);
    cout << ">>>        <<<";

    Set_colorText(yellow);
    Goto_xy(45, 13);
    cout << "TEAM 5";
    Set_colorText(red);
    Goto_xy(35, 14);
    cout << "HN21_CPLU.HUST_LITE_CPP_01";
    Set_colorText(white);

    Goto_xy(33, 16);
    cout << "*******************************" << endl;

    Goto_xy(36, 19);
    cout << "press any key to continue";
    _getch();
}
void Rules()
{
    Clear_Screen();
    cout << "1.Each turn, you mark one of the small squares..\n\n";
    cout << "2.When you get three in a row on a small board, you have won that board.\n\n";
    cout << "3.To win the game, you need to win three small boards in a row.\n\n";
    cout << "*** Note: You do not get to pick which of the nine boards to play on.\n";
    cout << "          That is determined by the previous Move of your opponent.\n";
    cout << "          Whichever square he picks, that is the board you must play in next.\n\n";
    cout << "Press any key to continue....";
    _getch();
}
int Play_with_Friend()
{
    Clear_Screen();

    /* Stack save Large Board to replay */
    stack<Large_Board> his_board;
    Large_Board current_board;

    Enter_name(); // Enter player name;

    current_board.DrawBoards();

    int board_num;
    cout << "       Enter the board number to start with: ";
    cin >> board_num;
    current_board.SetBoardNum(board_num);
    Draw_select(current_board.GetBoardNum() - 1);
    int cell;
    while (1)
    {
        his_board.push(current_board);
        current_board.DrawBoards();
        Goto_xy(7, 20);
        cout << "Player " << current_board.GetTurn() << ": select cell";

        Goto_xy(7, 21);
        cout << "Cell: ";
        while (1)
        {
            cin >> cell;
            if (cell <= 9 && cell >= 0)
                break;
            Goto_xy(7, 21);
            cout << "Re-Enter Cell: ";
        }

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (his_board.empty())
                    break;
                current_board = his_board.top();
                his_board.pop();
            }
            continue;
        }
        current_board.Move(cell);
        int status = current_board.CheckWin();
        current_board.DrawBoards();

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
        if (current_board.BoardFinished())
            current_board.SelectNewBoard();
    }
}
int Play_with_BotEasy()
{
    Clear_Screen();

    Large_Board current_board;

    current_board.DrawBoards();

    int board_num;
    cout << "       Enter the board number to start with: ";
    cin >> board_num;
    current_board.SetBoardNum(board_num);
    int cell;

    while (1)
    {
        his_board.push(current_board);
        current_board.DrawBoards();
        switch (current_board.GetTurn())
        {
        case X:
            Goto_xy(7, 20);
            cout << "Player " << current_board.GetTurn() << ": select cell";
            Goto_xy(7, 21);
            cout << "Cell: ";
            while (1)
            {
                cin >> cell;
                if (cell <= 9 && cell >= 0)
                    break;
                Goto_xy(7, 21);
                cout << "Re-Enter Cell: ";
            }
            break;

        case O:
            Goto_xy(7, 20);
            cout << "Bot " << current_board.GetTurn() << ": select cell";
            Goto_xy(7, 21);
            cell = FindBestMove(current_board);
            cout << "Cell: " << cell;
            break;
        }

        // If cell = 0, replay
        if (cell == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                if (his_board.empty())
                    break;
                current_board = his_board.top();
                his_board.pop();
            }
            continue;
        }

        current_board.Move(cell);
        int status = current_board.CheckWin();
        current_board.DrawBoards();

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
        if (current_board.BoardFinished())
            current_board.SelectNewBoard();
    }
}

void Enter_name()
{
    cout << "*** Note: Player 1 is always X" << endl;
    fflush(stdin);
    cout << "Enter player name 1: ";
    getline(cin, player[0]);
    cout << "Enter player name 2: ";
    getline(cin, player[1]);
}

void Record_Game()
{
    Large_Board curr_boards; // Current Board

    stack<Large_Board> temp;

    for (; !his_board.empty(); his_board.pop())
    {
        curr_boards = his_board.top();
        temp.push(curr_boards);
    }

    for (; !temp.empty(); temp.pop())
    {
        curr_boards = temp.top();
        curr_boards.DrawBoards();
        Sleep(500);
    }
}
