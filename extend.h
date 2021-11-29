#ifndef _extend_h_
#define _extend_h_

#include "ultimate_tic_tac_toe.h"

//  Bot Normal
int EvaluateValue(SmallBoard);    // Score board of current
int FindBestMove(LargeBoard);     // Find best move for Bot Normal
int BotSelectCell(LargeBoard *);  // Random with condition check
int BotSelectBoard(LargeBoard *); // Random with condition check

// Handle input data from the keyboard
int InputData(); // Allows input from the keypad integers from 0 to 9

#endif