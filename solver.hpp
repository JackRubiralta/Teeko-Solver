#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "transpositiontable.hpp"
#include <unordered_set>

TranspositionTable transpositionTable = TranspositionTable(76000000);

unsigned int nodesExplored = 0;
void reset() {
    nodesExplored = 0;
    //transpositionTable.reset();
}

int negamax(const Teeko &node, int alpha, int beta, int depth) {
    if (depth <= 0) { return 0; }
    nodesExplored++;   
    if (node.isWin()) { // isAlignment
        return -(((int)100 + (int)1 - (int)node.moveCounter) / (int)2);
    } 

    const int alphaOriginal = alpha;
    Entry entry = transpositionTable.lookup(node.key());
    
    // have return beta if still computing
    if (entry.flag == C) {
        return -1000000;
    } if ((entry.flag != INVALID) && (entry.depth == depth)) {
        if (entry.flag == EXACT) {
            return entry.value;
        } else if (entry.flag == LOWERBOUND) {
            alpha = std::max(alpha, int(entry.value));
        } else if (entry.flag == UPPERBOUND) {
            beta = std::min(beta, int(entry.value));
        }

        if (alpha >= beta) { return entry.value; }
        // 64198351;
        // 63663737;
    }

    entry.flag = C;
    transpositionTable.insert(node.key(), entry);
   

    std::vector<bitboard> moves = node.possibleMoves();
    int bestValue = -2147483;

    for (bitboard move : moves) { // could loop through moves
        Teeko child = Teeko(node);
        child.makeMove(move);

        
        int value = -negamax(child, -beta, -alpha, depth - 1);

        if (value >= bestValue) {
            bestValue = value;
            if (value >= alpha) alpha = value;
            if (value >= beta) break;
        }
    }


    
    entry.value = bestValue;
    if (alpha <= alphaOriginal) {
        entry.flag = UPPERBOUND;
    } else if (bestValue >= beta) {
        entry.flag = LOWERBOUND;
    } else {
        entry.flag = EXACT;
    }
    entry.depth = depth;
    transpositionTable.insert(node.key(), entry);
    
    return bestValue;

    
};


int solve(const Teeko &root, int depth) {
    return negamax(root, -2147483, 2147483, depth);
};

bitboard analyze(Teeko &root, unsigned int depth) {
    int bestValue = -2147483;
    bitboard bestMove;

    std::vector<bitboard> possible = root.possibleMoves();
    for (const bitboard move : possible) { 
        Teeko node = Teeko(root);
        node.makeMove(move);
        //if (node.isWin()) { return move; }
        int value = -solve(node, depth - 1);

        if (value > bestValue) {
            bestValue = value;
            bestMove = move;
        }
    }
    // print best value
    std::cout << "best value: " << bestValue << std::endl;
    return bestMove;
};

#endif
