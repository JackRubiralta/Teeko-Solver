#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "transpositiontable.hpp"
#include <algorithm>
#include <unordered_set>

TranspositionTable transpositionTable = TranspositionTable(75710250);
std::unordered_set<uint64_t> previousStates = std::unordered_set<uint64_t>();
unsigned int long long nodesExplored = 0;

void reset() {
    nodesExplored = 0;
    previousStates.empty();
    transpositionTable.reset();
}

int negamax(const Teeko &node, int alpha, int beta, unsigned int depth) {
    if (depth <= 0) { return 0; }
    if (node.isDraw()) { return 0; }
    if (previousStates.find(node.key()) != previousStates.end()) { return 0; }

    if (node.isWin()) { return -(((int)100 + (int)1 - (int)node.moveCounter) / (int)2); } 

    const int alphaOriginal = alpha;
    Entry entry = transpositionTable.lookup(node.key());
    if (entry.flag != INVALID && entry.depth >= depth) {
        if (entry.flag == EXACT) {
            return entry.value;
        } else if (entry.flag == LOWERBOUND) {
            alpha = std::max(alpha, int(entry.value));
        } else if (entry.flag == UPPERBOUND) {
            beta = std::min(beta, int(entry.value));
        }
        if (alpha >= beta) { return entry.value; }
    }

    previousStates.insert(node.key());

    int bestValue = -2147483;
    for (bitboard move : node.possibleMoves()) { // could loop through moves
        Teeko child = Teeko(node);
        child.makeMove(move);

        int value = -negamax(child, -beta, -alpha, depth - 1);
        if (value >= bestValue) {
            bestValue = value;
            if (value >= alpha) alpha = value;
            if (value >= beta) break;
        }
    }

    previousStates.erase(node.key());
    
    entry.value = bestValue;
    if (alpha <= alphaOriginal) {
        entry.flag = UPPERBOUND;
    } else if (bestValue >= beta) {
        entry.flag = LOWERBOUND;
    } else {
        entry.flag = EXACT;
    }
    
    transpositionTable.insert(node.key(), entry);
    
    nodesExplored++;
    
    return bestValue;
};


int solve(const Teeko &root, unsigned int depth) {
    return negamax(root, -2147483, 2147483, depth);
};


#endif
