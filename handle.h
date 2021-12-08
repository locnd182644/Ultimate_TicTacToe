#ifndef _handle_h_
#define _handle_h_

#include <iostream>
#include "tic_tac_toe.h"
#include "ultimate_tic_tac_toe.h"
#include "player_infor.h"

/*  Handling input data from the keyboard */
int InputData(); // Allows input from the keypad integers from 0 to 9

/*  Handling select first to play */
PIECE SelectFirstPlay(MODE);

/******** Handling for BOT **********/

/*  Handling Easy Bot */
int BotSelectCell(cLargeBoard *);  // random with checked condition : Cell must be Piece_BLANK
int BotSelectBoard(cLargeBoard *); // random with checked condition: The small board must be NONE

/*  Handling Bots with minimax */
int Minimax(cSmallBoard, int, bool); // score of current small board
int BestMove(cLargeBoard, int);      // find best move for bot

/*  Handling Hard Bot */
int MoveNum(cLargeBoard); // the number of moves in current small board

#endif