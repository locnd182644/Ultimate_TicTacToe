#include "player_infor.h"
#include "graphics.h"

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

/** Return player's index in list **/
int iSearchPlayer(vector<cPlayerInfor> &listPlayer, string name)
{
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
    return i + 1;
}

/** Read Information of player from file **/
void ReadInforPlayer(ifstream &filein, cPlayerInfor &player)
{
    getline(filein, player.m_name, ',');
    filein >> player.m_win;
    filein >> player.m_tie;
    filein >> player.m_lose;
}

/** Read Information of player from file, then push on the list **/
void ReadInforListPlayer(ifstream &filein, vector<cPlayerInfor> &listPlayer)
{
    cPlayerInfor TempPlayer;
    while (!filein.eof()) // Check file end
    {
        ReadInforPlayer(filein, TempPlayer);
        listPlayer.push_back(TempPlayer);
    }
}

/** Export imformation of player on screen**/
void WriteInforListPlayer_Screen(vector<cPlayerInfor> listPlayer)
{
    cPlayerInfor tempPlayer;
    Set_colorText(green);
    cout << "Name\t\tWin\tTie\tLose\tWin rate\n\n";
    Set_colorText(white);
    for (int i = 0; i < listPlayer.size(); i++)
    {
        tempPlayer = listPlayer[i];
        cout << tempPlayer.m_name
             << "\t"
             << tempPlayer.m_win
             << "\t"
             << tempPlayer.m_tie
             << "\t"
             << tempPlayer.m_lose
             << "\t"
             << tempPlayer.WinRate() * 100 << " %"
             << "\n\n\n";
    }
    cout << "Press any key to continue....";
    _getch();
}

/** Save Players' list in file **/
void WriteInforListPlayer_File(ofstream &fileout, vector<cPlayerInfor> listPlayer)
{
    cPlayerInfor tempPlayer;
    for (int i = 0; i < listPlayer.size(); i++)
    {
        tempPlayer = listPlayer[i];
        fileout << tempPlayer.m_name
                << ",\n"
                << tempPlayer.m_win
                << "\n"
                << tempPlayer.m_tie
                << "\n"
                << tempPlayer.m_lose;
    }
}