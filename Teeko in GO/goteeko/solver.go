package main

import "fmt"


func factorial(number uint) uint {
    if number >= 1 {
        return number * factorial(number - 1)
    } else {
        return 1
    }
}


// for decode we do not precompute at we only compute values of 25 times
func encode(game Teeko) uint32 {
	var n uint = 0; // index of the current location in mask array of size [8]
	var p uint = 0; // index of the current location in pattern array of size [4]

	var pattern_encoding uint32 = 1 // order of marker colors with array of size [4] and of values 1 to 8
	var mask_encoding uint32 = 1

	var current_marker_index uint = 0 // index of marker on board 
	var current_pattern_index uint = 0 
	for i := uint(0); i <= 25; i++ {
		if game.mask & bitboard(1 << i) != 0 {
			var last_marker_index uint = current_marker_index; // last marker index
			current_marker_index = i;
			
			
			{ // new scope dont like this move out
				var max uint64 = 1 
				var num uint64 = 1
				for j := uint(25); j != (25 - (8 - n)); j-- {
					max *= uint64(j - last_marker_index)
					num *= uint64(1 + j - current_marker_index) 
				}	
				mask_encoding += uint32((max - num) / uint64(factorial(8 - n)));
				
			}
			n += 1
			
		
			if game.position & bitboard(1 << i) != 0 {
				var last_pattern_index uint = current_pattern_index
				current_pattern_index = n;
				
				var max uint64 = 1 
				var num uint64 = 1
				for j := uint(8); j != (8 - (4 - p)); j-- {
					max *= uint64(j - last_pattern_index)
					num *= uint64(1 + j - current_pattern_index) 
				}	
				pattern_encoding += uint32((max - num) / uint64(factorial(4 - p)));
				p += 1
			}
		}
	}
	fmt.Println(mask_encoding);
	return mask_encoding // + (biggest_possible * (pattern_encoding - 1)
}


func decode(key uint32) Teeko {
	var game Teeko = makeTeeko();


	var n uint = 0; // index of the current location in mask array of size [8]

	var current_marker_index uint = 0 // index of marker on board 
	var last_k uint32 = 0;
	var hold uint32 = 0;
	var last_marker_index uint
	for i := uint(1); i <= 26; i++ { // maybe change to 25
		current_marker_index = i;
		fmt.Println("I: ", i)
		
		
		
		var max uint64 = 1 
		var num uint64 = 1
		for j := uint(25); j != (25 - (8 - n)); j-- {
			max *= uint64(j - last_marker_index)
			num *= uint64(1 + j - current_marker_index) 
		}	
		max = max / uint64(factorial(8 - n))
		num = num / uint64(factorial(8 - n))
		//fmt.Println("max: ", max)
		//fmt.Println("num: ", num)

		var k uint32 = uint32(max - num);
		//fmt.Println("k: ", k)

		
		var temp uint32 = uint32(int64((hold + uint32(max))) - int64(key))
		//fmt.Println("temp: ", int64((hold + uint32(max))) - int64(key))


		//fmt.Println("hold: ", hold)


		if (temp >= uint32(num)) {
			fmt.Println("mark: ", i - 1)
			n += 1
			hold += last_k
			last_marker_index = current_marker_index - 1; // last marker index
			i -= 1; // added
		} // issue with skipping one and causing problem solve soon plase


		last_k = k
		//fmt.Println("")
	}


	return game
}


func main() {
	game := makeTeeko()
	var black_indexes [4]uint32 = [4]uint32{5, 8, 11, 22};
	var red_indexes [4]uint32 = [4]uint32{2, 10, 15, 23} 
	
	game.mask |= bitboard(1 << black_indexes[0])
	game.mask |= bitboard(1 << black_indexes[1])
	game.mask |= bitboard(1 << black_indexes[2])
	game.mask |= bitboard(1 << black_indexes[3])

	game.mask |= bitboard(1 << red_indexes[0])
	game.mask |= bitboard(1 << red_indexes[1])
	game.mask |= bitboard(1 << red_indexes[2])
	game.mask |= bitboard(1 << red_indexes[3])

	game.position |= bitboard(1 << black_indexes[0])
	game.position |= bitboard(1 << black_indexes[1])
	game.position |= bitboard(1 << black_indexes[2])
	game.position |= bitboard(1 << black_indexes[3])


	key := encode(game)
	fmt.Println(key)

	fmt.Println(decode(key)) 
}