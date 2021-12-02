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

int iSeachPlayer(vector<cPlayerInfor> &listPlayer, string name)
{
    int i;
    // Duyet danh sach, neu co ten nguoi choi tra ve chi so nguoi choi trong danh sach
    for (i = 0; i < listPlayer.size(); i++)
    {
        if (listPlayer[i].m_name == name)
            return i;
    }

    // neu khong thi tao nguoi choi moi va tra ve chi so
    cPlayerInfor newPlayer(name);
    listPlayer.push_back(newPlayer);
    return i + 1;
}

/** Read Information of player from file **/
void ReadInforPlayer(fstream &filein, cPlayerInfor &player)
{
    getline(filein, player.m_name, ',');
    filein >> player.m_win;
    filein >> player.m_tie;
    filein >> player.m_lose;
}

/** Read Information of player from file, then push on the list **/
void ReadInforListPlayer(fstream &filein, vector<cPlayerInfor> &listPlayer)
{
    cPlayerInfor TempPlayer;
    while (!filein.eof()) // Check end file
    {
        ReadInforPlayer(filein, TempPlayer);
        listPlayer.push_back(TempPlayer);
    }
}

/** Export imformation of player to screen**/
void ExportInforListPlayer(vector<cPlayerInfor> listPlayer)
{
    cPlayerInfor tempPlayer;
    Set_colorText(green);
    cout << "Name\t\tWin\tTie\tLose\tWin Rate\n\n";
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