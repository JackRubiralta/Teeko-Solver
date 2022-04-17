#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <cassert>
using std::string;

    
class Teeko {
    public:
        static constexpr unsigned int LENGTH = 5;
        using index = uint8_t;

        // list of the indexes of the pieces
        index black[4] = {3, 4, 20, 21};
        index red[4] = {0, 1, 23, 24};
        unsigned int moveCounter = 0;
        
        Teeko() {};

        Teeko(const Teeko &other) { 
            black[0], black[1], black[2], black[3] = other.black[0], other.black[1], other.black[2], other.black[3];
            red[0], red[1], red[2], red[3] = other.red[0], other.red[1], other.red[2], other.red[3];
            moveCounter = other.moveCounter;
        }

        // marker is the index of the piece to be moved (0-3)
        void play(const unsigned int marker, const index delta) {
            assert(marker < 3);
            // black is the player who plays first
            if (currentPlayer() == 0) {
                black[marker] += delta;
            } else {
                red[marker] += delta;
            }
            moveCounter++;
        }

        void playMove(index start, index end) {
            moveCounter++;
            if (currentPlayer() == 0) {
                for (index &marker : black) {
                    if (marker == start) {
                        marker = end;
                        return;
                    }
                }
            } else {
                for (index &marker : red) {
                    if (marker == start) {
                        marker = end;
                        return;
                    }
                }
            }
        }

        unsigned int currentPlayer() const {
            return moveCounter & 1;
        }
      
        void print() const {
            std::string arrayboard[25] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};
            

            // black player 
            for (index position : black) {
                arrayboard[position] = "\u001b[30;1mB\u001b[0m"; 
            }

            // red player
            for (index position : red) {
                arrayboard[position] = "\u001b[31;1mR\u001b[0m"; 
            }


            std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            
            
            std::cout << "\u001b[36m|\u001b[0m  " << "\u001b[34m4\u001b[0m" << "  \u001b[36m|\u001b[0m  " << arrayboard[20] << "  \u001b[36m|\u001b[0m  " << arrayboard[21] << "  \u001b[36m|\u001b[0m  " << arrayboard[22] << "  \u001b[36m|\u001b[0m  " << arrayboard[23] << "  \u001b[36m|\u001b[0m  " << arrayboard[24] << "  \u001b[36m|\u001b[0m" << std::endl; std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            std::cout << "\u001b[36m|\u001b[0m  " << "\u001b[34m3\u001b[0m" << "  \u001b[36m|\u001b[0m  " << arrayboard[15] << "  \u001b[36m|\u001b[0m  " << arrayboard[16] << "  \u001b[36m|\u001b[0m  " << arrayboard[17] << "  \u001b[36m|\u001b[0m  " << arrayboard[18] << "  \u001b[36m|\u001b[0m  " << arrayboard[19] << "  \u001b[36m|\u001b[0m" << std::endl; std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            std::cout << "\u001b[36m|\u001b[0m  " << "\u001b[34m2\u001b[0m" << "  \u001b[36m|\u001b[0m  " << arrayboard[8] << "  \u001b[36m|\u001b[0m  " << arrayboard[9] << "  \u001b[36m|\u001b[0m  " << arrayboard[10] << "  \u001b[36m|\u001b[0m  " << arrayboard[11] << "  \u001b[36m|\u001b[0m  " << arrayboard[12] << "  \u001b[36m|\u001b[0m" << std::endl; std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            std::cout << "\u001b[36m|\u001b[0m  " << "\u001b[34m1\u001b[0m" << "  \u001b[36m|\u001b[0m  " << arrayboard[3] << "  \u001b[36m|\u001b[0m  " << arrayboard[4] << "  \u001b[36m|\u001b[0m  " << arrayboard[5] << "  \u001b[36m|\u001b[0m  " << arrayboard[6] << "  \u001b[36m|\u001b[0m  " << arrayboard[7] << "  \u001b[36m|\u001b[0m" << std::endl; std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            std::cout << "\u001b[36m|\u001b[0m  " << "\u001b[34m0\u001b[0m" << "  \u001b[36m|\u001b[0m  " << arrayboard[0] << "  \u001b[36m|\u001b[0m  " << arrayboard[1] << "  \u001b[36m|\u001b[0m  " << arrayboard[2] << "  \u001b[36m|\u001b[0m  " << arrayboard[13] << "  \u001b[36m|\u001b[0m  " << arrayboard[14] << "  \u001b[36m|\u001b[0m" << std::endl; std::cout << "\u001b[36m-------------------------------------\u001b[0m" << std::endl;
            std::cout << "\u001b[36m|\u001b[0m  " << "-" << "  \u001b[36m|\u001b[0m  " << "\u001b[34m0\u001b[0m" << "  \u001b[36m|\u001b[0m  " << "\u001b[34m1\u001b[0m" << "  \u001b[36m|\u001b[0m  " << "\u001b[34m2\u001b[0m" << "  \u001b[36m|\u001b[0m  " << "\u001b[34m3\u001b[0m" << "  \u001b[36m|\u001b[0m  " << "\u001b[34m4\u001b[0m" << "  \u001b[36m|\u001b[0m" << std::endl;
        };
};
