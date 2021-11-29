#ifndef _extend_h_
#define _extend_h_

#include "ultimate_tic_tac_toe.h"

//  Bot Normal
int EvaluateValue(Small_Board);
int FindBestMove(Large_Board);      // Find best move for Bot Normal
int BotSelectCell(Large_Board);     // Random with condition check
int BotSelectBoard(Large_Board);    // Random with condition check

// Handle input data from the keyboard
int InputData();                    // Allows input from the keypad integers from 0 to 9

#endif