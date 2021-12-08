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

class cPlayerInfor
{
public:
    int m_win;     // the number of win
    int m_tie;     // the number of tie
    int m_lose;    // the number of lose
    string m_name; // player name

    cPlayerInfor(); // initial method
    cPlayerInfor(string);
    int TotalMatch(); // the number of matchmak
    float WinRate();  // the rate of win
};

/** Import name of player, find, return player's index in list **/
int iSearchPlayer(vector<cPlayerInfor> &);

/* Find the player with the closest win rate */
int iFindCompetitor(vector<cPlayerInfor>, cPlayerInfor);

/* Smallest difference value of win rate */
float SmallestDifference(vector<cPlayerInfor> , cPlayerInfor );

/** Read Player's Information from file and add into cPlayerInfor object **/
void ReadInforPlayer(ifstream &, cPlayerInfor &);

/** Read Player's Information from file and add into list **/
void ReadInforListPlayer(ifstream &, vector<cPlayerInfor> &);

/** Display Players' list **/
void WriteInforListPlayerScreen(vector<cPlayerInfor>);

/** Save Players' list in file **/
void WriteInforListPlayerFile(ofstream &, vector<cPlayerInfor>);

/* Swap of 2 objects  */
template <class T>
void Swap(T &, T &);

/** Sort Players by win rate **/
vector<cPlayerInfor> SortInforPlayer(vector<cPlayerInfor>, SORT);

/* Display information of player with options */
void DisplayInforPlayer(vector<cPlayerInfor>);

#endif