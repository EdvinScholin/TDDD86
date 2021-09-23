#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <fstream>
#include <vector>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
unordered_multimap<int, string> dict;
string currentWord = "";
string guessedLetters = "";
int guesses;
int length;

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

int askUserForLength(unordered_multimap<int, string> dict) {
    int length = 0;

    cout << "What length is your desired word? ";
    cin >> length;
    cout << endl;

    if (dict.find(length) != dict.end()) {
        cout << "Såja!" << endl;
        cout << dict.count(length) << endl;
    }

    else {
        cout << "The word is not of length of a word in the english dictionary, pick another."
             << endl;
        askUserForLength(dict);
    }

    return length;
}

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

vector<string> allWordsGivenLength(unordered_multimap<int, string> dict) {
    vector<string> matchingWords;
    int length = askUserForLength(dict);
    for (auto itr = dict.begin(); itr != dict.end(); itr++) {
        if (itr -> first == length) {
            string word = itr -> second;
            matchingWords.insert(matchingWords.begin(), word);
        }
    }

    //cout << matchingWords.size() << endl;
    //cout << matchingWords[1] << endl;

    return matchingWords;
}

string askUserForAGuess() {
    string letter;
    cout << "Guess letter." << endl;
    cin >> letter;

    if (guessedLetters.find(letter) != string::npos || ALPHABET.find(letter) == string::npos || letter.size() != 1) {
        cout << "Error, try again." << endl;
        askUserForAGuess();
    }

    else {
        guessedLetters += letter;
        //guesses--;
    }

    return letter;
}

void gameInterface() {
    if (currentWord == "") {
        for (int i = 0; i < length; i++) {
            currentWord += '-';
        }
    }

    cout << "Guesses left: " << guesses << endl;
    cout << "Guessed letters: " << guessedLetters << endl;
    cout << currentWord << endl;

    askUserForAGuess();
    //cout << "Words left: " <<
}

multimap<vector<int>, string> checkFamilies(vector<string> matchingWords, char letter) {
    multimap<vector<int>, string> families;
    for (string word : matchingWords) {
        vector<int> matchingPos;
        for(int i=0; i<word.size(); i++) {
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

vector<int> checkMostCommonFamily(multimap<vector<int>, string> families) {
    vector<int> largestFamily;
    int max = 0;
    for(multimap<vector<int>,string>::iterator it = families.begin(), end = families.end(); it != end; it = families.upper_bound(it->first))
      {
        if (families.count(it->first) > max) {
            max = families.count(it->first);
            largestFamily = it->first;
        }

      }

    return largestFamily;
}

vector<string> retrieveMostCommonFamily(multimap<vector<int>, string> families) {
    vector<string> wordsLeft;
    vector<int> largestFamily = checkMostCommonFamily(families);

    for (auto it = families.begin(); it != families.end(); it++) {
        if(it -> first == largestFamily) {
            wordsLeft.push_back(it -> second);
        }
    }

    return wordsLeft;
}

int main() {
    cout << "Welcome to Hangman." << endl;
    saveDictionary(dict);

    //length = askUserForLength(dict);
    //guesses = askUserForGuesses();
    //askUserForWord(dict);
    //askUserForGuesses();
    //askUserForInterface();
    //game(dict);

    //while (true) {
      //  gameInterface();
    //}

    vector<string> allWords = allWordsGivenLength(dict);
    multimap<vector<int>, string> families = checkFamilies(allWords, 'e');
    vector<int> bestFamily = checkMostCommonFamily(families);
    cout << "[";
    for (int x : bestFamily) {
        cout << x << " ";
    }
    cout << "]" << "elems: " << families.count(bestFamily) << endl;

    vector<string> words = retrieveMostCommonFamily(families);
    cout << "words: " << words.size();

    return 0;
}
