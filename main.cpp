#include "solver.hpp"

Teeko game = Teeko();

void playerInput() {
    char markerColumn, markerRow, destinationColumn, destinationRow;
    game.print();
    reset();
    int value = solve(game, 14);
    // 1258407
    // 1079184
    std::cout << "nodesExplored: " << nodesExplored << std::endl;
    std::cout << "Value: " << value << std::endl;
    std::cout << "Player " << (game.currentPlayer() ? "black" : "red") << " enter move: ";
    std::cin >> markerColumn >> markerRow >> destinationColumn >> destinationRow;
    game.makeMove(markerColumn - 48, markerRow - 48, destinationColumn - 48, destinationRow - 48);
}


int main(int argc, const char** argv) {
    
    while (true) {
        
        playerInput();
    }
    
    
    game.print();
    std::cout << "Player " << (game.currentPlayer() ^ 1) << " wins!" << std::endl;
    
    return 0;
}