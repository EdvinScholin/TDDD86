// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>

using namespace std;

string askUserForFileName() {
    string x;
    cout << "Enter your filename! " << endl;
    cin >> x;
    cout << "Filename: " << x << endl;
    return x;
}

int main() {

    // TODO: Finish the program!

    cout << "Have a nice Life! "  << endl;
    askUserForFileName();
    return 0;
}
