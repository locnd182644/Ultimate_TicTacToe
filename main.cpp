#include <windows.h>
#include <stack>
#include "handle.h"
#include "mode.h"
#include "graphics.h"
#include "player_infor.h"
#include "ultimate_tic_tac_toe.h"

using namespace std;

#define SleepTime2000 2000

vector<cPlayerInfor> g_players;
extern stack<cLargeBoard> g_hisBoard;
cPlayerInfor *pPlayer[2];

void Start(void);
void Rules(void);

int main()
{
    ifstream fileIn;
    ofstream fileOut;

    fileIn.open("Infor_Player.txt", ios::in);
    ReadInforListPlayer(fileIn, g_players);
    fileIn.close();
    fileOut.open("Infor_Player.txt", ios::out | ios::trunc); // mode clean & write file

    Start();
    int choice1, choice2;
    while (1)
    {
        ClearScreen();
        SetColorText(green);
        cout << "Choose Options\n\n";
        SetColorText(white);
        cout << "1. Start New Game\n";
        cout << "2. Information of player\n";
        cout << "3. How To Play\n";
        cout << "4. Save Information & Exit\n\n";
        cout << "Option: ";
        choice1 = InputData(); // allows input from the keypad integers from 0 to 9
        switch (choice1)
        {
        case 1:

            pPlayer[0] = InputPlayerName(g_players); // import name of current player
            while (1)
            {

                ClearScreen();
                cout << "____  ";
                SetColorText(green);
                cout << pPlayer[0]->m_name; // Display current player name
                SetColorText(white);
                cout << "  ____\n\n";
                cout << "1. Play with friend \n";
                cout << "2. Play with Bot Easy\n";
                cout << "3. Play with Bot Normal\n";
                cout << "4. Play with Bot Hard\n";
                cout << "5. Watch the game again\n";
                cout << "6. Return\n\n";
                cout << "Option: ";
                choice2 = InputData();
                switch (choice2)
                {
                /*  Play with friend */
                case 1:
                    ClearScreen();
                    pPlayer[1] = InputPlayerName(g_players); // import name of the player to play with the current player
                    switch (PlayWithFriend(SelectFirstPlay(FRIEND)))
                    {
                    case X:
                        pPlayer[0]->m_win++;
                        pPlayer[1]->m_lose++;
                        break;
                    case O:
                        pPlayer[1]->m_win++;
                        pPlayer[0]->m_lose++;
                        break;
                    case TIE:
                        pPlayer[0]->m_tie++;
                        pPlayer[1]->m_tie++;
                        break;
                    }
                    Sleep(SleepTime2000); // screen pause for 2 seconds
                    break;

                /* Play with Bot Easy */
                case 2:
                    ClearScreen(); // clean Screen
                    switch (PlayWithBotEasy(SelectFirstPlay(BOT)))
                    {
                    case X:
                        pPlayer[0]->m_win++;
                        break;
                    case O:
                        pPlayer[0]->m_lose++;
                        break;
                    case TIE:
                        pPlayer[0]->m_tie++;
                        break;
                    }
                    Sleep(SleepTime2000); // screen pause for 2 seconds
                    break;

                /* Play with Bot Normal */
                case 3:
                    ClearScreen(); // clean Screen
                    switch (PlayWithBotNormal(SelectFirstPlay(BOT)))
                    {
                    case X:
                        pPlayer[0]->m_win++;
                        break;
                    case O:
                        pPlayer[0]->m_lose++;
                        break;
                    case TIE:
                        pPlayer[0]->m_tie++;
                        break;
                    }
                    Sleep(SleepTime2000); // screen pause for 2 seconds
                    break;

                case 5:
                    /* Re-watch the latest match */
                    RecordGame();
                    Sleep(SleepTime2000); // screen pause for 2 seconds
                    break;
                }

                /* Return Choose Options */
                if (choice2 == 6)
                    break;
            }
            break;

        case 2:
            ClearScreen();
            WriteInforListPlayerScreen(g_players); // display list of player information
            break;

        case 3:
            ClearScreen();
            Rules();
            break;

        case 4:
            /* Save information into file & Exit */
            WriteInforListPlayerFile(fileOut, g_players);
            fileOut.close();
            return 0;
        }
    }
}

void Start()
{
    ClearScreen();
    GotoXY(33, 9);
    cout << "*******************************";

    GotoXY(39, 11);
    SetColorText(green);
    cout << "ULTIMATE TIC TAC TOE";

    GotoXY(41, 13);
    cout << ">>>        <<<";

    GotoXY(45, 13);
    SetColorText(yellow);
    cout << "TEAM 5";
    GotoXY(35, 14);
    SetColorText(red);
    cout << "HN21_CPLU.HUST_LITE_CPP_01";
    SetColorText(white);

    GotoXY(33, 16);
    cout << "*******************************" << endl;

    GotoXY(36, 19);
    cout << "Press any key to continue";
    _getch();
}

void Rules()
{
    SetColorText(green);
    cout << "            HOW TO PLAY GAME\n\n";
    SetColorText(white);
    cout << "          1.Each turn, you mark one of the small squares.\n\n";
    cout << "          2.When you get three in a row on a small board, you have won that board.\n\n";
    cout << "          3.To win the game, you need to win three small boards in a row.\n\n";
    cout << "*** Note: You do not get to pick which of the nine boards to play on.\n";
    cout << "          That is determined by the previous Move of your opponent.\n";
    cout << "          Whichever square he picks, that is the board you must play in next.\n\n\n";
    cout << "          Press any key to continue....";
    _getch();
}
