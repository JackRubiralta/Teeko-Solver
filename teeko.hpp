#include <bitset>
#include <iostream>
#include <string>
#include <vector>
#include <array> 


// MAX MOVES = 100
/*
Board Position
    20 21 22 23 24
    15 16 17 18 19
    10 11 12 13 14
    05 06 07 08 09
    00 01 02 03 04
*/

using bitboard = uint32_t; 


class Teeko {
    public:
        // the size of the board is 5 * 5 = 25 tiles
        static constexpr unsigned int LENGTH = 5;
        static constexpr unsigned int MAX_MOVES = 100;
        
        bitboard red;
        bitboard black;
        unsigned int moveCounter = 0;
        
        Teeko(bool x) {
            unsigned int blackIndexes[4] = {14, 18, 19, 24};
            unsigned int redIndexes[4] = {13, 15, 17, 23};
            for (unsigned int i; i != 4; i++) {
                black |= (bitboard)1 << (blackIndexes[i] - 1); 
                red |= (bitboard)1 << (redIndexes[i] - 1);
            }
        }

        Teeko() {
            red = 0b1100000000000000011000;
            black = 0b1100000000000000000000011;
        };

        Teeko(const Teeko& other) { 
            red = other.red;
            black = other.black;
            moveCounter = other.moveCounter;
        }

        // the move consist of a 2 bits one of the piece to be moved and the other of the destination
        void makeMove(bitboard move) {
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
            bitboard position;
            if (currentPlayer() == 0) { position = red; } else { position = black; }

            bitboard m;
            m = position & (position >> 1) & (position >> 2) & (position >> 3);
            if ((m & 0b0001100011000110001100011) != 0) {
                return true;
            }

            // vertical
            m = position & (position >> 5) & (position >> 10) & (position >> 15);
            if ((m & 0b0000000000000001111111111) != 0) {
                return true;
            }

            // diagonal 1
            m = position & (position >> 6) & (position >> 12) & (position >> 18);
            if ((m & 0b0001100011) != 0) {
                return true;
            }

            m = position & (position >> 4) & (position >> 8) & (position >> 12);
            if ((m & 0b1100011000) != 0) {
                return true;
            }
            return false;
        };

        bool isDraw() const {
            return moveCounter >= MAX_MOVES;
        }

        bool isGameOver() const {
            return isWin() || isDraw();
        }

        std::vector<bitboard> possibleMoves() const {
            std::vector<bitboard> moves = std::vector<bitboard>();

            bitboard markers = currentPlayer() == 0 ? black : red; 
            const bitboard unoccupied = ~mask();

            while (markers != 0) {
                bitboard marker = (markers & -markers);
                markers ^= marker;

                bitboard move;    
                move = ((marker << 1) & 0b1111011110111101111011110) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = ((marker << 6) & 0b1111011110111101111011110) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = ((marker >> 4) & 0b1111011110111101111011110) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = ((marker >> 1) & 0b0111101111011110111101111) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = ((marker >> 6) & 0b0111101111011110111101111) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = ((marker << 4) & 0b0111101111011110111101111) & unoccupied;
                if (move != 0) { moves.push_back(move | marker); };
                move = (marker >> 5) & unoccupied; // south
                if (move != 0) { moves.push_back(move | marker); };
                move = (marker << 5) & unoccupied; // north 
                if (move != 0) { moves.push_back(move | marker); };
            }      
            return moves;      
        }

        uint64_t key() const {
            return (uint64_t)red | ((uint64_t)black << 32);
        }

        void print() const {
            const std::string verticalSeperator = "\u001b[36m|\u001b[0m";
            const std::string horizontalSeperator = "\u001b[36m-------------------------------------\u001b[0m";
            const std::string redMarker = "\u001b[31;1m R \u001b[0m";
            const std::string blackMarker = "\u001b[30;1m B \u001b[0m";
            std::string arrayboard[25] = {" - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - ", " - "};
            

            for (int i = 0; i < 25; i++) {
                if ((((bitboard)1 << i) & black) != 0) {
                    arrayboard[i] = blackMarker;
                }
                if ((((bitboard)1 << i) & red) != 0) {
                    arrayboard[i] = redMarker;
                }
                for (const bitboard move : possibleMoves()) {
                    if ((((bitboard)1 << i) & (move & ~mask())) != 0) {
                        arrayboard[i] = "\u001b[35;1m + \u001b[0m";
                    }
                } 
            }
            
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << "\u001b[34m 4 \u001b[0m" << " " << verticalSeperator << " " << arrayboard[20] << " " << verticalSeperator << " " << arrayboard[21] << " " << verticalSeperator << " " << arrayboard[22] << " " << verticalSeperator << " " << arrayboard[23] << " " << verticalSeperator << " " << arrayboard[24] << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << "\u001b[34m 3 \u001b[0m" << " " << verticalSeperator << " " << arrayboard[15] << " " << verticalSeperator << " " << arrayboard[16] << " " << verticalSeperator << " " << arrayboard[17] << " " << verticalSeperator << " " << arrayboard[18] << " " << verticalSeperator << " " << arrayboard[19] << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << "\u001b[34m 2 \u001b[0m" << " " << verticalSeperator << " " << arrayboard[10] << " " << verticalSeperator << " " << arrayboard[11] << " " << verticalSeperator << " " << arrayboard[12] << " " << verticalSeperator << " " << arrayboard[13] << " " << verticalSeperator << " " << arrayboard[14] << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << "\u001b[34m 1 \u001b[0m" << " " << verticalSeperator << " " << arrayboard[5] << " " << verticalSeperator << " " << arrayboard[6] << " " << verticalSeperator << " " << arrayboard[7] << " " << verticalSeperator << " " << arrayboard[8] << " " << verticalSeperator << " " << arrayboard[9] << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << "\u001b[34m 0 \u001b[0m" << " " << verticalSeperator << " " << arrayboard[0] << " " << verticalSeperator << " " << arrayboard[1] << " " << verticalSeperator << " " << arrayboard[2] << " " << verticalSeperator << " " << arrayboard[3] << " " << verticalSeperator << " " << arrayboard[4] << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
            std::cout << verticalSeperator << " " << " - " << " " << verticalSeperator << " " << "\u001b[34m 0 \u001b[0m" << " " << verticalSeperator << " " << "\u001b[34m 1 \u001b[0m" << " " << verticalSeperator << " " << "\u001b[34m 2 \u001b[0m" << " " << verticalSeperator << " " << "\u001b[34m 3 \u001b[0m" << " " << verticalSeperator << " " << "\u001b[34m 4 \u001b[0m" << " " << verticalSeperator << std::endl;
            std::cout << horizontalSeperator << std::endl;
        };

        static constexpr bitboard indexMask(unsigned int index) {
            return (bitboard)1 << index;
        };

        static constexpr bitboard boardMask = 0b1111111111111111111111111;
};
