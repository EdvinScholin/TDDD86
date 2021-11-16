// You will edit and turn in this CPP file.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace with your own

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
// TODO: include any other header files you need

void showBoard(Grid<string>& board) {
    //cout << board.toString();
    //cout << board.get(0, 0);

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
           cout << board.get(row, col) << " ";
        }
        cout << endl;
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)
    showBoard(boggle.getBoard());
}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
