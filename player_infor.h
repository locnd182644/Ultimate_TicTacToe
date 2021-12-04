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
    int m_win;     // the number of win
    int m_tie;     // the number of tie
    int m_lose;    // the number of lose
    string m_name; // player name

    cPlayerInfor(); // Initial method
    cPlayerInfor(string);
    int TotalMatch(); // the number of matchmak 
    float WinRate();  // the rate of win
};

/** return player's index in list **/
int iSearchPlayer(vector<cPlayerInfor> &, string);

/** Read Player's Information from file and add into cPlayerInfor object **/
void ReadInforPlayer(ifstream &, cPlayerInfor &);

/** Read Player's Information from file and add into list **/
void ReadInforListPlayer(ifstream &, vector<cPlayerInfor> &);

/** Display Players' list **/
void WriteInforListPlayer_Screen(vector<cPlayerInfor>);

/** Save Players' list in file **/
void WriteInforListPlayer_File(ofstream &, vector<cPlayerInfor>);

#endif