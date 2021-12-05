#ifndef _mode_h_
#define _mode_h_

#include <stack>
#include <cstdlib> // Random
#include <windows.h>
#include "ultimate_tic_tac_toe.h"

#define SleepTime500 500

/*  Handle Bot Easy */
int BotSelectCell(cLargeBoard *);  // Random with condition check
int BotSelectBoard(cLargeBoard *); // Random with condition check

/*  Handle Bot Normal */
int EvaluateValue(cSmallBoard); // Score of current small board
int FindBestMove(cLargeBoard);  // Find best move for Bot Normal

/*  Handle Bot Hard */

/* Mode play with Friend */
STATUS PlayWithFriend(PIECE);

/* Mode play with Bot Easy */
STATUS PlayWithBotEasy(PIECE);

/* Mode play with Bot Normal */
STATUS PlayWithBotNormal(PIECE);

/* Re-watch the latest match */
void RecordGame(void);

#endif