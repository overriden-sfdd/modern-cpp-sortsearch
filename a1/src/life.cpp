#include "life.hpp"

#include <iostream>

namespace LifeGame
{

/*
Pre:  The Life object contains a configuration, and the coordinates
      row and col define a cell inside its hedge.
Post: The number of living neighbors of the specified cell is returned.
*/
int Life::neighbor_count(int row, int col)
{
    int start_rows = row == 1 ? row : row - 1;
    int start_cols = col == 1 ? col : col - 1;
    int iter_rows = row == maxrow - 1 ? row : row + 1;
    int iter_cols = col == maxcol - 1 ? col : col + 1;

    int count = 0;
    for (int i = start_rows; i <= iter_rows; ++i) {
        for (int j = start_cols; j <= iter_cols; ++j)
            count += grid[i][j];  //  Increase the count if neighbor is alive.
    }
    count -= grid[row][col]; //  Reduce count, since cell is not its own neighbor.
    return count;
}

/*
Pre:  The Life object contains a configuration.
Post: The Life object contains the next generation of configuration.
*/
void Life::update()
{
    int row, col;
    int new_grid[maxrow + 2][maxcol + 2];

    for (row = 1; row <= maxrow; ++row) {
        for (col = 1; col <= maxcol; ++col) {
            switch (neighbor_count(row, col)) {
            case 2:
                new_grid[row][col] = grid[row][col];  //  Status stays the same.
                break;
            case 3:
                new_grid[row][col] = 1;                //  Cell is now alive.
                break;
            default:
                new_grid[row][col] = 0;                //  Cell is now dead.
            }
        }
    }

    for (row = 1; row <= maxrow; row++) {
        for (col = 1; col <= maxcol; col++)
            grid[row][col] = new_grid[row][col];
    }
}

/*
Pre:  None.
Post: Instructions for using the Life program have been printed.
*/
void Life::instructions() const
{
    std::cout << "Welcome to Conway's game of Life.\n"
        << "This game uses a grid of size " << maxrow << " by " << maxcol
        << " in which\n" << "each cell can either be occupied by an organism or not.\n"
        << "The occupied cells change from generation to generation according to"
        << " the number of neighboring cells which are alive." << std::endl;
}

/*
Pre:  None.
Post: The Life object contains a configuration specified by the user.
*/
void Life::initialize()
{
    std::cout << "Enter the grid size pair 'row col':\n";
    std::cin >> maxrow >> maxcol;
    std::cout << std::endl;
    
    std::vector<std::vector<int>> vec(maxrow + 2, std::vector<int>(maxcol + 2, 0));
    grid = vec;

    int row = 0, col = 0;
    std::cout << "List the coordinates for living cells.\n";
    std::cout << "Terminate the list with the special pair -1 -1\n";
    std::cin >> row >> col;

    while (row != -1 || col != -1) {
        if (row >= 1 && row <= maxrow) {
            if (col >= 1 && col <= maxcol) {
                grid[row][col] = 1;
            } else {
                std::cout << "Column " << col << " is out of range.\n";
            }
        } else {
            std::cout << "Row " << row << " is out of range.\n";
        }
        std::cin >> row >> col;
    }
}

/*
Pre:  The Life object contains a configuration.
Post: The configuration is written for the user.
*/
void Life::print() const
{
    int row, col;
    std::cout << "\nThe current Life configuration is:\n";
    for (row = 1; row <= maxrow; ++row) {
        for (col = 1; col <= maxcol; ++col) {
            if (grid[row][col] == 1) {
                std::cout << '*';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

extern bool user_says_yes()
{
    int c;
    bool initial_response = true;

    do {  //  Loop until an appropriate input is received.
        if (initial_response) {
            std::cout << " (y,n)? " << std::flush;
        } else {
            std::cout << "Respond with either y or n: " << std::flush;
        }

        do { //  Ignore white space.
            c = std::cin.get();
        } while (c == '\n' || c == ' ' || c == '\t');

        initial_response = false;

    } while (c != 'y' && c != 'Y' && c != 'n' && c != 'N');
    return (c == 'y' || c == 'Y');
}

} // namespace LifeGame