#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

/*
 * Saves all the words in the english dictionary to an
 * unordered set.
 */
void saveDictionary(unordered_multimap<int, string>& dict) {
    int length = 0;
    pair<int, string> pair;
    string filename = "dictionary.txt";
    ifstream input;
    input.open(filename.c_str());
    string line;

    while (getline(input, line)) {
        length = line.length();
        pair.first = length;
        pair.second = line;
        dict.insert(pair);
    }
}

/*
 * User chooses a length for the word for which the user is going to
 * guess.
 */
int askUserForLength(unordered_multimap<int, string> dict) {
    int length = 0;

    cout << "What length is your desired word? ";
    cin >> length;
    cout << endl;

    if (dict.find(length) != dict.end()) {
        cout << "Words with the length of " << length << " is " << dict.count(length) << endl;
    }

    else {
        cout << "The word is not of length of a word in the english dictionary, pick another." << endl;
        askUserForLength(dict);
    }

    return length;
}

/*
 * User chooses a number of guesses to guess the right word.
 */
int askUserForGuesses() {
    int guesses = 0;
    cout << "How many guesses do you want? ";
    cin >> guesses;
    cout << endl;

    if (guesses > 0) {
        return guesses;
    }

    else {
        cout << "Your guesses have to be more than 0, try again." << endl;
        askUserForGuesses();
    }

    return guesses;
}

/*
 * The user chooses if the user wants to see how many words are left for the
 * computer to choose from (anwser yes for testing/grading).
 */
bool askUserForInterface() {
    string answer;
    cout << "Do you want to see the amount of words left in the dictionary after each guess, yes or no?"
         << endl;
    cin >> answer;

    if (answer == "yes") {
        return true;
    }

    else if (answer == "no") {
        return false;
    }

    else {
        cout << "Write 'yes' or 'no', try again." << endl;
        askUserForInterface();
    }

    return false;
}

/*
 * Calculates and returns all words given the length the user chooses.
 */
vector<string> allWordsGivenLength(unordered_multimap<int, string> dict, int& length) {
    vector<string> matchingWords;
    length = askUserForLength(dict);
    for (auto itr = dict.begin(); itr != dict.end(); itr++) {
        if (itr -> first == length) {
            string word = itr -> second;
            matchingWords.insert(matchingWords.begin(), word);
        }
    }
    return matchingWords;
}

/*
 * User guesses a letter for the word and the method adds the guessed letter to
 * the string of guessed letters.
 */
string askUserForALetter(string& guessedLetters) {
    string letter;
    cout << "Guess a letter: ";
    cin >> letter;

    if (guessedLetters.find(letter) != string::npos || ALPHABET.find(letter) == string::npos || letter.size() != 1) {
        cout << "Error, try again." << endl;
        askUserForALetter(guessedLetters);
    }

    else {
        guessedLetters += letter;
    }
    cout << endl;

    return letter;
}

/*
 * Adds lines for the hidden letters in the word, adds the correct guessed letters to the word,
 * decrement guesses for wrong guess and prints guesses left, guessed letters and the word with
 * lines and letters.
 */
void gameInterface(string& currentWord, vector<int> largestFamily, string& guessedLetters, int& guesses, int& length) {
    if (currentWord == "") {
        for (int i = 0; i < length; i++) {
            currentWord += '-';
        }
    }

    else if (!largestFamily.empty()) {
        for (int i : largestFamily) {
            currentWord[i] = guessedLetters[guessedLetters.length()-1];
        }
    }

    else if (largestFamily.empty()) {
        guesses--;
    }

    cout << "Guesses left: " << guesses << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    /*
    cout << "Largest Family: [";
    for (int x: largestFamily) {
        cout << x << " ";
    }
    cout << "]" << endl;
    */
    cout << "Word: " << currentWord << endl;
}

/*
 * Checks what type of families the guess generates. A multimap is created with the
 * type as key and the word of that type as value. The multimap is then returned.
 */
multimap<vector<int>, string> checkFamilies(vector<string> matchingWords, char letter) {
    multimap<vector<int>, string> families;
    for (string word : matchingWords) {
        vector<int> matchingPos;
        for (int i=0; i < word.size(); i++) {
            if (word[i] == letter) {
                matchingPos.push_back(i);
            }
        }
        pair<vector<int>, string> myPair;
        myPair.first = matchingPos;
        myPair.second = word;
        families.insert(myPair);
    }
    return families;
}

/*
 * Returns the family that has the most occurences in the multimap with different types of
 * families.
 */
vector<int> checkMostCommonFamily(multimap<vector<int>, string> families) {
    vector<int> largestFamily;
    int max = 0;

    for (multimap<vector<int>,string>::iterator it = families.begin(), end = families.end(); it != end; it = families.upper_bound(it->first))
      {
        if (families.count(it->first) > max) {
            max = families.count(it->first);
            largestFamily = it->first;
        }

      }

    return largestFamily;
}

/*
 * Adds the words of the largest family to a vector.
 */
vector<string> retrieveMostCommonFamily(multimap<vector<int>, string> families, vector<int> largestFamily) {
    vector<string> wordsLeft;

    for (auto it = families.begin(); it != families.end(); it++) {
        if(it -> first == largestFamily) {
            wordsLeft.push_back(it -> second);
        }
    }

    return wordsLeft;
}

/*
 * Generates the user interface and checks whether the user has won or lost to
 * the computer. Otherwise the method calls all necessary methods for the game
 * to continue. The method also shows all words if the user has allowed it.
 */
void game(string& currentWord, vector<int>& largestFamily, string& guessedLetters, int& guesses, vector<string>& allWords, int length,
          bool& gameOver, bool showWordsLeft) {
    gameInterface(currentWord, largestFamily, guessedLetters, guesses, length);

    if (guesses > 0) {
        if (currentWord.find('-') == string::npos) {
            gameOver = true;
            cout << "Congratulations! YOU WON!!!" << endl;
        }
        else {
            char letter = askUserForALetter(guessedLetters)[0];
            multimap<vector<int>, string> families = checkFamilies(allWords, letter);
            largestFamily = checkMostCommonFamily(families);
            allWords = retrieveMostCommonFamily(families, largestFamily);
            if(showWordsLeft == true) {
                cout << "Words left: " << allWords.size() << endl;
            }
        }
    }

    else {
        gameOver = true;
        cout << "Congratualtions! You lost!" << endl;
    }
}

int main() {
    cout << "Welcome to Hangman." << endl;
    unordered_multimap<int, string> dict;
    saveDictionary(dict);
    bool playAgain = true;
    string currentWord;
    vector<int> largestFamily;
    string guessedLetters;
    int guesses;
    int length;
    vector<string> allWords;
    bool gameOver;
    bool showWordsLeft;

    while(playAgain) {
        currentWord = "";
        largestFamily = {};
        guessedLetters = "";
        guesses = 0;
        length = 0;
        allWords = allWordsGivenLength(dict, length);
        guesses = askUserForGuesses();
        gameOver = false;
        showWordsLeft = askUserForInterface();

        while(!gameOver) {
            game(currentWord, largestFamily, guessedLetters, guesses, allWords, length, gameOver, showWordsLeft);
        }

        cout << "Do you want to play again? (y/n): ";
        char answer;
        cin >> answer;
        if(answer == 'n') {
            playAgain = false;
        }
    }
    return 0;
}















