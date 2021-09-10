#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/*
 * Asks for a start colony in text format.
 */
string askUserForFileName() {
    string str;
    cout << "Grid input file name? ";
    cin >> str;
    return str;
}

/*
 * Asks user for what should be done in the program.
 */
string askUserForAction() {
    string str;
    cout << "a)nimate, t)ick, q)uit? ";
    cin >> str;
    return str;
}

/*
 * Converts a string from the textfile to an integer.
 */
int convertStringToInt(const string str) {
    int integer;
    stringstream convert(str);
    convert >> integer;
    return integer;
}

/*
 * Sets the grid as the textfile dictates.
 */
void setGrid(Grid<char>& grid, ifstream& input, string& line, const int row_length,
             const int col_length) {
    for(int row=0; row < row_length; row++) {
        getline(input, line);
        for(int col=0; col < col_length; col++) {
            grid.set(row, col, line[col]);
        }
    }
}

/*
 * Sets the right size of the grid from the first two rows
 * of the textfile where the number of columns and rows of the grid is
 * stated.
 */
void getGridFromFile(Grid<char>& grid) {
    string filename = askUserForFileName();
    ifstream input;
    input.open(filename.c_str());
    string line;

    getline(input, line);
    int row_length = convertStringToInt(line);

    getline(input, line);
    int col_length = convertStringToInt(line);

    grid.resize(row_length, col_length);
    setGrid(grid, input, line, row_length, col_length);

    input.close();
}

/*
 * Prints the grid as the same format as the textfile.
 */
void printGrid(const Grid<char>& grid) {
    for(int row = 0; row < grid.numRows(); row++) {
        for (int col = 0; col < grid.numCols(); col++) {
            cout << grid.get(row, col);
        }
        cout << endl;
    }
}

/*
 * Counts the amount of neighbours of a given cell.
 */
int checkTotalNeighbours(const Grid<char>& grid, const int row, const int col) {
    int totalNeighbours = 0;

    for (int inner_row = row-1; inner_row < row+2; inner_row++) {

        for (int inner_col = col-1; inner_col < col+2; inner_col++) {
            if (grid.inBounds(inner_row, inner_col)) {

                if (grid.get(inner_row, inner_col) == 'X') {

                    if ((inner_row != row) || (inner_col != col)) {
                        totalNeighbours++;
                    }
                }
            }
        }
    }
    return totalNeighbours;
}

/*
 * Ticks the cell simulation one step according to the rules of
 * the game of life.
 */
void advanceGrid(Grid<char>& grid) {
    Grid<char> tempGrid(grid.numRows(), grid.numCols());
    int neighbours = 0;

    for(int row=0; row < grid.numRows(); row++) {
        for(int col=0; col < grid.numCols(); col++) {
            neighbours = checkTotalNeighbours(grid, row, col);

            if (neighbours <= 1) {
                tempGrid.set(row, col, '-');
            }

            else if (neighbours == 2) {
                tempGrid.set(row, col, grid.get(row, col));
            }

            else if (neighbours == 3) {
                tempGrid.set(row, col, 'X');
            }

            else {
                tempGrid.set(row, col, '-');
            }
        }
    }
    grid = tempGrid;
}

/*
 * Ticks cell simulation one step forward every 100 ms while clearing the console
 * and counting colony generations.
 */
void animate(Grid<char>& grid) {
    int generations = 0;
    while(1==1) {
        advanceGrid(grid);
        generations++;
        clearConsole();
        printGrid(grid);
        cout << "generations: " << generations << endl;
        pause(100);
    }
}

/*
 * Checks user action input from the console and calls the appropriate
 * functions.
 */
void userInterface(Grid<char>& grid) {
    string action = askUserForAction();
    if (action == "a") {
        animate(grid);
    }

    else if (action == "t") {
        advanceGrid(grid);
        printGrid(grid);
        userInterface(grid);
    }

    else if (action == "q") {
        cout << "Have a nice Life! "  << endl;
    }

    else {
        userInterface(grid);
    }
}

/*
 * Main function which starts the program.
 */
int main() {
    Grid<char> grid;
    getGridFromFile(grid);
    printGrid(grid);
    userInterface(grid);
    return 0;
}
