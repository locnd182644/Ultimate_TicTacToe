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
        ClearScreen();
        cPlayerInfor *pPlayer;
        string name;
        SetColorText(green);
        cout << "Choose Options\n\n";
        SetColorText(white);
        cout << "1. Start New Game\n";
        cout << "2. Information of player\n";
        cout << "3. How To Play\n";
        cout << "4. Save Information & Quit\n\n";
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

                ClearScreen();
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
                    Sleep(SleepTime2000); // Screen pause for 2 seconds
                    break;
                case 2:
                    ClearScreen(); // clean Screen
                    switch (PlayWithBotEasy(SelectFirstPlay()))
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
                    Sleep(SleepTime2000); // Screen pause for 2 seconds
                    break;
                case 3:
                    ClearScreen(); // clean Screen
                    switch (PlayWithBotNormal(SelectFirstPlay()))
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
                    Sleep(SleepTime2000); // Screen pause for 2 seconds
                    break;
                case 5:
                    RecordGame();
                    Sleep(SleepTime2000); // Screen pause for 2 seconds
                    break;
                }
                if (choice2 == 6)
                    break;
            }

            break;

        case 2:
            ClearScreen();
            WriteInforListPlayerScreen(g_players);
            break;

        case 3:
            ClearScreen();
            Rules();
            break;

        case 4:
            WriteInforListPlayerFile(fileOut, g_players); // Chinh lai dinh dang viet vao
            fileOut.close();                              // Viết file đang không trùng với đọc file
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
