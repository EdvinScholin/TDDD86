/*
 * This assignment is made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
 * Excecuting this program a game of hangman is intialized. The code is built
 * to deceive the user. The algorithm will not choose a word beforehand,
 * rather it will wait to choose a word until the user has guessed letters
 * so that there is only one possible word to spell out left.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <vector>
#include <unordered_set>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Saves all the words in the english dictionary to an
 * unordered set.
 */
void saveDictionary(unordered_map<int, unordered_set<string>>& dict) {
    string filename = "dictionary.txt";
    ifstream input;
    input.open(filename.c_str());
    string word;

    while (getline(input, word)) {
        dict[word.length()].insert(word);
    }
    input.close();
}

/*
 * User chooses a length for the word for which the user is going to
 * guess.
 */
void askUserForLength(unordered_map<int, unordered_set<string>> const& dict, int& length) {
    string input = "";
    bool isNumber = true;
    cout << "What length is your desired word? ";
    cin >> input;
    cout << endl;

    for (char const&c : input) {
        if (isdigit(c) == false) {
            isNumber = false;
        }
    }

    if (isNumber == true) {
        length = stoi(input);
        if (dict.find(length) != dict.end()) {
            cout << "Words with the length of " << length << " is " << dict.at(length).size() << endl;
        }

        else {
            cout << "The word is not of length of a word in the english dictionary, pick another." << endl;
            askUserForLength(dict, length);
        }
    }

    else {
        cout << "Not a number." << endl;
        askUserForLength(dict, length);
    }

}

/*
 * User chooses a number of guesses to guess the right word.
 */
void askUserForGuesses(int& guesses) {
    string input;
    bool isNumber = true;
    cout << "How many guesses do you want? ";
    cin >> input;
    cout << endl;

    for (char const&c : input) {
        if (isdigit(c) == false) {
            isNumber = false;
        }
    }

    if (isNumber == true) {
        if (stoi(input) > 0) {
            guesses = stoi(input);
        }

        else {
            cout << "Your guesses have to be more than 0, try again." << endl;
            askUserForGuesses(guesses);
        }
    }

    else {
        cout << "Not a number." << endl;
        askUserForGuesses(guesses);
    }
}

/*
 * The user chooses if the user wants to see how many words are left for the
 * computer to choose from (anwser yes for testing/grading).
 */
bool askUserForInterface() {
    string answer;
    cout << "Do you want to see the amount of words left in the dictionary after each guess, y/n? ";
    cin >> answer;

    if (answer == "y") {
        return true;
    }

    else if (answer == "n") {
        return false;
    }

    else {
        cout << "y/n, try again." << endl;
        askUserForInterface();
    }

    return false;
}

/*
 * User guesses a letter for the word and the method adds the guessed letter to
 * the string of guessed letters.
 */
void askUserForALetter(string& guessedLetters, char& letter) {
    string input;
    cout << "Guess a letter: ";
    cin >> input;

    if (guessedLetters.find(input) != string::npos || ALPHABET.find(input) == string::npos || input.size() != 1) {
        cout << "Error, try again." << endl;
        askUserForALetter(guessedLetters, letter);
    }

    else {
        guessedLetters += input;
        letter = input[0];
    }
}

/*
 * Adds lines for the hidden letters in the word, adds the correct guessed letters to the word,
 * decrement guesses for wrong guess and prints guesses left, guessed letters and the word with
 * lines and letters.
 */
void gameInterface(string& currentWord, vector<int> const& largestFamilyKey, string const& guessedLetters, int& guesses, int const& length) {
    if (currentWord == "") {
        for (int i = 0; i < length; i++) {
            currentWord += '-';
        }
    }

    else if (!largestFamilyKey.empty()) {
        for (int i : largestFamilyKey) {
            currentWord[i] = guessedLetters[guessedLetters.length()-1];
        }
    }

    else if (largestFamilyKey.empty()) {
        guesses--;
    }

    cout << "Guesses left: " << guesses << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    cout << "Word: " << currentWord << endl;
}

/*
 * Checks what type of families the guess generates. The content of the map of families that are
 * referenced as a parameter is replaced with the new families the new guess generates. A vector of
 * integers contains the potential positions that the letter guessed may have.
 */
void checkFamilies(unordered_set<string> const& largestFamily, char const letter, map<vector<int>, unordered_set<string>>& families) {
    families = {{},{}};

    for (string const& word : largestFamily) {
        vector<int> matchingPos;
        for (int i=0; i < word.size(); i++) {
           if (word[i] == letter) {
                matchingPos.push_back(i);
           }
        }
        families[matchingPos].insert(word);
    }
}

/*
 * Returns the family that has the most occurences in the multimap with different types of
 * families.
 */
void checkMostCommonFamily(map<vector<int>, unordered_set<string>> const& families, unordered_set<string>& largestFamily, vector<int>& largestFamilyKey) {
    int max = 0;
    largestFamily = {};

    for (pair<vector<int>, unordered_set<string>> const& family : families) {
        if (family.second.size() > max) {
            max = family.second.size();
            largestFamily = family.second;
            largestFamilyKey = family.first;
        }
    }
}

/*
 * Generates the user interface and checks whether the user has won or lost to
 * the computer. Otherwise the method calls all necessary methods for the game
 * to continue. The method also shows all words if the user has allowed it.
 */
void game(string& currentWord, string& guessedLetters, int& guesses, unordered_set<string>& largestFamily, bool& gameOver, bool showWordsLeft,
          map<vector<int>, unordered_set<string>>& families, vector<int>& largestFamilyKey, int length) {
    char letter;
    gameInterface(currentWord, largestFamilyKey, guessedLetters, guesses, length);

    if (guesses > 0) {
        if (currentWord.find('-') == string::npos) {
            gameOver = true;
            cout << "Congratulations! YOU WON!!!" << endl;
        }
        else {
            askUserForALetter(guessedLetters, letter);
            checkFamilies(largestFamily, letter, families);
            checkMostCommonFamily(families, largestFamily, largestFamilyKey);
            if (showWordsLeft == true) {
                cout << "Words left: " << largestFamily.size() << endl;
            }
        }
    }

    else {
        gameOver = true;
        cout << "Congratualtions! You lost!" << endl;
        cout << "The word we were thinking of was " << *begin(largestFamily) << endl;
    }
}

int main() {
    cout << "Welcome to Hangman." << endl;
    unordered_map<int, unordered_set<string>> dict;
    saveDictionary(dict);
    bool playAgain = true;
    string currentWord;
    unordered_set<string> largestFamily;
    vector<int> largestFamilyKey;
    map<vector<int>, unordered_set<string>> families;
    string guessedLetters;
    int guesses;
    int length;
    bool gameOver;
    bool showWordsLeft;

    while(playAgain) {
        currentWord = "";

        largestFamilyKey = {};
        length = 0;
        askUserForLength(dict, length);
        largestFamily = dict[length];

        guessedLetters = "";
        guesses = 0;
        askUserForGuesses(guesses);

        gameOver = false;
        showWordsLeft = askUserForInterface();

        while(!gameOver) {
             game(currentWord, guessedLetters, guesses, largestFamily, gameOver, showWordsLeft, families, largestFamilyKey, length);
        }

        cout << "Do you want to play again? (y/n): ";
        char answer;
        cin >> answer;
        cout << endl;
        if(answer == 'n') {
            playAgain = false;
        }
    }
}















