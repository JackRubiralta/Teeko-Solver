import math

def combination_index(comb, n):
    """
    Computes the lexicographical index of the combination 'comb' among all combinations
    of len(comb) elements from n elements.
    """
    index = 0
    k = len(comb)
    for i in range(k):
        x = comb[i]
        if i == 0:
            start = 0
        else:
            start = comb[i - 1] + 1
        for j in range(start, x):
            index += math.comb(n - j - 1, k - i - 1)
    return index

def index_to_combination(index, n, k):
    """
    Converts an index back to the combination of k elements out of n.
    Returns a list of indices representing the combination.
    """
    comb = []
    a = index
    x = 0
    for i in range(k):
        for j in range(x, n - k + i + 1):
            c = math.comb(n - j - 1, k - i - 1)
            if a < c:
                comb.append(j)
                x = j + 1
                break
            else:
                a -= c
    return comb

def encode_position(position):
    """
    Encodes a Teeko game position into a unique number.
    """
    # Extract occupied positions S
    S = [i for i, disc in enumerate(position) if disc != 0]
    S.sort()
    k = combination_index(S, 25)
    
    # Extract red disc positions R within S
    R = [S.index(i) for i in S if position[i] == 1]
    R.sort()
    l = combination_index(R, 8)
    
    # Compute final encoding number N
    N = k * math.comb(8, 4) + l
    return N

def decode_position(N):
    """
    Decodes the unique number back into the Teeko game position.
    """
    total_red_combinations = math.comb(8, 4)
    k = N // total_red_combinations
    l = N % total_red_combinations
    
    # Reconstruct S
    S = index_to_combination(k, 25, 8)
    
    # Reconstruct R (indices within S)
    R_indices = index_to_combination(l, 8, 4)
    R = [S[i] for i in R_indices]
    
    # Build the game position
    position = [0] * 25
    for i in S:
        position[i] = 2  # Black disc by default
    for i in R:
        position[i] = 1  # Red disc
    return position

def main():
    total_positions = math.comb(25, 8) * math.comb(8, 4)
    print(f"Total number of positions to test: {total_positions}")
    
    # Uncomment the following line to run the full test
    # for i in range(total_positions):
    
    # For practical purposes, let's test a subset (e.g., the first 1000 positions)
    test_limit = 75000000  # Change this number to increase or decrease the test range
    for i in range(test_limit):
        # Decode the position from the number
        position = decode_position(i)
        print(position)
        
        # Encode the position back to a number
        N = encode_position(position)
        
        # Check if the re-encoded number matches the original
        if N != i:
            print(f"Discrepancy found at index {i}: Encoded back to {N}")
            break
        # Optional: Print progress every 100 iterations
        if i % 100 == 0:
            print(f"Progress: Tested up to position {i}")
    else:
        print("Test passed: All positions encode and decode correctly within the test limit.")

if __name__ == "__main__":
    main()
