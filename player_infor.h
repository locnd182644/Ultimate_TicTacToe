#ifndef _player_infor_h_
#define _player_infor_h_

#include <iostream>
#include <string>

using namespace std;

class Player_infor
{
private:
    int _win;
    int _lose;
    int _tie;

public:
    string name;
    Player_infor();
    Player_infor(string);

    int get_win();
    int get_tie();
    int get_lose();

    void win();
    void tie();
    void lose();

    int total_match();
    float win_rate();
};

#endif