#ifndef _player_infor_h_
#define _player_infor_h_

#include "tic_tac_toe.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class CPlayerInfor
{
public:
    int m_win;     // the number of win
    int m_tie;     // the number of tie
    int m_lose;    // the number of lose
    string m_name; // player name

    CPlayerInfor(); // initial method
    CPlayerInfor(string);
    int TotalMatch(); // the number of match 
    float WinRate();  // the rate of win
};

/** Import name of player, find, return player's index in list **/
int iSearchPlayer(vector<CPlayerInfor> &);

/** Find the player with the closest win rate **/
int iFindCompetitor(vector<CPlayerInfor>, CPlayerInfor);

/** Smallest difference value of win rate **/
float SmallestDifference(vector<CPlayerInfor> , CPlayerInfor );

/** Read Player's Information from file and add into CPlayerInfor object **/
void ReadInforPlayer(ifstream &, CPlayerInfor &);

/** Read Player's Information from file and add into list **/
void ReadInforListPlayer(ifstream &, vector<CPlayerInfor> &);

/** Display Players' list **/
void WriteInforListPlayerScreen(vector<CPlayerInfor>);

/** Save Players' list in file **/
void WriteInforListPlayerFile(ofstream &, vector<CPlayerInfor>);

/** Swap of 2 objects  **/
template <class T>
void Swap(T &, T &);

/** Sort Players by win rate **/
vector<CPlayerInfor> SortInforPlayer(vector<CPlayerInfor>, eSort);

/** Display information of player with options **/
void DisplayInforPlayer(vector<CPlayerInfor>);

#endif