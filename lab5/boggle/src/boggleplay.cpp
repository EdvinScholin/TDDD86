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
#include <regex>
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

string inputBoard(string prompt) {
    cout << prompt;
    string answer;
    getline(cin, answer);
    answer = trim(toUpperCase(answer));
    if (!regex_match(answer, regex("^[A-Z]{16}$"))) {
        inputBoard("Your board is not valid. Try again! ");
    }

    return answer;
}

void userWordInput(Boggle& boggle) {
    while (true) {
        cout << "Type a word (or press Enter to end your turn): ";
        string answer;
        getline(cin, answer);
        answer = trim(toUpperCase(answer));

        if (answer == "") {
            break;
        }

        else if (boggle.validWord(answer)) {
            cout << "You found a new word! " << answer << endl;
        }

        else {
            cout << "Not valid!" << endl;
        }
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    // TODO: implement this function (and add any other functions you like to help you)

    if (yesOrNo("Do you want to generate a random board? ")) {
        boggle.createBoard();
        showBoard(boggle.getBoard());
    }
    else {
        string input = inputBoard("Enter board letters: ");
        boggle.createBoard(input);
        showBoard(boggle.getBoard());
    }

    userWordInput(boggle);

    set<string> words = boggle.findAllWords();

    if (words.empty()) {
        cout << "found no words." << endl;
    }
    for (string word : words){
        cout << word << endl;
    }
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
