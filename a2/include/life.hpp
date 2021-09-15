#ifndef LIFE_HPP_
#define LIFE_HPP_

#include <vector>
#include <string>
#include <fstream>

namespace LifeGame
{

class Life
{
public:
    void initialize();
    void print() const;
    void update();
    void instructions() const;

    ~Life();

public:
    int update_delay = 3, number_of_updates = 5;

private:
    int maxrow = 20, maxcol = 60;
    unsigned char read_from_file = 0;

    std::fstream input_file;
    std::vector<std::vector<int>> grid;  //  allows for two extra rows and columns
    int neighbor_count(int row, int col);
};

extern void instructions();

extern bool user_says_yes();

} // namespace LifeGame

#endif  // LIFE_HPP_