/*
 * This assignment is made by Wilmer Segerstedt and Edvin Schölin.
 * Excecuting this program creates a minimal wordchain from one start
 * word to an end word after asking the user for these words.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
unordered_set<string> dict;

/*
 * Saves all the words in the english dictionary to an
 * unordered set.
 */
void saveDictionary(unordered_set<string>& dict) {
    string filename = "dictionary.txt";
    ifstream input;
    input.open(filename.c_str());
    string line;

    while (getline(input, line)) {
        dict.insert(line);
    }
}

/*
 * Returns a pair of two words that the user has entered
 * through the console.
 */
pair<string, string> askUserForTwoWords() {
    string str1;
    string str2;
    cout << "Please type two words: ";
    cin >> str1;
    cin >> str2;
    pair<string, string> myPair;
    myPair.first = str1;
    myPair.second = str2;
    return myPair;
}

/*
 * Creates a minimal word chain from a start word to an end word.
 */
void wordChain(string w1, string w2) {
    queue<stack<string>> q;
    stack<string> chain_stack;
    unordered_set<string> neighbours;
    chain_stack.push(w1);
    q.push(chain_stack);

    while (!q.empty()) {
        chain_stack = q.front();
        q.pop();
        if (chain_stack.top() == w2) {
            while (!chain_stack.empty()) {
                cout << chain_stack.top() << " ";
                chain_stack.pop();
            }
        }

        else {
            int length = chain_stack.top().length();
            for (int i = 0; i < length; i++) {
                string temp_word = chain_stack.top();
                for (char letter : ALPHABET) {
                    temp_word[i] = letter;

                    if (dict.find(temp_word) != dict.end()) {
                        if (neighbours.find(temp_word) == neighbours.end()) {
                            stack<string> copy_stack = chain_stack;
                            neighbours.insert(temp_word);
                            copy_stack.push(temp_word);
                            q.push(copy_stack);
                        }
                    }
                }
            }
        }
    }
}


int main() {
    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    pair<string, string> wordPair = askUserForTwoWords();
    saveDictionary(dict);

    cout << "Chain from " << wordPair.first << " back to " << wordPair.second << endl;

    wordChain(wordPair.first, wordPair.second);

    cout << endl;
    cout << "Have a nice day.";

    return 0;
}
