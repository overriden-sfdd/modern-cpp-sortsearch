#include "life.hpp"

#include <chrono>
#include <thread>
#include <iostream>

using namespace LifeGame;

/*
Pre:  The user supplies an initial configuration of living cells.
Post: The program prints a sequence of pictures showing the changes in
      the configuration of living cells according to the rules for
      the game of Life.
Uses: The class Life and its methods initialize(), print(), and update().
      The functions  instructions(),  user_says_yes().
*/

//  Program to play Conway's game of Life.
int main(int argc, char** argv)
{
    Life configuration;
    configuration.instructions();
    configuration.initialize();
    configuration.print();
    int number_of_updates_done = 0;
    while (++number_of_updates_done < configuration.number_of_updates) {
        configuration.update();
        configuration.print();
        std::this_thread::sleep_for(std::chrono::seconds
            (configuration.update_delay));
    }
}