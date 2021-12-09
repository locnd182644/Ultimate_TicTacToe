#ifndef _handle_h_
#define _handle_h_

#include <iostream>
#include "tic_tac_toe.h"
#include "ultimate_tic_tac_toe.h"
#include "player_infor.h"

/*  Handling input data from the keyboard */
int InputData(); // Allows input from the keypad integers from 0 to 9

/*  Handling select first to play */
ePiece SelectFirstPlay(eMode);

/******** Handling for BOT **********/

/*  Handling Easy Bot */
int BotSelectCell(CLargeBoard *);  // random with checked condition : Cell must be Piece_BLANK
int BotSelectBoard(CLargeBoard *); // random with checked condition: The small board must be NONE

/*  Handling Bots with minimax */
int Minimax(CSmallBoard, int, bool); // score of current small board
int BestMove(CLargeBoard, int);      // find best move for bot

/*  Handling Hard Bot */
int MoveNum(CLargeBoard); // the number of moves in current small board

#endif