#include "teeko.hpp"
#include <string>
#include <iterator>
#include <algorithm>

int main(int argc, const char** argv) {
    Teeko game = Teeko();
    char row;
    char column;

    int value;
    while (true) {
        game.print();
        
        std::cout << "Player " << game.currentPlayer() << ": ";
        std::cout << "Enter move: ";
        std::cin >> row >> column;
        game.play(row - 48, column - 48);
    }
    
    
    game.print();
    std::cout << "Player " << (game.currentPlayer() ^ 1) << " wins!" << std::endl;
    
    return 0;
}