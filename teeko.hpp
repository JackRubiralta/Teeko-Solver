#include <bitset>
#include <iostream>
#include <string>

/*
Board Position
    20 21 22 23 24
    15 16 17 18 19
    10 11 12 13 14
    05 06 07 08 09
    00 01 02 03 04
*/



class Teeko {
    public:
        // the size of the board is 5 * 5 = 25 tiles
        using bitboard = uint32_t; 
        static constexpr unsigned int LENGTH = 5;

        bitboard red = 0b1100000000000000011000;
        bitboard black = 0b1100000000000000000000011;
        unsigned int moveCounter = 0;
        
        Teeko() {};

        Teeko(const Teeko& other) { 
            red = other.red;
            black = other.black;
            moveCounter = other.moveCounter;
        }

        // the move consist of a 2 bits one of the piece to be moved and the other of the destination
        void makeMove(bitboard move) {
            std::cout << "move: " << std::bitset<25>(move) << std::endl;
            // black is the player who plays first
            if (currentPlayer() == 0) {
                black ^= move;
            } else {
                red ^= move;
            }
            moveCounter++;
        }

        void makeMove(unsigned int markerIndex, unsigned int destinationIndex) {
            makeMove((bitboard)1 << markerIndex | (bitboard)1 << destinationIndex);
        }

        void makeMove(unsigned int markerColumn, unsigned int markerRow, unsigned int destinationColumn, unsigned int destinationRow) {
            unsigned int markerIndex = markerRow * LENGTH + markerColumn; 
            unsigned int destinationIndex = destinationRow * LENGTH + destinationColumn; 
            makeMove(markerIndex, destinationIndex);
        }

        bitboard mask() const {
            return black | red;
        }

        unsigned int currentPlayer() const {
            return moveCounter & 1;
        }

        bool isWin() const {
            // or could check if position is equal to all winning positions

            // horizontal
            bitboard position;
            if (currentPlayer() == 0) { position = red; } else { position = black; }

            bitboard m = position & (position >> (LENGTH));
            if(m & (m >> (2 * (LENGTH)))) return true;

            // diagonal 1
            m = position & (position >> (LENGTH - 1));
            if(m & (m >> (2 * (LENGTH - 1)))) return true;

            // diagonal 2 
            m = position & (position >> (LENGTH + 1));
            if(m & (m >> (2 * (LENGTH + 1)))) return true;

            // vertical;
            m = position & (position >> 1);
            if(m & (m >> 2)) return true;

            return false;
        };
      
        void print() const {
            const std::string verticalSeperator = "\u001b[36m|\u001b[0m";
            const std::string horizontalSeperator = "\u001b[36m-------------------------------------\u001b[0m";
            const std::string redMarker = "\u001b[31;1mR\u001b[0m";
            const std::string blackMarker = "\u001b[30;1mB\u001b[0m";

            std::string arrayboard[25] = {"-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-", "-"};

            for (int i = 0; i < 25; i++) {
                if ((((bitboard)1 << i) & black) != 0) {
                    arrayboard[i] = blackMarker;
                }
                if ((((bitboard)1 << i) & red) != 0) {
                    arrayboard[i] = redMarker;
                } 
            }
            
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "\u001b[34m4\u001b[0m" << "  " << verticalSeperator << "  " << arrayboard[20] << "  " << verticalSeperator << "  " << arrayboard[21] << "  " << verticalSeperator << "  " << arrayboard[22] << "  " << verticalSeperator << "  " << arrayboard[23] << "  " << verticalSeperator << "  " << arrayboard[24] << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "\u001b[34m3\u001b[0m" << "  " << verticalSeperator << "  " << arrayboard[15] << "  " << verticalSeperator << "  " << arrayboard[16] << "  " << verticalSeperator << "  " << arrayboard[17] << "  " << verticalSeperator << "  " << arrayboard[18] << "  " << verticalSeperator << "  " << arrayboard[19] << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "\u001b[34m2\u001b[0m" << "  " << verticalSeperator << "  " << arrayboard[10] << "  " << verticalSeperator << "  " << arrayboard[11] << "  " << verticalSeperator << "  " << arrayboard[12] << "  " << verticalSeperator << "  " << arrayboard[13] << "  " << verticalSeperator << "  " << arrayboard[14] << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "\u001b[34m1\u001b[0m" << "  " << verticalSeperator << "  " << arrayboard[5] << "  " << verticalSeperator << "  " << arrayboard[6] << "  " << verticalSeperator << "  " << arrayboard[7] << "  " << verticalSeperator << "  " << arrayboard[8] << "  " << verticalSeperator << "  " << arrayboard[9] << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "\u001b[34m0\u001b[0m" << "  " << verticalSeperator << "  " << arrayboard[0] << "  " << verticalSeperator << "  " << arrayboard[1] << "  " << verticalSeperator << "  " << arrayboard[2] << "  " << verticalSeperator << "  " << arrayboard[3] << "  " << verticalSeperator << "  " << arrayboard[4] << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << "  " << "-" << "  " << verticalSeperator << "  " << "\u001b[34m0\u001b[0m" << "  " << verticalSeperator << "  " << "\u001b[34m1\u001b[0m" << "  " << verticalSeperator << "  " << "\u001b[34m2\u001b[0m" << "  " << verticalSeperator << "  " << "\u001b[34m3\u001b[0m" << "  " << verticalSeperator << "  " << "\u001b[34m4\u001b[0m" << "  \u001b[36m|\u001b[0m" << std::endl;
            std::cout << horizontalSeperator << std::endl;
        };

        static constexpr bitboard indexMask(unsigned int index) {
            return (bitboard)1 << index;
        };

        static constexpr bitboard boardMask = 0b1111111111111111111111111;
};
