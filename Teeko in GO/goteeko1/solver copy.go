
import "fmt"


func factorial(number uint32) uint32 {
    if number >= 1 {
        return number * factorial(number - 1)
    } else {
        return 1
    }
}


// for decode we do not precompute at we only compute values of 25 times
func encode(game Teeko) uint32 {
	var mask_indexes [8]uint32;
	var n uint32 = 0;
	var position_indexes [4]uint32;
	var p uint32 = 0;
	for i := uint32(0); i <= 25; i++ {
		if (game.mask & (bitboard(1) << bitboard(i))) != 0 {
			mask_indexes[n] = i;
			n++; 
			
			
			if (game.position & (bitboard(1) << bitboard(i))) != 0 {
				position_indexes[p] = n
				p++
			}
		}
	}

	var key uint32 = 0; 

	var cm uint32 = 0;  // current marker
	var lm uint32 = cm; // last marker

	for i := uint32(0); i != 8; i++ {
		lm = cm;
		cm = mask_indexes[i]
		var max uint64 = 1;
		var num uint64 = 1;
		for j := uint32(25); j != (25 - (8 - i)); j-- {
			max *= uint64(j - lm);
			num *= uint64(1 + j - cm); 
		}	
		key += uint32((max - num) / uint64(factorial(8 - i)));
	}



	key += 1
	
	var p1 uint32 = position_indexes[0]
	var p2 uint32 = position_indexes[1]
	var p3 uint32 = position_indexes[2]
	var p4 uint32 = position_indexes[3]
	
	var a1 uint32 = ((5) * (6) * (7) * (8) - (6 - p1) * (7 - p1) * (8 - p1) * (9 - p1)) / uint32(factorial(4))
	var a2 uint32 = ((6 - p1) * (7 - p1) * (8 - p1) - (7 - p2) * (8 - p2) * (9 - p2)) / uint32(factorial(3))
	var a3 uint32 = ((7 - p2) * (8 - p2) - (8 - p3) * (9 - p3)) / uint32(factorial(2))
	var a4 uint32 = ((8 - p3) - (9 - p4)) / (uint32(factorial(1)))
	
	key *= (a1 + a2 + a3+ a4 + 1)
	
	return key
}

func main() {
	game := makeTeeko()
	var black_indexes [4]uint32 = [4]uint32{7, 8, 11, 22};
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
	fmt.Println("key: ", key)

}