#include <bitset>
#include <iostream>
#include <string>
#include <cassert>
struct Move {
    uint8_t start;
    uint8_t end;
};
    
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
            for (index position : black) {
                arrayboard[position] = "\u001b[31;1mR\u001b[0m"; 
            }

            std::reverse(std::begin(arrayboard), std::end(arrayboard));

            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "4" << "  |  " << arrayboard[0] << "  |  " << arrayboard[1] << "  |  " << arrayboard[2] << "  |  " << arrayboard[3] << "  |  " << arrayboard[4] << "  |" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "3" << "  |  " << arrayboard[5] << "  |  " << arrayboard[6] << "  |  " << arrayboard[7] << "  |  " << arrayboard[8] << "  |  " << arrayboard[9] << "  |" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "2" << "  |  " << arrayboard[10] << "  |  " << arrayboard[11] << "  |  " << arrayboard[12] << "  |  " << arrayboard[13] << "  |  " << arrayboard[14] << "  |" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "1" << "  |  " << arrayboard[15] << "  |  " << arrayboard[16] << "  |  " << arrayboard[17] << "  |  " << arrayboard[18] << "  |  " << arrayboard[19] << "  |" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "0" << "  |  " << arrayboard[20] << "  |  " << arrayboard[21] << "  |  " << arrayboard[22] << "  |  " << arrayboard[23] << "  |  " << arrayboard[24] << "  |" << std::endl;
            std::cout << "-------------------------------------------" << std::endl;
            std::cout << "|  " << "-" << "  |  " << "0" << "  |  " << "1" << "  |  " << "2" << "  |  " << "3" << "  |  " << "4" << "  |" << std::endl;
        };
};
