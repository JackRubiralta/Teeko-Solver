#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "transpositiontable.hpp"
TranspositionTable transpositionTable = TranspositionTable(100000000);
unsigned int nodesExplored = 0;
int reset() {
    nodesExplored = 0;
    transpositionTable.reset();
}

int negamax(const Teeko &node, int alpha, int beta, int depth) {
    if (depth <= 0) { return 0; }
    nodesExplored++;   
    if (node.isWin()) { // isAlignment
        return -1;//-((Teeko::LENGTH * Teeko::LENGTH + 1 - node.moveCounter) / 2);
    } 

    const int alphaOriginal = alpha;
    Entry entry = transpositionTable.lookup(node.key());
    if (entry.flag == COMPUTING) {
        return beta;
    } else if (entry.flag != INVALID) {
        if (entry.depth >= depth) {
            if (entry.flag == EXACT) {
                return entry.value;
            } else if (entry.flag == LOWERBOUND) {
                alpha = std::max(alpha, int(entry.value));
            } else if (entry.flag == UPPERBOUND) {
                beta = std::min(beta, int(entry.value));
            }

            if (alpha >= beta) { return entry.value; }
        }
    }
    entry.flag = COMPUTING;
    transpositionTable.insert(node.key(), entry);


    std::vector<bitboard> moves = node.possibleMoves();
    int value = -2147483647;

    for (bitboard move : moves) { // could loop through moves
        Teeko child = Teeko(node);
        child.makeMove(move);
        
        value = std::max(value, -negamax(child, -beta, -alpha, depth - 1));
        alpha = std::max(alpha, value);
        if (alpha >= beta) { break; }
    }

    entry.value = value;
    if (alpha <= alphaOriginal) {
        entry.flag = UPPERBOUND;
    } else if (value >= beta) {
        entry.flag = LOWERBOUND;
    } else {
        entry.flag = EXACT;
    }
    entry.depth = depth;
    transpositionTable.insert(node.key(), entry);
    return value;

    
};


int solve(const Teeko &root, int depth) {
    return negamax(root, -2147483647, 2147483647, depth);
};

#endif
