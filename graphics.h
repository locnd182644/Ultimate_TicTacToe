#ifndef _graphics_h_
#define _graphics_h_

#include "ultimate_tic_tac_toe.h"

#define xBoardInfor 47 // x-coordinate of the Information Board
#define yBoardInfor 2  // y-coordinate of the Information Board
#define hBoardInfor 16 // high of the Information Board
#define xInput 7       //  X-coordinate of input cell
#define yInput 19      //  y-coordinate of input cell

enum eColors
{
    green = 10,
    red = 12,
    pink = 13,
    yellow = 14,
    white = 15
};

void ClearScreen(void);       // clear the screen
void GotoXY(int, int);        // set Coordinates of text poiter
void DrawSelect(int);         // dispaly specify the current table
void SetColorText(eColors);   // set color of text
void DrawBoards(CLargeBoard); // draw a large board

/*******  Information  *******/
void Information(CLargeBoard);           // dispaly Information Board
void InforStatusLargeBoard(CLargeBoard); // dispaly Information Status of Large Board
void DisplayCurrPlayer(CLargeBoard);     // display name of current player
void DisplayBoardsMode(CLargeBoard);     // display mode large board

#endif