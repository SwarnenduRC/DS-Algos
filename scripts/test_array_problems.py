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
            
def test_oneEditAway():
    classObj = AA()
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
        assert classObj.oneEditAway(firstString, secondString)
        
    for firstString, secondString in dataSetPositive:
        assert classObj.oneEditAway(secondString, firstString)
        
    dataSetNegative = [("algorithm", "lgorishm"), 
                       ("programming", "programimg"),
                       ("integration", "integrateo"),
                       ("examination", "exmimation"),
                       ("concentration", "concentrsion"),
                       ("university", "univercty"),
                       ("extrapolation", "extrapolatim"),
                       ("development", "developemt"),
                       ("acceleration", "aseleration"),
                       ("difficulties", "dipiculties")]
    
    for firstString, secondString in dataSetNegative:
        assert not classObj.oneEditAway(firstString, secondString)
        
    for firstString, secondString in dataSetNegative:
        assert not classObj.oneEditAway(secondString, firstString)
        
    dataSetPositive = [("algorithm", "algorishm"), 
                       ("programming", "programmimg"),
                       ("integration", "integratiom"),
                       ("examination", "examimation"),
                       ("concentration", "concentrasion"),
                       ("university", "univercity"),
                       ("extrapolation", "dxtrapolation"),
                       ("development", "developmemt"),
                       ("acceleration", "asceleration"),
                       ("difficulties", "difficultigs")]
    
    for firstString, secondString in dataSetPositive:
        assert classObj.oneEditAway(firstString, secondString)
        
def test_stringCompress():
    clsObj = AA()
    dataset = [("aabcccccaaa", "a2b1c5a3"),
               ("aabcccccaaad", "a2b1c5a3d1"),
               ("zzzzzzzzzzz", "z11"),
               ("yzzzzzzzzzzz", "y1z11")]
    
    for string, expString in dataset:
        assert clsObj.compressString(string) == expString
        
def test_isRotation():
    clsObj = AA()
    dataset = [("waterbottle", "erbottlewat"),
               ("programming", "grammingpro"),
               ("openai", "aiopen"),
               ("stackoverflow", "overflowstack")]
    
    for S1, S2 in dataset:
        assert clsObj.isRotation(S1, S2)
        
    S1 = "waterbottle"
    S2 = "ear"
    assert not clsObj.isRotation(S1, S2)
    
    S2 = "er"
    assert not clsObj.isRotation(S1, S2)
    