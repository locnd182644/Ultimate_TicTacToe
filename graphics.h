#ifndef _graphics_h_
#define _graphics_h_

#include "ultimate_tic_tac_toe.h"

#define xBoardInfor 47 // X-coordinate of the Information Board
#define yBoardInfor 2  // Y-coordinate of the Information Board
#define hBoardInfor 16 // High of the Information Board
#define xInput 7    //  X-coordinate of input cell
#define yInput 19   //  y-coordinate of input cell

enum COLORS
{
    green = 10,
    red = 12,
    pink = 13,
    yellow = 14,
    white = 15
};

void ClearScreen(void);      // Clear the screen
void GotoXY(int, int);       // Set Coordinates of text poiter
void DrawSelect(int);        // Specify the current table
void SetColorText(COLORS);   // Set color of text
void DrawBoards(cLargeBoard); // Draw a large board

/*******  Information  *******/
void Information(cLargeBoard);       // Information Board
void InforStatusLargeBoard(cLargeBoard); // Information Status of Large Board
void DisplayCurrPlayer(cLargeBoard); // Display name of current player

#endif