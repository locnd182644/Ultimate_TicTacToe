#ifndef _mode_h_
#define _mode_h_

#include <stack>
#include <cstdlib> // random
#include <windows.h>
#include "ultimate_tic_tac_toe.h"

#define SleepTime500 500

/*  Handling Easy Bot */
int BotSelectCell(cLargeBoard *);  // random with checked condition : Cell must be Piece_BLANK
int BotSelectBoard(cLargeBoard *); // random with checked condition: The small board must be NONE 

/*  Handling Bots with minimax */
int Minimax(cSmallBoard, int, bool); // score of current small board
int BestMove(cLargeBoard, int);      // find best move for bot

/*  Handle Hard Bot */

/* Mode play with Friend */
STATUS PlayWithFriend(PIECE);

/* Mode play with Bot Easy */
STATUS PlayWithBotEasy(PIECE);

/* Mode play with Bot Normal */
STATUS PlayWithBotNormal(PIECE);

/* Re-watch the latest match */
void RecordGame(void);

#endif