from array_problems import ArrayAlgos as AA

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