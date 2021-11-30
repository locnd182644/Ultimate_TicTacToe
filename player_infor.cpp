#include <iostream>
#include "player_infor.h"

using namespace std;

Player_infor::Player_infor()
{
    name = "NULL";
    _win = 0;
    _lose = 0;
    _tie = 0;
}

Player_infor::Player_infor(string temp_name)
{
    name = temp_name;
    _win = 0;
    _lose = 0;
    _tie = 0;
}

int Player_infor::get_win()
{
    return _win;
}

int Player_infor::get_tie()
{
    return _tie;
}

int Player_infor::get_lose()
{
    return _lose;
}

void Player_infor::win()
{
    _win++;
}

void Player_infor::tie()
{
    _tie++;
}

void Player_infor::lose()
{
    _lose++;
}

int Player_infor::total_match()
{
    return _win + _tie + _lose;
}

float Player_infor::win_rate()
{
    return (total_match() == 0) ? 0 : (_win) / total_match();
}