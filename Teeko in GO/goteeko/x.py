def is_palindrome(number_str):
    return number_str == number_str[::-1]

def find_largest_palindrome(limit):
    for num in range(limit - 1, 0, -1):
        num_base_10 = str(num)
        num_base_8 = oct(num)[2:]
        
        if is_palindrome(num_base_10) and is_palindrome(num_base_8):
            return num
    return None

if __name__ == "__main__":
    limit = 1000
    largest_palindrome = find_largest_palindrome(limit)
    print("The largest palindrome in both base 10 and base 8 less than", limit, "is:", largest_palindrome)
