# Practice Makes Perfect
# Is_Even
def is_even(x):
    if (x % 2 == 0): return True
    else: return False

# Is_Int
import math

def is_int(x):
    if (math.floor(x) == x): return True
    else: return False

# Digit_Sum
def digit_sum(n):
    digit_string = str(n)
    total = 0
    for char in digit_string:
        total += int(char)
    return total

# Factorial
def factorial(x):
    total = 1
    for i in range(1,x+1):
        total *= i
    return total

# Is_Prime
def is_prime(x):
    if (x < 2): return False
    for i in range(2,x-1):
        if (x % i == 0): return False
    return True

# Reverse
def reverse(string):
    return_str = ""
    length = len(string)-1
    for i in range(len(string)):
        return_str += string[length]
        length -= 1
    return return_str

# Anti_Vowel
def anti_vowel(text):
    returnString = ""
    for char in text:
        if (not(char in "aeiouAEIOU")):
            returnString += char
    return returnString

# Scrabble_Score
score = {"a": 1, "c": 3, "b": 3, "e": 1, "d": 2, "g": 2, 
         "f": 4, "i": 1, "h": 4, "k": 5, "j": 8, "m": 3, 
         "l": 1, "o": 1, "n": 1, "q": 10, "p": 3, "s": 1, 
         "r": 1, "u": 1, "t": 1, "w": 4, "v": 4, "y": 4, 
         "x": 8, "z": 10}

def scrabble_score(word):
    total = 0
    for char in word:
        total += score[char.lower()]
    return total

# Censor
def censor(text, word):
    result = ""
    filler = "*" * len(word)
    result = filler.join(text.split(word))
    return result

# Count
def count(sequence, item):
    total = 0
    for num in sequence:
        if (num == item):
            total += 1
    return total

# Purify
def purify(nums):
    only_evens = []
    for x in nums:
        if (x % 2 == 0):
            only_evens.append(x)
    return only_evens

# Product
def product(nums):
    total = 1
    for i in nums:
        total *= i
    return total

# Remove_Duplicates
def remove_duplicates(lst):
    final = []
    for item in lst:
        if (not(item in final)):
            final.append(item)
    return final

# Median
def median(nums):
    new = sorted(nums)
    if (len(new) % 2 == 0):
        #even length list
        print new[len(new)/2 - 1]
        print new[len(new)/2]
        return ((new[len(new)/2] + new[len(new)/2 - 1]))/2.0
    else:
        #odd length
        return new[len(new)/2]
