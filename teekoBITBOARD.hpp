#include <bitset>
#include <iostream>
#include <string>

    
class Teeko {
    public:
        // the size of the board is 5 * 5 = 25 tiles
        using bitboard = uint32_t; 
        static constexpr unsigned int LENGTH = 5;

        bitboard red = 0;
        bitboard black = 0;
        unsigned int moveCounter = 0;
        
        Teeko() {};

        Teeko(const Teeko& other) { 
            red = other.red;
            black = other.black;
            moveCounter = other.moveCounter;
        }

        // the move consist of a 2 bits one of the piece to be moved and the other of the destination
        void play(bitboard move) {
            // black is the player who plays first
            if (currentPlayer() == 0) {
                black ^= move;
            } else {
                red |= move;
            }
            moveCounter++;
        }

        bitboard mask() const {
            return black | red;
        }

        void play(unsigned int row, unsigned int column) {
            unsigned int idx = column * LENGTH + row; 
            play((bitboard)1 << idx);
        }

        unsigned int currentPlayer() const {
            return moveCounter & 1;
        }

        bool isWin() const {
            // or could check if position is equal to all winning positions

            // horizontal
            bitboard position;

            if (currentPlayer() == 0) {
                position = red;
            } else {
                position = black;
            }

            bitboard m = position & (position >> (LENGTH));
            if(m & (m >> (3 * (LENGTH)))) return true;

            // diagonal 1
            m = position & (position >> (LENGTH - 1));
            if(m & (m >> (3 * (LENGTH - 1)))) return true;

            // diagonal 2 
            m = position & (position >> (LENGTH + 1));
            if(m & (m >> (3 * (LENGTH + 1)))) return true;

            // vertical;
            m = position & (position >> 1);
            if(m & (m >> 3)) return true;

            return false;
        };

        // check if chaos won
      
        void print() const {
            std::string arrayboard[25] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};
            
            std::string blackBits = std::bitset<36>(black).to_string();
            std::string redBits = std::bitset<36>(red).to_string();

            // black player 
            for (int i = 0; i < 25; i++) {
                if (blackBits[i] == '1') { arrayboard[i] = "\u001b[30;1mB\u001b[0m"; } 
            }

            // red player
            for (int i = 0; i < 25; i++) {
                if (redBits[i] == '1') { arrayboard[i] = "\u001b[31;1mR\u001b[0m"; } 
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

        static constexpr bitboard indexMask(unsigned int index) {
            return (bitboard)1 << index;
        };

        static constexpr bitboard boardMask = 0b1111111111111111111111111;
};
