/*
 * This assigment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 *
 * This cpp file contains the implementation of the Boggle class. See header file to
 * view a description of the methods.
 */

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "string.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
static const int rowAndColSize = 4; // the row and column size of the grid

Boggle::Boggle(){
    this->dict.addWordsFromFile("EnglishWords.dat");
}

void Boggle::createBoard() {
    this->userChosenWords = {};
    this->computerWords = {};
    this->points = 0;
    this->computerPoints = 0;
    int i = 0;
    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            this->board[row][col] = CUBES[i][randomInteger(0,5)];
            i++;
        }
    }
    shuffle(board);
}

void Boggle::createBoard(string& playerChosenBoard) {
    this->userChosenWords = {};
    this->computerWords = {};
    this->points = 0;
    this->computerPoints = 0;
    int i = 0;
    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            this->board[row][col] = playerChosenBoard[i];
            i++;
        }
    }
}

Grid<string> const& Boggle::getBoard() {
    return this->board;
}

bool Boggle::validWord(string word) {
    if (userChosenWords.find(word) != userChosenWords.end()) {
        return false;
    }

    else if (word.size() < 4) {
        return false;
    }

    else if (!dict.contains(word)) {
        return false;
    }

    return true;
}

void Boggle::findAllWordsHelper(set<pair<int, int>>& visited, int row, int col, string& possibleWord) {
    visited.insert({row, col});
    possibleWord += board.get(row, col);

    if (possibleWord.size() >= 4 && dict.contains(possibleWord) && userChosenWords.find(possibleWord) == userChosenWords.end()) {
        computerWords.insert(possibleWord);
    }

    for (int inner_row = row-1; inner_row < row + 2; inner_row++) {
        for (int inner_col = col-1; inner_col < col + 2; inner_col++) {
            if(board.inBounds(inner_row, inner_col) && visited.find({inner_row,inner_col}) == visited.end()) {
                if (dict.containsPrefix(possibleWord)) {
                    findAllWordsHelper(visited, inner_row, inner_col, possibleWord);
                }
            }
        }
    }

    possibleWord.erase(possibleWord.size() - 1);
    visited.erase({row, col});
}

void Boggle::findAllWords() {
    set<string> foundWords;
    set<pair<int, int>> visited;
    string possibleWord = "";


    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            findAllWordsHelper(visited, row, col, possibleWord);
        }
    }

    computerPoints = calculateComputerPoints();
}


bool Boggle::foundWordHelper(string& word, string possibleWord, set<pair<int, int>>& visited, int row, int col){
    if (possibleWord == ""){
        return true;
    }

    else {
        visited.insert({row, col});

        for (int inner_row = row-1; inner_row < row + 2; inner_row++) {
            for (int inner_col = col-1; inner_col < col + 2; inner_col++) {
                if (board.inBounds(inner_row, inner_col) && visited.find({inner_row,inner_col}) == visited.end()) {
                    if (possibleWord.substr(0,1) == board.get(inner_row, inner_col)) {
                        if (foundWordHelper(word, possibleWord.substr(1), visited, inner_row, inner_col)) {
                            return true;
                        }
                    }
                }
            }
        }
        visited.erase({row, col});

    }
    return false;
}

bool Boggle::foundWord(string& word) {
    set<string> foundWords;
    set<pair<int, int>> visited;

    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            if (word.substr(0,1) == board.get(row, col)) {
                if (foundWordHelper(word, word.substr(1), visited, row, col)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Boggle::addPoint(string const& word) {
    int lettersOverFour = word.size() - 3;
    points += lettersOverFour;
}

void Boggle::addUserWord(string const& word) {
    userChosenWords.insert(word);
}

int Boggle::getPoints() {
    return points;
}

int Boggle::getComputerPoints() {
    return computerPoints;
}

set<string>& Boggle::getUserChosenWords() {
    return userChosenWords;
}

set<string>& Boggle::getComputerWords() {
    return computerWords;
}

int Boggle::calculateComputerPoints() {
    int points = 0;
    for (auto word : computerWords) {
        points += word.length()-3;
    }
    return points;
}




