#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
unordered_multimap<int, string> dict;

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

void game(unordered_multimap<int, string> dict) {
    vector<string> listOfWords;
    int length = askUserForLength(dict);
    for (auto itr = dict.begin(); itr != dict.end(); itr++) {
        if (itr -> first == length) {
            string word = itr -> second;
            listOfWords.insert(listOfWords.begin(), word);
        }
    }

    cout << listOfWords.size() <<endl;;
    cout << listOfWords[1] << endl;
}

int main() {
    cout << "Welcome to Hangman." << endl;
    saveDictionary(dict);
    //askUserForWord(dict);
    //askUserForGuesses();
    //askUserForInterface();
    game(dict);

    return 0;
}
