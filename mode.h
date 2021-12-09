#ifndef _mode_h_
#define _mode_h_

#include <stack>
#include <cstdlib> // random
#include <windows.h>
#include "ultimate_tic_tac_toe.h"

#define SleepTime500 500

/* Mode play with Friend */
eStatus PlayWithFriend(ePiece);

/* Mode play with Bot Easy */
eStatus PlayWithBotEasy(ePiece);

/* Mode play with Bot Normal */
eStatus PlayWithBotNormal(ePiece);

/* Mode play with Bot Hard */
eStatus PlayWithBotHard(ePiece);

/* Re-watch the latest match */
void RecordGame(void);

#endif