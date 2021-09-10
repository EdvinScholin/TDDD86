#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <unordered_set>
using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";
unordered_set<string> dict;

void saveDictionary(unordered_set<string>& dict) {
    string filename = "dictionary.txt";
    ifstream input;
    input.open(filename.c_str());
    string line;

    while (getline(input, line)) {
        dict.insert(line);
    }
}

pair<string, string> askUserForTwoWords() {
    string str1;
    string str2;
    cout << "Please type two words: ";
    cin >> str1;
    cin >> str2;
    pair<string, string> myPair;
    myPair.first = str1;
    myPair.second = str2;
    cout << myPair.first << " " << myPair.second << endl;
    return myPair;
}

stack<string> wordChain(string w1, string w2) {
    queue<stack<string>> q;
    stack<string> stack;
    stack.push(w1);
    q.push(stack);

    while (!q.empty()) {
        stack = q.front(); // Osäker
        q.pop();
        if (stack.top() == w2) {
            return stack;
        }

        else {
            int length = stack.top().length(); // bytes?
            for (int i = 0; i < length; i++) {
                for (char letter : ALPHABET) {

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

    askUserForTwoWords();
    saveDictionary(dict);
    if (dict.find("penis") == dict.end()) {
        cout << "Not found." << endl;
    }

    else {
        cout << "Found." << endl;
    }


    // TODO: Finish the program!

    return 0;
}
