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
    cout << "Filename: " << x << endl;
    return x;
}

int convertStringToInt(string str) {
    int integer;
    stringstream convert(str);
    convert >> integer;
    return integer;
}

void setGrid(Grid<char>& grid, ifstream& input, string& line, int& row_length,
              int& col_length) {
    for(int row=0; row < row_length; row++) {
        getline(input, line);
        for(int col=0; col < col_length; col++) {
            grid.set(row, col, line[col]);
        }
    }
}

void getGridFromFile(Grid<char>& grid) {
    string filename ="simple.txt"; //ask_user_for_filename()
    //string filename = askUserForFileName();
    ifstream input;
    input.open(filename.c_str());
    string line;

    getline(input, line);
    int row_length = convertStringToInt(line);

    getline(input, line);
    int col_length = convertStringToInt(line);

    grid.resize(row_length, col_length);
    setGrid(grid, input, line, row_length, col_length);

    cout << grid.toString() << endl;
    input.close();
}

void printGrid(Grid<char>& grid) {
    for(int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}

int checkTotalNeighbours(Grid<char>& grid, int row, int col) {
    int totalNeighbours = 0;

    for (int inner_row = row-1; inner_row < row+2; inner_row++) {
        for (int inner_col = col-1; inner_col < col+2; inner_col++) {

            if (grid.inBounds(inner_row, inner_col)) {

                if (grid.get(inner_row, inner_col) == 'X') { // and if inte 0,0
                    if (inner_row != row && inner_col != col) {
                        totalNeighbours++;
                    }
                }
            }
        }
    }

    cout << totalNeighbours << endl;
    return totalNeighbours;
}

void advanceGrid(Grid<char>& grid) {
    for(int row=0; row < grid.numRows(); row++) {
        for(int col=0; col < grid.numCols(); col++) {
            char cellType = grid.get(row, col);
            int neighbours = checkTotalNeighbours(grid, row, col);

        }
    }
}


int main() {

    // TODO: Finish the program!

    cout << "Have a nice Life! "  << endl;

    Grid<char> grid;
    getGridFromFile(grid);
    cout << endl;
    printGrid(grid);
    checkTotalNeighbours(grid, 0,0);
    cout << "done...";
    return 0;


}
