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
        Goto_xy(7, 22);
        cout << "Re-Enter: ";
    }
    return (int)data - 48;
}