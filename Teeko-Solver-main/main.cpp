#include "solver.hpp"
#include <ctime>
Teeko game = Teeko();

void analysis() {
    reset();
    clock_t timeRequired = clock();
    int value = solve(game, 7);
    timeRequired = clock() - timeRequired;
    std::cout << "Value: " << value;
    std::cout << "; ";
    std::cout << "nodesExplored: " << nodesExplored;
    std::cout << "; ";
    std::cout << "timeRequired: " << (float)timeRequired / CLOCKS_PER_SEC << "s";
    std::cout << "; ";
    std::cout << "nodes/s: " << (nodesExplored / ((float)timeRequired));
    std::cout << std::endl;
} 

void computerMove() {
    //game.print();

    reset();
    clock_t timeRequired = clock();
    bitboard move = analyze(game, 8);
    timeRequired = clock() - timeRequired;
    game.makeMove(move);
    std::cout << "nodesExplored: " << nodesExplored;
    std::cout << "; ";
    std::cout << "timeRequired: " << (float)timeRequired / CLOCKS_PER_SEC << "s";
    std::cout << "; ";
    std::cout << "nodes/s: " << (nodesExplored / ((float)timeRequired));
    std::cout << std::endl;
} 


void playerInput() {
    char markerColumn, markerRow, destinationColumn, destinationRow;
    game.print();

    analysis();

    std::cout << "Player " << (game.currentPlayer() ? "black" : "red") << " enter move: ";
    std::cin >> markerColumn >> markerRow >> destinationColumn >> destinationRow;
    game.makeMove(markerColumn - 48, markerRow - 48, destinationColumn - 48, destinationRow - 48);
}


int main(int argc, const char** argv) {

    while (!game.isWin()) {
        computerMove();
        //playerInput();
    }


    //game.print();
    std::cout << "Player " << (game.currentPlayer() ^ 1) << " wins!" << std::endl;

    return 0;
}