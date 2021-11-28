#ifndef _extend_h_
#define _extend_h_

#include "ultimate_tic_tac_toe.h"

//  Bot Normal
int EvaluateValue(Small_Board);
int FindBestMove(Large_Board);      // Find best move for Bot Normal
int BotSelectCell(Large_Board);     // Random with condition check
int BotSelectBoard(Large_Board);    // Random with condition check

#endif