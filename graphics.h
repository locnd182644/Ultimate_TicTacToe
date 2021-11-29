#ifndef _graphics_h_
#define _graphics_h_

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
void Information(void);      // Information Board
void Infor_LargeBoard(void); // Information Status of Large Board

#endif