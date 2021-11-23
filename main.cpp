#include <iostream>
#include <conio.h>
#include "ultimate_tic_tac_toe.cpp"

void Start()
{
    Clear_Screen();
    Goto_xy(33, 9);
    cout << "*****************************";
    Goto_xy(37, 11);
    cout << "ULTIMATE TIC TAC TOE";

    Goto_xy(33, 16);
    cout << "*****************************" << endl;
    Goto_xy(33, 17);

    Goto_xy(33, 19);

    cout << " press any key to continue";
    _getch();
}
void Rules()
{
    Clear_Screen();
    cout << "1.Each turn, you mark one of the small squares..\n\n";
    cout << "2.When you get three in a row on a small board, you’ve won that board.\n\n";
    cout << "3.To win the game, you need to win three small boards in a row.\n\n";
    cout << "*** Note: You do not get to pick which of the nine boards to play on. That is determined by the previous move of your opponent. Whichever square he picks, that is the board you must play in next.\n\n";
    cout << "Press any key to continue....";
    _getch();
}

void Play_game()
{
    Clear_Screen();
    Large_Board board;

    //Nhap_ten();
    board.displayBoards();

    int board_num;
    cout << "Enter the board number to start with: ";
    cin >> board_num;
    board.setBoardNum(board_num);
    board.Draw_select();
    int cell;
    bool playing = true;
    while (playing)
    {
        Goto_xy(0, 18);
        cout << "Player " << board.getTurn() << ": select cell" << endl;
        cout << "cell: ";
        cin >> cell;
        board.move(cell);
        board.displayBoards();
        int status = board.update();

        switch (status)
        {
        case X:
            cout << "X has won!" << endl;
            playing = false;
            break;
        case O:
            cout << "O has won!" << endl;
            playing = false;
            break;
        case TIE:
            cout << "Game over. Tie" << endl;
            playing = false;
            break;
        default:
            break;
        }
        if (board.boardFinished())
            board.selectNewBoard();
    }
}
int main()
{
    Large_Board game;
    Start();
    int choice;
    while (1)
    {
        Clear_Screen();
        cout << "Choose Options\n\n1.Start New Game\n2.How To Play\n3.Quit\n\n";
        cout << "Option: ";
        cin >> choice;
        if (choice == 1)
        {
            Play_game();
        }
        if (choice == 2)
        {
            Rules();
            continue;
        }
        if (choice == 3)
            break;
    }
    return 0;
}
