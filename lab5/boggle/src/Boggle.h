/*
 * This assigment was made by Edvin Schölin (edvsc779) and Wilmer Segerstedt (wilse150).
 *
 * This is the header file of the game Boggle. See boggle.cpp for the implementation of
 * the methods.
 */

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include <set>
#include <grid.h>
#include <lexicon.h>
#include <vector>
#include <utility>

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

    /*
     * Creates board with the pre determined cubes and then shuffles board.
     */
    void createBoard();

    /*
     * Creates board when player chooses what letters should be included.
     */
    void createBoard(string& playerChosenBoard);

    /*
     * Returns the board.
     */
    Grid<string> const& getBoard();

    /*
     * Checks if inputed word is valid.
     */
    bool validWord(string word);

    /*
     * Helper function for the foundWord() method. Uses recursive backtracking.
     */
    bool foundWordHelper(string& word, string possibleWord, set<pair<int, int>>& visited, int row, int col);

    /*
     * Uses helper function to check if a given word is in board.
     */
    bool foundWord(string& word);

    /*
     * Helper function for the findAllWords() method. Uses recursive backtracking.
     */
    void findAllWordsHelper(set<pair<int, int>>& visited, int row, int col, string& possibleWord);

    /*
     * Uses helper function to let the computer find all words in the board.
     */
    void findAllWords();

    /*
     * Adds appropriate amounts of points for a given word.
     */
    void addPoint(string const& word);

    /*
     * Adds given word to userChosenWords.
     */
    void addUserWord(string const& word);

    /*
     * Returns player points.
     */
    int getPoints();

    /*
     * Returns the computer points.
     */
    int getComputerPoints();

    /*
     * Returns set of words the user has answered correctly.
     */
    set<string>& getUserChosenWords();

    /*
     * Returns all the words the player couldn't find.
     */
    set<string>& getComputerWords();

    /*
     * Returns the sum of points from the words the computer has found.
     */
    int calculateComputerPoints();


private:
    Grid<string> board = Grid<string>(4,4);
    Lexicon dict;
    set<string> userChosenWords;
    set<string> computerWords;
    int points;
    int computerPoints;
};

#endif
