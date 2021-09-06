// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

string askUserForFileName() {
    string x;
    cout << "Enter your filename! " << endl;
    cin >> x;
    //cout << "Filename: " << x << endl;
    return x;
}

void getFileContent() {
    string filename ="simple.txt";
    ifstream input;
    input.open(filename.c_str());
    string line;
    int row_length;
    int col_length;

    getline(input, line);
    stringstream convert_row(line);
    convert_row >> row_length;
    cout <<  "rows: " << line << endl;
    getline(input, line);
    stringstream convert_col(line);
    convert_col >> col_length;
    cout << "cols: " << line << endl;

    cout << "converted row and col: " << row_length << ", " << col_length << endl;

    Grid<char> grid(row_length, col_length);

    //int count = 0;

    for(int row=0; row < row_length; row++) {
        getline(input, line);
        for(int col=0; col < col_length; col++) {
            //cout << line[i];
            //count++;
            grid.set(row, col, line[col]);

        }
    }

    cout << grid.toString() << endl;
    input.close();

}


int main() {

    // TODO: Finish the program!

    cout << "Have a nice Life! "  << endl;

    getFileContent();
    cout << "done...";
    //askUserForFileName();
    return 0;


}
