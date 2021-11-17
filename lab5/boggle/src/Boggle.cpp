// This is the .cpp file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header and replace it with your own

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include "string.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
static const int rowAndColSize = 4;

Boggle::Boggle(){
    this->dict.addWordsFromFile("EnglishWords.dat");
    this->userChosenWords = {};
    //createBoard();
}

// TODO: implement the members you declared in Boggle.h
//Boggle::Boggle(string& playerChosenBoard) {
////    this->dict = dict;
//    createBoard(playerChosenBoard);
//}

//Boggle::Boggle(const Lexicon& dict){
//    this->dict = dict;
//    createBoard();
//}

/*
 * Creates board with the pre determined cubes and then shuffles board.
 */
void Boggle::createBoard() {
    int i = 0;
    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            this->board[row][col] = CUBES[i][randomInteger(0,5)];
            i++;
        }
    }
    shuffle(board);
}

/*
 * Creates board when player chooses what letters should be included.
 */
void Boggle::createBoard(string& playerChosenBoard) {
    int i = 0;
    for (int row = 0; row < rowAndColSize; row++) {
        for (int col = 0; col < rowAndColSize; col++) {
            this->board[row][col] = playerChosenBoard[i];
            i++;
        }
    }
}

Grid<string>& Boggle::getBoard() {
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

    userChosenWords.insert(word);
    return true;
}

bool Boggle::findWordInBoard(string word, vector<int[2]> visited, int row, int col) {
    if(this->board.get(row, col) == word.substr(0)) {
        visited.push_back({row, col});
        findWordInBoard(word.substr(1, word.size()-1), visited, )
    }

    if (word[0])
}

















