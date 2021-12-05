#ifndef _handle_h_
#define _handle_h_

#include <iostream>
#include "tic_tac_toe.h"
#include "player_infor.h"

/* Handle input data from the keyboard */
int InputData(); // Allows input from the keypad integers from 0 to 9

/* Select first to play */
PIECE SelectFirstPlay1();

/* Select first to play */
PIECE SelectFirstPlay2();

/* Import name of player & Returns that cPlayerInfor obj's address in the vector list */
cPlayerInfor *InputPlayerName(vector<cPlayerInfor> &);

#endif