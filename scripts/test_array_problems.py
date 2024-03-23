from array_problems import ArrayAlgos as AA
from itertools import permutations

def test_isUnique():
    string = "abcd1234"
    classObj = AA()
    assert classObj.isUnique(string)
    
    string = "abcd1234ABCD"
    assert classObj.isUnique(string, True)
    assert classObj.isUnique(string, True, False)
    
    string = "abcd1234ABCDa"
    assert not classObj.isUnique(string, True)
    assert not classObj.isUnique(string, True, False)
    
    string = "abcd1234ABCD2"
    assert not classObj.isUnique(string, True)
    assert not classObj.isUnique(string, True, False)
    
    string = "abcd1234A"
    assert classObj.isUnique(string, True) == True
    assert classObj.isUnique(string, True, False) == True
    assert not classObj.isUnique(string)
    assert not classObj.isUnique(string, False, False)
    
    string = "  abcd1234A "
    assert classObj.isUnique(string, True) == False
    assert classObj.isUnique(string, True, False) == False
    assert not classObj.isUnique(string)
    assert not classObj.isUnique(string, False, False)
    
    string = " abcd1234A"
    assert classObj.isUnique(string, True)
    assert classObj.isUnique(string, True, False)
    
def test_isPermutation():
    firstString = ""
    secondString = ""
    classObj = AA()
    assert classObj.isPermutation(firstString, secondString)
    
    secondString = "ab"
    assert not classObj.isPermutation(firstString, secondString)
    
    firstString = "ba "
    assert not classObj.isPermutation(firstString, secondString)
    assert classObj.isPermutation(firstString, secondString, False, True)
    
    firstString = "BA "
    assert not classObj.isPermutation(firstString, secondString)
    assert classObj.isPermutation(firstString, secondString, False, True)
    
    firstString = "BA "
    secondString = " ab"
    assert classObj.isPermutation(firstString, secondString)
    assert classObj.isPermutation(firstString, secondString, False)
    
def test_palindromePermutation1():
    dataset = [ "radar", "level", "deified", "madam", "racecar", "noon", "civic", "rotor", "refer", "redder" ]
    classObj = AA()
    for string in dataset:
        permutation_list = [''.join(perm) for perm in permutations(string)]
        for permString in permutation_list:
            assert classObj.isPalindromePermutation(permString)
            
    dataset = [ "radara", "wlevel", "edeified", "nmadam", "aacecar", "pmnoon", "mcivic", "mrotor", "trefer" ]
    for string in dataset:
        permutation_list = [''.join(perm) for perm in permutations(string)]
        for permString in permutation_list:
            assert not classObj.isPalindromePermutation(permString)
    