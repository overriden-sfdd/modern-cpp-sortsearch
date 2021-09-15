#include "life.hpp"

#include <iostream>

namespace LifeGame
{

Life::~Life()
{
    std::cout << "Do you want to save your game"
        << "configuration to local input.txt file?" << '\n';

    if (user_says_yes()) {
        if (this->input_file.is_open()) {
            this->input_file.close();
        }

        this->input_file.open("input.txt", std::ios::trunc | std::ios::out);

        this->input_file << std::to_string(this->maxrow)
            + ' ' + std::to_string(this->maxcol) << '\n';

        // TODO: attention code duplication!

        for (int row = 1; row <= this->maxrow; ++row) {
            std::string row_cells {};
            for (int col = 1; col <= this->maxcol; ++col) {
                row_cells += this->grid[row][col] == 1 ? '*' : ' ';
            }
            this->input_file << row_cells << '\n';
        }
    }

    this->input_file.close();
}

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
    std::string row_cells;

    std::cout << "Do you want to read game state from the file?";

    if (user_says_yes()) {
        this->read_from_file = 1;
        this->input_file.open("input.txt", std::ios::out | std::ios::in);
        this->input_file >> this->maxrow >> this->maxcol;
        std::getline(this->input_file, row_cells);
    } else {
        std::cout << "Enter the grid size pair row col: ";
        std::cin >> this->maxrow >> this->maxcol;
        // skip the empty character
        std::getline(std::cin, row_cells);
        std::cout << std::endl;
        std::cout << "List the coordinates for living cells.\n";
        std::cout << "Terminate the list with the word END\n";
    }

    for (auto& el : this->grid) {
        for (auto& ell : el)
            std::cout << ell << '\n';
    }

    std::cout << "Insert the delay for each cell living "
        << "cycle and the number of updates n1 n2: ";
    std::cin >> this->update_delay >> this->number_of_updates;

    std::vector<std::vector<int>> vec(this->maxrow + 2, std::vector<int>(this->maxcol + 2, 0));
    this->grid = vec;

    // go row-by-row
    for (int row = 1; row <= this->maxrow; ++row) {

        if (this->read_from_file) {
            std::getline(input_file, row_cells);
        } else {
            std::getline(std::cin, row_cells);
        }

        if (row_cells.size() > this->maxcol) {
            std::cout << "Too many cells in line " << row-- << '\n';
        } else if (row_cells == "END") {
            return;
        }

        for (int col = 1; col <= row_cells.size(); ++col) {
            grid[row][col] = row_cells[col] == '*' ? 1 : 0;
        }
    }

    if (this->input_file.is_open()) this->input_file.close();
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