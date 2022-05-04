#include "solver.hpp"
#include <ctime>
#include <fstream>
#include <process.h>
#include <windows.h>

bool coderunning = true;
void logStuff(void*) {
    while (coderunning) {
        std::cout << "transpositionTableSize: " << transpositionTable.size() << "; " <<  "nodesExplored: " << nodesExplored << std::endl;
        Sleep(30000);
    }
}

void analysis() {
    std::cout << "Running" << std::endl;
    Teeko game = Teeko();
    
    clock_t timeRequired = clock();
    int value = solve(game);
    timeRequired = clock() - timeRequired;
    std::cout << "Value: " << value;
    std::cout << "; ";
    std::cout << "nodesExplored: " << nodesExplored;
    std::cout << "; ";
    std::cout << "timeRequired: " << (float)timeRequired / CLOCKS_PER_SEC << "s";
    std::cout << "; ";
    std::cout << "nodes/s: " << (nodesExplored / ((float)timeRequired));
    std::cout << "; ";
    std::cout << "transpositionTableSize: " << transpositionTable.size();
    std::cout << "; ";
    std::cout << std::endl;

    coderunning = false;
   
    
    std::ofstream tableFile("book.txt");
    for (const auto & [ key, value ] : transpositionTable) {
        tableFile << key << ": " << value << std::endl;
    }
    tableFile.close();
}


int main(int argc, const char** argv) {
    reset();

    auto y = _beginthread(logStuff,0,NULL);
    analysis();



    return 0;
}