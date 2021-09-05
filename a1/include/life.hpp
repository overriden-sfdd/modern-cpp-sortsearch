#ifndef LIFE_HPP_
#define LIFE_HPP_

#include <vector>

namespace LifeGame
{

class Life
{
public:
    void initialize();
    void print() const;
    void update();
    void instructions() const;

private:
    int maxrow = 20, maxcol = 60;
    std::vector<std::vector<int>> grid;  //  allows for two extra rows and columns
    int neighbor_count(int row, int col);
};

extern void instructions();

extern bool user_says_yes();

} // namespace LifeGame

#endif  // LIFE_HPP_