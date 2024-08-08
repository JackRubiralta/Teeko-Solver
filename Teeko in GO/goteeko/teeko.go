package main

import "fmt"

type bitboard uint32

const LENGTH bitboard = 5 // size of board (LENGTH x LENGTH)
type Teeko struct {
	position       bitboard
	mask           bitboard
	current_player bool // black to move is zero
}

const DROP_PHASE bool = false
const MOVE_PHASE bool = true

const BLACK_TURN bool = false
const RED_TURN bool = true

func makeTeeko() Teeko {
	return Teeko{0, 0, BLACK_TURN}
}

func (game *Teeko) phase() bool {
	var n bitboard = game.position
	n = n & (n - 1)
	n = n & (n - 1)
	n = n & (n - 1)

	if n != 0 { // still has one bit set
		return MOVE_PHASE
	} else {
		return DROP_PHASE
	}
}

func (game *Teeko) dropMarker(drop bitboard) {
	if game.current_player == BLACK_TURN { // black goes first
		game.current_player = RED_TURN
	} else {
		game.current_player = BLACK_TURN
	}
	game.position = game.position ^ game.mask
	game.mask |= drop
}

func (game *Teeko) moveMarker(move bitboard) {
	if game.current_player == BLACK_TURN { // black goes first
		game.current_player = RED_TURN
	} else {
		game.current_player = BLACK_TURN
	}
	game.position = game.position ^ game.mask
	game.mask |= move

}

func (game *Teeko) isWin() bool {
	// replace game.position with game.position & game.mask
	var opponent bitboard = game.position ^ game.mask

	// horizontal
	if ((opponent & (opponent >> 1) & (opponent >> 2) & (opponent >> 3)) & 0b0001100011000110001100011) != 0 {
		return true
	}

	// vertical
	if ((opponent & (opponent >> (LENGTH * 1)) & (opponent >> (LENGTH * 2)) & (opponent >> (LENGTH * 3))) & 0b0000000000000001111111111) != 0 {
		return true
	}

	// diagonal
	if ((opponent & (opponent >> ((LENGTH + 1) * 1)) & (opponent >> ((LENGTH + 1) * 2)) & (opponent >> ((LENGTH + 1) * 3))) & 0b0001100011000110001100011) != 0 {
		return true
	}

	// diagonal
	if ((opponent & (opponent >> ((LENGTH - 1) * 1)) & (opponent >> ((LENGTH - 1) * 2)) & (opponent >> ((LENGTH - 1) * 3))) & 0b1100011000110001100011000) != 0 {
		return true
	}

	// square
	if ((opponent & (opponent >> 1) & (opponent >> LENGTH) & (opponent >> (LENGTH + 1))) & 0b011110111101111011110111101111) != 0 {
		return true
	}

	return false
}

func (game *Teeko) possibleMoves() []bitboard { // return this or return all moves
	const board_mask bitboard = 0b1111111111111111111111111
	var markers bitboard = game.position
	var unoccupied bitboard = game.mask ^ board_mask

	var possible_moves []bitboard
	for markers != 0 {
		var current_marker bitboard = markers ^ (markers & (markers - 1))
		markers ^= current_marker

		var move bitboard

		move = ((current_marker << 1) & 0b1111011110111101111011110) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = ((current_marker << 6) & 0b1111011110111101111011110) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = ((current_marker >> 4) & 0b1111011110111101111011110) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = ((current_marker >> 1) & 0b0111101111011110111101111) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = ((current_marker >> 6) & 0b0111101111011110111101111) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = ((current_marker << 4) & 0b0111101111011110111101111) & unoccupied
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = (current_marker >> 5) & unoccupied // south
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}

		move = (current_marker << 5) & unoccupied // north
		if move != 0 {
			possible_moves = append(possible_moves, move)
		}
	}
	return possible_moves
}

func (game *Teeko) possibleDrops() []bitboard {
	const board_mask bitboard = 0b1111111111111111111111111

	var empty_positions bitboard = game.mask ^ board_mask
	var possible_drops []bitboard
	for empty_positions != 0 {
		var current_position bitboard = empty_positions ^ (empty_positions & (empty_positions - 1))
		empty_positions ^= current_position
		possible_drops = append(possible_drops, current_position)
	}
	return possible_drops
}

func (game *Teeko) print() {
	const vertical_separator string = "\u001b[36m|"
	const horizontal_separator string = "\u001b[36m-------------------------------------"

	var black bitboard
	var red bitboard
	if game.current_player == BLACK_TURN {
		black = game.position
		red = game.position ^ game.mask
	} else {
		black = game.position ^ game.mask
		red = game.position
	}

	for row := (LENGTH); row != 0; row-- {

		fmt.Print(horizontal_separator, "\n")
		fmt.Print(vertical_separator, "  ", row, "  ")
		for column := bitboard(1); column <= bitboard(LENGTH); column++ {
			fmt.Print(vertical_separator)

			var index bitboard = (column-1)*(LENGTH) + (row - 1)
			if ((1 << index) & black) != 0 {
				fmt.Print("  ", "\u001b[30;1mB", "  ")

			} else if ((1 << index) & red) != 0 {
				fmt.Print("  ", "\u001b[31;1mR", "  ")

			} else if false {
				fmt.Print("  ", "\u001b[35;1m+", "  ")
			} else {
				fmt.Print("  ", "\u001b[0m-", "  ")

			}
		}
		fmt.Print(vertical_separator, "\n")
	}
	fmt.Print(horizontal_separator, "\n")

	fmt.Print(vertical_separator, "  ", "0", "  ")
	for column := uint(1); column <= uint(LENGTH); column++ {
		fmt.Print(vertical_separator)
		fmt.Print("  ", column, "  ")
	}
	fmt.Print(vertical_separator, "\n")
	fmt.Print(horizontal_separator, "\n")
	fmt.Print("\u001b[0m")
}

/*

func encode(game Teeko) uint32 {
	//var mask_indexes[8] = 
	return 1;
}
func decode(pos uint32) Teeko {
	// pos / 70 first
	// loop though 0 to 25 and find k1 k2 k3 k4 k5 k6
	// check by seeing it it is more
	// if k1 is a 2
	// subtract k1 at 2 to pos
	// go from 3 to find k2
	return makeTeeko();
}
*/