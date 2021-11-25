/*
 * This assigment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 *
 * This file handles the visual elements of the Boggle game.
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <regex>

/*
 * Iterates over grid elements.
 */
void showBoard(Grid<string>& board) {
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
           cout << board.get(row, col) << " ";
        }
        cout << endl;
    }
}

/*
 * Sets the board to players input.
 */
string inputBoard(string prompt) {
    cout << prompt;
    string answer;
    getline(cin, answer);
    answer = trim(toUpperCase(answer));
    if (!regex_match(answer, regex("^[A-Z]{16}$"))) {
        answer = inputBoard("Your board is not valid. Try again! ");
    }

    return answer;
}

void printWords(set<string> words) {
    cout << "{";
    for (auto word: words) {
        cout << "\"" << word << "\", ";
    }
    cout << "}" << endl;
}

/*
 * Handles the interface of all rounds of the game.
 */
void userInterface(Boggle& boggle) {
    cout << "It's your turn!" << endl;
    showBoard(boggle.getBoard());

    string answer;

    while(true) {
        cout << "Your words (" << boggle.getUserChosenWords().size() << "): ";
        printWords(boggle.getUserChosenWords());
        cout << "Your score: " << boggle.getPoints() << endl;

        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, answer);
        answer = trim(toUpperCase(answer));

        if (answer == "") {
            break;
        }

        else if (boggle.validWord(answer) && boggle.foundWord(answer) == true) {
            cout << "You found a new word! " << answer << endl;
            boggle.addUserWord(answer);
            boggle.addPoint(answer);
        }

        else {
            cout << "Not valid!" << endl;
        }

        showBoard(boggle.getBoard());
        cout << endl;
    }
}

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {
    if (yesOrNo("Do you want to generate a random board? ")) {
        boggle.createBoard();
    }
    else {
        string input = inputBoard("Enter board letters: ");
        boggle.createBoard(input);

    }

    userInterface(boggle);

    cout << "It's my turn!" << endl;
    boggle.findAllWords();
    cout << "My words (" << boggle.getComputerWords().size() << "): ";
    printWords(boggle.getComputerWords());
    cout << "My score: " << boggle.getComputerPoints() << endl;

    if (boggle.getPoints() >= boggle.getComputerPoints()) {
        cout << "WOW, you defeated me! Congratulations!" << endl;
    }
    else {
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human!" << endl;
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
