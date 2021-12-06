#include "player_infor.h"
#include "graphics.h"
#include "handle.h"

using namespace std;

cPlayerInfor::cPlayerInfor()
{
    m_name = "NULL";
    m_win = 0;
    m_tie = 0;
    m_lose = 0;
}

cPlayerInfor::cPlayerInfor(string TempName)
{
    m_name = TempName;
    m_win = 0;
    m_tie = 0;
    m_lose = 0;
}

int cPlayerInfor::TotalMatch()
{
    return m_win + m_tie + m_lose;
}

float cPlayerInfor::WinRate()
{
    return (TotalMatch() == 0) ? 0 : (m_win) / (float)TotalMatch();
}

/** Import name of player
/** Return player's index in list **/
int iSearchPlayer(vector<cPlayerInfor> &listPlayer)
{
    string name;
    cout << "Input your name: ";
    fflush(stdin); // clean buffer memory
    getline(cin, name);
    int i;
    /* Browse the list, if the player name already exists,
       return the index of players in the list */
    for (i = 0; i < listPlayer.size(); i++)
    {
        if (listPlayer[i].m_name == name)
            return i;
    }

    /* if not then create new player */
    cPlayerInfor newPlayer(name);
    listPlayer.push_back(newPlayer);
    return i;
}

/* Find the player with the closest win rate */
// maximum difference 10 %
/* Return player's index in list or return -1 */
int iFindCompetitor(vector<cPlayerInfor> listPlayer, cPlayerInfor currPlayer)
{
    /* if a win rate difference of more than 10% % then return -1 */
    if (SmallestDifference(listPlayer, currPlayer) > 0.1)
        return -1;

    for (int i = 0; i < listPlayer.size(); i++)
    {
        /* Skip current turn */
        if (listPlayer[i].m_name == currPlayer.m_name)
            continue;

        /* Check the player with the closest win rate to current player
         */
        if (abs(listPlayer[i].WinRate() - currPlayer.WinRate()) == SmallestDifference(listPlayer, currPlayer))
        {
            return i;
        }
    }
}

/* Smallest difference value of win rate */
float SmallestDifference(vector<cPlayerInfor> listPlayer, cPlayerInfor currPlayer)
{
    // offset: difference of win rate
    float offset = 1; // 100 %
    for (int i = 0; i < listPlayer.size(); i++)
    {
        /* Skip current turn */
        if (listPlayer[i].m_name == currPlayer.m_name)
            continue;
        
        /* Compare offset */
        if (abs(listPlayer[i].WinRate() - currPlayer.WinRate()) < offset)
            offset = abs(listPlayer[i].WinRate() - currPlayer.WinRate());
    }
    return offset;
}

/** Read Information of player from file **/
void ReadInforPlayer(ifstream &filein, cPlayerInfor &player)
{
    getline(filein, player.m_name, ',');
    if (player.m_name[0] == '\n')
        player.m_name.erase(player.m_name.begin()); // Clear first character ('\n')
    filein >> player.m_win;
    filein >> player.m_tie;
    filein >> player.m_lose;
}

/** Read Information of player from file, then push on the list **/
void ReadInforListPlayer(ifstream &filein, vector<cPlayerInfor> &listPlayer)
{
    cPlayerInfor tempPlayer;
    while (!filein.eof()) // Check file end
    {
        ReadInforPlayer(filein, tempPlayer);
        listPlayer.push_back(tempPlayer);
    }
}

/** Display imformation of player on screen**/
void WriteInforListPlayerScreen(vector<cPlayerInfor> listPlayer)
{
    cPlayerInfor tempPlayer;
    SetColorText(green);
    cout << "Name\t\t\tWin\tTie\tLose\tWin rate\n\n";
    SetColorText(white);
    for (int i = 0; i < listPlayer.size(); i++)
    {
        tempPlayer = listPlayer[i];
        cout << tempPlayer.m_name
             << "\t\t"
             << tempPlayer.m_win
             << "\t"
             << tempPlayer.m_tie
             << "\t"
             << tempPlayer.m_lose
             << "\t"
             << tempPlayer.WinRate() * 100 << " %"
             << "\n\n\n";
    }
}

/** Save Players' list in file **/
void WriteInforListPlayerFile(ofstream &fileout, vector<cPlayerInfor> listPlayer)
{
    cPlayerInfor tempPlayer;

    for (int i = 0; i < listPlayer.size(); i++)
    {
        tempPlayer = listPlayer[i];
        fileout << "\n"
                << tempPlayer.m_name
                << ",\n"
                << tempPlayer.m_win
                << "\n"
                << tempPlayer.m_tie
                << "\n"
                << tempPlayer.m_lose;
    }
}

/* Swap of 2 objects  */
template <class T>
void Swap(T &a, T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}

/** Sort Players by win rate **/ /* Bubble sort */
vector<cPlayerInfor> SortInforPlayer(vector<cPlayerInfor> listPlayer, SORT mode)
{
    switch (mode)
    {
    case INCREASE:
        for (int i = 0; i < listPlayer.size() - 1; i++)
            for (int j = listPlayer.size() - 1; j > i; j--)
                /* Compare win rate */
                if (listPlayer[j - 1].WinRate() > listPlayer[j].WinRate())
                    Swap(listPlayer[j], listPlayer[j - 1]);
        break;

    case DECREASE:
        for (int i = 0; i < listPlayer.size() - 1; i++)
            for (int j = listPlayer.size() - 1; j > i; j--)
                /* Compare win rate */
                if (listPlayer[j - 1].WinRate() < listPlayer[j].WinRate())
                    Swap(listPlayer[j], listPlayer[j - 1]);
        break;
    }
    return listPlayer;
}

/* Display information of player with options */
void DisplayInforPlayer(vector<cPlayerInfor> listPlayer)
{
    int option = 1;
    while (1)
    {
        switch (option)
        {
            /* Display by the history of creating player */
        case 1:
            ClearScreen();
            WriteInforListPlayerScreen(listPlayer);
            break;

            /* Displayed by decrease win rate */
        case 2:
            ClearScreen();
            /* D */
            WriteInforListPlayerScreen(SortInforPlayer(listPlayer, DECREASE));
            break;

            /*  Displayed by increase win rate */
        case 3:
            ClearScreen();
            WriteInforListPlayerScreen(SortInforPlayer(listPlayer, INCREASE));
            break;

        case 4:
            return;
        default:
            ClearScreen();
        }
        SetColorText(green);
        cout << "Choose: \n";
        cout << "1. Display by the history of creating player\n";
        cout << "2. Display by decrease win rate\n";
        cout << "3. Display by increase win rate\n";
        cout << "4. Return\n\n";
        SetColorText(white);
        cout << "Option: ";
        option = InputData();
    }
}
