#ifndef _player_infor_h_
#define _player_infor_h_

#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

class cPlayerInfor
{

public:
    int m_win;
    int m_lose;
    int m_tie;
    string m_name;
    cPlayerInfor();
    cPlayerInfor(string);

    int TotalMatch();
    float WinRate();
};

/** **/
int iSeachPlayer(vector<cPlayerInfor>&, string);

/** **/
void ReadInforPlayer(fstream &, cPlayerInfor &);

void ReadInforListPlayer(fstream &, vector<cPlayerInfor> &);

void ExportInforListPlayer(vector<cPlayerInfor>);

#endif