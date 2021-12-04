#include <windows.h>
#include <stack>
#include "handle.h"
#include "mode.h"
#include "graphics.h"
#include "player_infor.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

#define SleepTime1000 1000

vector<cPlayerInfor> g_players;
extern stack<cLargeBoard> g_hisBoard;

void Start(void);
void Rules(void);

int main()
{
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open("Infor_Player.txt", ios::in);
    ReadInforListPlayer(fileIn, g_players);
    fileIn.close();

    fileOut.open("Infor_Player.txt", ios::out | ios::trunc); // mode write file

    Start();
    int choice1, choice2;
    while (1)
    {
        Clear_Screen();
        cPlayerInfor *pPlayer;
        string name;

        Set_colorText(green);
        cout << "Choose Options\n\n";
        Set_colorText(white);
        cout << "1. Start New Game\n";
        cout << "2. Information of player\n";
        cout << "3. How To Play\n";
        cout << "4. Quit\n\n";
        cout << "Option: ";

        cin >> choice1;
        switch (choice1)
        {
        case 1:
            cout << "Input your name: ";
            fflush(stdin); // clean buffer memory
            getline(cin, name);

            // Refer to current Player
            pPlayer = &g_players[iSearchPlayer(g_players, name)];

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
                    PlayWithFriend();
                    Sleep(SleepTime1000); // Screen pause for 1 seconds
                    break;
                case 2:
                    switch (PlayWithBotEasy())
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
                    Sleep(SleepTime1000); // Screen pause for 1 seconds
                    break;
                case 3:
                    switch (PlayWithBotNormal())
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
                    Sleep(SleepTime1000); // Screen pause for 1 seconds
                    break;
                case 5:
                    RecordGame();
                    Sleep(SleepTime1000); // Screen pause for 1 seconds
                    break;
                }
                if (choice2 == 6)
                    break;
            }

            break;

        case 2:
            Clear_Screen();
            WriteInforListPlayer_Screen(g_players);
            break;

        case 3:
            Clear_Screen();
            Rules();
            break;

        case 4:
            return 0;
        }
        WriteInforListPlayer_File(fileOut, g_players);
    }
    fileOut.close();
    return 0;
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
