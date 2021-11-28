#ifndef _graphics_h_
#define _graphics_h_

enum Colors
{
    red = 12,
    pink = 13,
    yellow = 14,
    white = 15
};

void Clear_Screen(void);
void Goto_xy(int, int);
void Draw_select(int);
void Set_colorText(Colors);

/*******  Information  *******/
void Information(void);
void Infor_LargeBoard(void);

#endif