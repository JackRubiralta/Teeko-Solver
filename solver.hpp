#ifndef SOLVER_HPP
#define SOLVER_HPP
#include "teeko.hpp"
#include <algorithm>
#include <unordered_set>
#include <vector>
class Node {  // changed to class because class is refernce instead of by value
    public:
        Teeko game;
        std::vector<Node> children;
        Node(const Teeko g) {
            game = g;
        }
};

std::unordered_set<uint64_t> previousStates = std::unordered_set<uint64_t>();
// use unordered_map to store the previous states
// with the key and then the value is the node as reference

Node gameGraph;
void generateGameGraph() {
    Teeko game = Teeko();
    gameGraph.game = game;
    for (const Teeko child : game.generateChildren()) {
        gameGraph.children.push_back(Node(child));
    }
    iterativeGeneration(gameGraph.children);
}

unsigned int currentIteration = 0;
void iterativeGeneration(std::vector<Node> parents) {
    currentIteration++;

    std::vector<Node> children;
    for (Node parent : parents) { // dont need to pass by refernce 
        for (const Teeko childGame : parent.game.generateChildren()) {
            if (childGame.isWin()) {
                Node child = Node(childGame);
                parent.children.push_back(child);
                continue;
            }

            if (previousStates.find(childGame.key()) == previousStates.end()) {
                Node child = Node(childGame);
                
                parent.children.push_back(child);
                previousStates.insert(childGame.key());
                children.push_back(child);
            } else {
                // add child as refernce to other node in graph
                // parent.children.push_back(ref of other node in graph);
            }
        }
    }
    
    // clear progress bar
    std::cout << "\r";
    // print current iteration
    std::cout << "Iteration " << currentIteration++ << "; ";
    std::cout << "Nodes: " << previousStates.size() << "; ";
    std::cout << "Children: " << children.size() << "; ";
    std::cout << std::endl;
    iterativeGeneration(children);
}

#endif
