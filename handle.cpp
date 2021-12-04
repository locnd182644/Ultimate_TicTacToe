#include "handle.h"
#include "graphics.h"

using namespace std;

/* Allows input from the keypad integers from 0 to 9 */
int InputData()
{
    char data;
    while (1)
    {
        cin >> data;
        if ((int)data <= 57 && (int)data >= 48 || (int)data == 114)
            break;
        GotoXY(7, 22);
        cout << "Re-Enter: ";
    }
    return (int)data - 48;
}

PIECE SelectFirstPlay()
{
    PIECE piece; // first turn
    int option;  // option
    cout << "*** NOTE: Bot is always O\n\n";
    SetColorText(green);
    cout << "Choose to play first: \n";
    SetColorText(white);
    cout << "1. Bot\n";
    cout << "2. Player\n";
    cout << "Option: ";
    while (1)
    {
        option = InputData();
        if (option == 1)
        {
            piece = Piece_O;
            break;
        }
        if (option == 2)
        {
            piece = Piece_X;
            break;
        }
    }
    return piece;
}