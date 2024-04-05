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
    
    def isPalindromePermutation(self, string: str) -> bool:
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
    
    def oneEditAway(self, firstString: str, secondString: str) -> bool:
        if len(firstString) == 0 or len(secondString) == 0:
            return False
        
        if len(firstString) == len(secondString) + 1 or len(firstString) + 1 == len(secondString):
            idxFirst = 0
            idxSecond = 0
            diffFound = False
            while idxFirst < len(firstString) and idxSecond < len(secondString):
                if firstString[idxFirst] != secondString[idxSecond]:
                    if diffFound:
                        return False
                    diffFound = True
                    if len(firstString) < len(secondString):
                        idxSecond += 1
                    elif len(firstString) > len(secondString):
                        idxFirst += 1
                    continue
                                
                idxFirst += 1
                idxSecond += 1
                
            return True  ## Don't need to check the status of diffFound as the last character of one of the string is what extra if it reaches here
        
        if len(firstString) == len(secondString):
            diffFound = False
            idxFirst = 0
            idxSecond = 0
            while idxFirst < len(firstString) and idxSecond < len(secondString):
                if firstString[idxFirst] != secondString[idxSecond]:
                    if diffFound:
                        return False
                    diffFound = True
                idxFirst += 1
                idxSecond += 1
            if diffFound:
                return True
            return False
        
    def compressString(self, string: str) -> str:
        if len(string) == 0:
            return str()
        
        if len(string) < 2:
            return string
        
        current = string[0]
        startPos = 1
        repCnt = 1
        appendString = []
        for idx in range(startPos, len(string)):
            next = string[idx]
            if current == next:
                repCnt += 1
            else:
                appendString.append(current)
                appendString.append(str(repCnt))
                repCnt = 1
                
            current = next
            
        appendString.append(current)
        appendString.append(str(repCnt))
        return ''.join(appendString)
    
    def isRotation(self, S1: str, S2: str) -> bool:
        if len(S1) == 0 or len(S2) == 0:
            return False
        if len(S1) != len(S2):
            return False
        
        S1S1 = S1 + S1
        return S1S1.find(S2) != -1
    
    def setZero(self, matrix):
        if len(matrix) == 0:
            return

        rowWithZeros = [False] * len(matrix)
        colWithZeros = [False] * len(matrix[0])

        for row in range(len(matrix)):
            for col in range(len(matrix[row])):
                if matrix[row][col] == 0:
                    rowWithZeros[row] = True
                    colWithZeros[col] = True

        for row in range(len(rowWithZeros)):
            if rowWithZeros[row]:
                for col in range(len(matrix[0])):
                    matrix[row][col] = 0

        for col in range(len(colWithZeros)):
            if colWithZeros[col]:
                for row in range(len(matrix)):
                    matrix[row][col] = 0

def main():    
    aa = ArrayAlgos()
            
    dataSetPositive = [("algorithm", "lgorithm"), 
                       ("programming", "programing"),
                       ("integration", "integratio"),
                       ("examination", "exmination"),
                       ("concentration", "concentrtion"),
                       ("university", "universty"),
                       ("extrapolation", "extrapolatin"),
                       ("development", "developent"),
                       ("acceleration", "aceleration"),
                       ("difficulties", "dificulties")]
    
    for firstString, secondString in dataSetPositive:
        assert aa.oneEditAway(firstString, secondString)
    
if __name__ == "__main__":
    main()
    