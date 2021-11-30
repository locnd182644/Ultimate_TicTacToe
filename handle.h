#ifndef _handle_h_
#define _handle_h_

#include "ultimate_tic_tac_toe.h"

// Handle input data from the keyboard
int InputData(); // Allows input from the keypad integers from 0 to 9

//  Handle Bot Easy
int BotSelectCell(LargeBoard *);  // Random with condition check
int BotSelectBoard(LargeBoard *); // Random with condition check

//  Handle Bot Normal
int EvaluateValue(SmallBoard);    // Score board of current
int FindBestMove(LargeBoard);     // Find best move for Bot Normal

//  Handle Bot Hard

#endif