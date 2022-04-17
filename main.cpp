#include "teeko.hpp"
#include <cassert>

Teeko game = Teeko();

void playerInput() {
    char markerColumn, markerRow, destinationColumn, destinationRow;
    game.print();
    std::cout << "Player " << game.currentPlayer() << " enter move: ";
    std::cin >> markerColumn >> markerRow >> destinationColumn >> destinationRow;
    game.makeMove(markerColumn - 48, markerRow - 48, destinationColumn - 48, destinationRow - 48);
}


int main(int argc, const char** argv) {
    
    while (!game.isWin()) {
        
        playerInput();
    }
    
    
    game.print();
    std::cout << "Player " << (game.currentPlayer() ^ 1) << " wins!" << std::endl;
    
    return 0;
}