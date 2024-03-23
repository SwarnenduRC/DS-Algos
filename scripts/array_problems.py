import array
from itertools import permutations

class ArrayAlgos:
    def __init__(self) -> None:
        pass
    
    def isUnique(self, string: str, caseSensitive=False, canUseExtraSpace=True) -> bool:
        if len(string) == 0:
            return False
        if len(string) > 123:   #The string is having more than 123 charecters thus definitiely repeatitive characters
            return False
        if not string.isascii():    #If the string contains anything other than ASCII charecters then also we are not validating
            return False
        
        if not caseSensitive:
            string = string.upper()
        
        if canUseExtraSpace:
            char_arr = [False] * 123
            for idx in string:
                if char_arr[ord(idx)]:
                    return False
                char_arr[ord(idx)] = True
            return True
        else:
            string = ''.join(sorted(string))
            for idx in range(0, len(string) - 1):
                if string[idx] == string[idx+1]:
                    return False
            return True
        
    def isPermutation(self, stringOne: str, stringTwo: str, caseSensitive=False, ignoreWhiteSpace=False) -> bool:
        if len(stringOne) == 0 and len(stringTwo) == 0:
            return True
        if len(stringOne) == 0 or len(stringTwo) == 0:
            return False
        if len(stringOne) != len(stringTwo) and not ignoreWhiteSpace:
            return False
        if len(stringOne) > 123 or len(stringTwo) > 123:    ## Either string isn't of ASCII charecters
            return False
        
        if ignoreWhiteSpace:
            stringOne = stringOne.replace(" ", "")
            stringTwo = stringTwo.replace(" ", "")
        
        if not caseSensitive:
            stringOne = stringOne.upper()
            stringTwo = stringTwo.upper()
            
        charArr = [0] * 123
        for idx in stringOne:
            charArr[ord(idx)] += 1
            
        for idx in stringTwo:
            charArr[ord(idx)] -= 1
            if charArr[ord(idx)] < 0:
                return False
        return True
    
    def isPalindromePermutation(self, string: str):
        if not string:
            return False
        
        string = string.replace(" ", "")
        alphabets = dict()
        
        for char in string:
            if char in alphabets:
                alphabets[char] += 1
            else:
                alphabets[char] = 1
                
        oddCnt = 0
        for char, value in alphabets.items():
            if value % 2 > 0:
                oddCnt += 1
            
        if oddCnt > 1:
            return False
        return True
    
    
    
def main():
    stringOne = "abc"
    stringTwo = " b a c "
    #print(stringOne)
    #print(stringTwo)
    
    aa = ArrayAlgos()
    if not aa.isPermutation(stringOne, stringTwo, False, True):
        print("Something wrong")
    else:
        print("Working here")
    
    
    stringOne = stringOne.replace(" ", "")
    stringTwo = stringTwo.replace(" ", "")
    print(stringOne)
    print(stringTwo)
    
    charArr = [0] * 123
    for idx in stringOne:
        charArr[ord(idx)] += 1
    print(charArr)
    
    print("")
    
    for idx in stringTwo:
        charArr[ord(idx)] -= 1
    print(charArr)
    
    dataset = [ "radara", "wlevel", "edeified", "nmadam", "aacecar", "pmnoon", "mcivic", "mrotor", "trefer" ]
    for string in dataset:
        permutation_list = [''.join(perm) for perm in permutations(string)]
        for permString in permutation_list:
            assert not aa.isPalindromePermutation(permString)
    
if __name__ == "__main__":
    main()
    