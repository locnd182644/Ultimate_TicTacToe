#ifndef _graphics_h_
#define _graphics_h_

#include "ultimate_tic_tac_toe.h"

#define coord_X_Infor 60 // X-coordinate of the Information Board

enum Colors
{
    red = 12,
    pink = 13,
    yellow = 14,
    white = 15
};

void Clear_Screen(void);    // Clear the screen
void Goto_xy(int, int);     // Set Coordinates of text poiter
void Draw_select(int);      // Specify the current table 
void Set_colorText(Colors); // Set color of text

/*******  Information  *******/
void Information(LargeBoard*);      // Information Board
void Infor_LargeBoard(LargeBoard*); // Information Status of Large Board

#endif