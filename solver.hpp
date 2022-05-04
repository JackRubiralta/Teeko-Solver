#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "teeko.hpp"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <ostream>
std::unordered_map<uint64_t, int> transpositionTable = std::unordered_map<uint64_t, int>();
std::unordered_set<uint64_t> previousStates = std::unordered_set<uint64_t>();
unsigned int long long nodesExplored = 0;

std::ostream& operator<<(std::ostream& os, const std::unordered_map<uint64_t, int>& table) {
    for (auto& entry : table) {
        os << entry.first << ": " << entry.second << std::endl;
    }
    return os;
}

int negamax(const Teeko &node) {
    if (node.isDraw()) { return 0; }
    if (node.isWin()) { return -(((int)Teeko::MAX_MOVES + (int)1 - (int)node.moveCounter) / (int)2); } 
    
    if (previousStates.find(node.key()) != previousStates.end()) { return 0; }
        
    if (transpositionTable.find(node.key()) != transpositionTable.end()) { return transpositionTable[node.key()]; }

    previousStates.insert(node.key());

    int bestValue = -2147483;
    for (bitboard move : node.possibleMoves()) { 
        Teeko child = Teeko(node);
        child.makeMove(move);

        int value = -negamax(child);
        if (value >= bestValue) {
            bestValue = value;
        }
    }

    previousStates.erase(node.key());
    transpositionTable[node.key()] = bestValue;
    return bestValue;
};

int solve(const Teeko &root) {
    return negamax(root);
};


void reset() {
    nodesExplored = 0;
    previousStates.empty();
    transpositionTable.clear();
}

#endif
