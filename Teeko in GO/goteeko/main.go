//package main

import "fmt"

func main() {
	game := makeTeeko()
	for game.isWin() == false {
		fmt.Print("\033[H\033[2J")
		game.print()

		var pt string
		if game.current_player == BLACK_TURN {
			pt = "\u001b[30;1mBlack\u001b[0m"
		} else {
			pt = "\u001b[31;1mRed\u001b[0m"
		}

		if game.phase() == DROP_PHASE {
			var position_x uint32
			var position_y uint32
			fmt.Print(pt, " enter drop: ")
			var input string
			fmt.Scanln(&input)
			position_x = uint32(input[0]-48) - 1
			position_y = uint32(input[1]-48) - 1

			game.dropMarker(bitboard(1 << (position_x*uint32(LENGTH) + position_y)))
		} else {
			var marker_x uint32
			var marker_y uint32
			var destination_x uint32
			var destination_y uint32
			fmt.Println(pt, "enter move: ")
			var input string
			fmt.Scanln(&input)
			marker_x = uint32(input[0]-48) - 1
			marker_y = uint32(input[1]-48) - 1
			destination_x = uint32(input[2]-48) - 1
			destination_y = uint32(input[3]-48) - 1
			game.moveMarker(bitboard((1 << (marker_y*uint32(LENGTH) + marker_x)) & (1 << (destination_y*uint32(LENGTH) + destination_x))))
		}
	}
	fmt.Print("\033[H\033[2J")
	game.print()

}