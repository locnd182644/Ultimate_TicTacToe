#ifndef _mode_h_
#define _mode_h_

#include <stack>
#include <cstdlib> // random
#include <windows.h>
#include "ultimate_tic_tac_toe.h"

#define SleepTime500 500

/* Mode play with Friend */
STATUS PlayWithFriend(PIECE);

/* Mode play with Bot Easy */
STATUS PlayWithBotEasy(PIECE);

/* Mode play with Bot Normal */
STATUS PlayWithBotNormal(PIECE);

/* Mode play with Bot Hard */
STATUS PlayWithBotHard(PIECE);

/* Re-watch the latest match */
void RecordGame(void);

#endif