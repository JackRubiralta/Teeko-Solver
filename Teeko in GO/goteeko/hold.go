
func decode(key uint32) Teeko {
	var cm uint32 = 0;  // current marker
	var lm uint32 = cm; // last marker
	var p uint64 = uint64(key / 70);
	var game Teeko = makeTeeko();

	var i uint32 = 0;
	for pos := uint32(0); pos <= 25; pos++ {
		//fmt.Println(pos)

		cm = pos + 1
		
		var max uint64 = 1;
		for j := uint32(25); j != (25 - (8 - i)); j-- {
			max *= uint64(j - lm);
		}
		max /= uint64(factorial((7 - i) + 1))


		var num uint64 = 1;
		for j := uint32(26); j != (26 - (8 - i)); j-- { 
			num *= uint64(j - cm);
		}
		
		num /= uint64(factorial((7 - i) + 1))
		//fmt.Println(num)
		//fmt.Println(max - uint64(p))
		fmt.Println(p)

		if (max - uint64(p)) >= num {
			game.mask |= bitboard(1 << bitboard(cm))
			
			p -= (max - num)
			i++;
			lm = cm
			
			//fmt.Println(max)
			//fmt.Println(num)
		}
	}
	return game
}
