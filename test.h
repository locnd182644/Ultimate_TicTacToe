#ifndef _test_h_
#define _test_h_

/** Test minimax algorithm **/

#include "tic_tac_toe.h"
#include "handle.h"

void Display(cSmallBoard);

int RandomMove(void);

int Minimax(cSmallBoard, int, bool);

int BestMove(cSmallBoard, int);

void Test(void);

void DisplayUltimateTicTacToe(void);

#endif