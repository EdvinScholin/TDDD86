/*
 * This assignment is made by Wilmer Segerstedt (wilse150) and Edvin Schölin (edvsc779).
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
void askUserForTwoWords(string& str1, string& str2) {
    cout << "Please type two words: ";
    cin >> str1;
    cin >> str2;
}

/*
 * Creates a minimal word chain from a start word to an end word.
 */
void wordChain(string& w1, string& w2, unordered_set<string> const& dict) {
    queue<stack<string>> q;
    stack<string> chain_stack;
    unordered_set<string> neighbours;           //save previous neighboring words
    chain_stack.push(w1);
    q.push(chain_stack);                        //create/add a stack containing {w1} to the queue

    while (!q.empty()) {                        //the queue is not empty
        chain_stack = q.front();
        q.pop();                                //dequeue the partial-chain stack from the front of the queue
        if (chain_stack.top() == w2) {          //if the word at the top of the stack is the destinaction word
            while (!chain_stack.empty()) {      //output the elements of the stack as the solution
                cout << chain_stack.top() << " ";
                chain_stack.pop();
            }
        }

        else {
            int length = chain_stack.top().length();
            for (int i = 0; i < length; i++) {
                string temp_word = chain_stack.top();                           //get next word in chain
                for (char letter : ALPHABET) {                                  //iterate through every possible neighbour word
                    temp_word[i] = letter;

                    if (dict.find(temp_word) != dict.end()) {                   //if that neighbour is a valid English word
                        if (neighbours.find(temp_word) == neighbours.end()) {   //if that neighbour word has not already been used in a ladder before
                            stack<string> copy_stack = chain_stack;             //create a copy of the current chain stack
                            neighbours.insert(temp_word);                       //ensure neighbour word is not used again
                            copy_stack.push(temp_word);                         //put the neighbour word at the top of the copy stack
                            q.push(copy_stack);                                 //add the copy stack to the end of the queue
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

    string word1 = "";
    string word2 = "";
    askUserForTwoWords(word1, word2);
    unordered_set<string> dict;
    saveDictionary(dict);

    cout << "Chain from " << word1 << " back to " << word2 << endl;

    wordChain(word1, word2, dict);

    cout << endl;
    cout << "Have a nice day." << endl;

    return 0;
}
