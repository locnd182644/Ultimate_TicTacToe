#include "handle.h"
#include "stack"
#include "graphics.h"

using namespace std;

extern vector<cPlayerInfor> g_players;
extern cPlayerInfor *pPlayer[2];

/* Allows input from the keypad integers from 0 to 9 */
int InputData()
{
    char data;
    while (1)
    {
        cin >> data;
        if ((int)data <= 57 && (int)data >= 48 || (int)data == 114)
            break;
        GotoXY(7, 22);
        cout << "Re-Enter: ";
    }
    return (int)data - 48;
}

/* Returns the first player */
PIECE SelectFirstPlay1()
{
    int option; // option
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

/* Returns the first player */
PIECE SelectFirstPlay2()
{
    int option; // option
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
}

/* Import name of player & Returns that cPlayerInfor obj's address in the vector list */
cPlayerInfor *InputPlayerName(vector<cPlayerInfor> &g_players)
{
    string name;
    cout << "Input your name: ";
    fflush(stdin); // clean buffer memory
    getline(cin, name);
    return &g_players[iSearchPlayer(g_players, name)]; // refer to current Player
}