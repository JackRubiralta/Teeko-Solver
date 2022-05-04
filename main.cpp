#include "solver.hpp"
#include <ctime>
Teeko game = Teeko();

int main(int argc, const char** argv) {
    reset();
    clock_t timeRequired = clock();
    int value = solve(game, 10);
    timeRequired = clock() - timeRequired;
    std::cout << "Value: " << value;
    std::cout << "; ";
    std::cout << "nodesExplored: " << nodesExplored;
    std::cout << "; ";
    std::cout << "timeRequired: " << (float)timeRequired / CLOCKS_PER_SEC << "s";
    std::cout << "; ";
    std::cout << "nodes/s: " << (nodesExplored / ((float)timeRequired));
    std::cout << "; ";
    std::cout << transpositionTable.size() << " entries in transposition table";
    std::cout << "; ";
    std::cout << std::endl;    
    return 0;
}