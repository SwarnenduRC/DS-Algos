/**
 * @file ArraysAndStringProblems.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "ArraysAndStringProblems.hpp"

#include <regex>
#include <algorithm>

bool AlgoProblems::isUnique(std::string theString, const bool caseSensitive, const bool additionalDataStructuresAllowed)
{
    /**
     * @brief The solution assumes that the string is made of ASCII characters, i.e.;
     * there can be of max 128 unique characters in the string. If it would have been
     * an extended ASCII string then the max unique characters can be 256. In case of
     * unicode then either UTF-8 or UTF-16 or UTF-32.
     */

    // Return FALSE straingt away if the string size is more than 128  or empty
    if (theString.size() > 128 || theString.empty())
        return false;

    // Now check if additional space can be used, if so, then...
    if (additionalDataStructuresAllowed)
    {
        // Solution 1 : Use a vector
        auto sol1 = [caseSensitive](const std::string& string)
        {
            std::vector<bool> charTracker;
            charTracker.resize(128);
            std::fill(charTracker.begin(), charTracker.end(), false);
            int ASCII_val = INT_MIN;
            auto stringCopy = string;
            for (auto& strChar : stringCopy)
            {
                if (caseSensitive)
                    strChar = static_cast<char>(std::toupper(strChar));

                ASCII_val = strChar;                
                if (charTracker[ASCII_val])
                    return false;

                charTracker[ASCII_val] = true;
            }
            return true;
        };
        return sol1(theString);
    }
    // Else...
    else
    {
        auto stringCopy = theString;
        if (caseSensitive)
        {
            for (auto& strChar : stringCopy)
                strChar = std::toupper(strChar);
        }        
        /**
         * @brief Logic is quite simple. Sort the string.
         * If it has repeatitive characters then after
         * sorting they will be sitting next to each other
         * and comparing the two subsequet chars one at a
         * step will catch them (if any)
         */
        std::sort(stringCopy.begin(), stringCopy.end());
        for (size_t startIdx = 0; startIdx <= stringCopy.size() - 2; ++startIdx)
        {
            if (stringCopy[startIdx] == stringCopy[startIdx + 1])
                return false;
        }
        return true;
    }
}

bool AlgoProblems::checkPermutation(std::string stringOne, 
                                    std::string stringTwo, 
                                    const bool ignoreWhitespace, 
                                    const bool ignoreCaseSensitivity)
{
    /**
     * @brief First check, if they are not of same size then
     * they can't be permutation of each other. Second check;
     * if either of them empty then also return FALSE. Third
     * P.S. It is assumed that the string contains only ASCII
     * characters.
     */
    if (stringOne.empty() || stringTwo.empty())
        return false;

    // If the strings to be compared irrespective of their case sensitivity
    // then convert both of them to either lowercase or uppercase
    if (ignoreCaseSensitivity)
    {
        for (auto& charItm : stringOne)
            charItm = std::tolower(charItm);

        for (auto& charItm : stringTwo)
            charItm = std::tolower(charItm);
    }
    // If whitespaces in the strings are to be ignored then remove the whitespaces from both the strings
    if (ignoreWhitespace)
    {
        std::regex whiteSpace("\\s");
        stringOne = std::regex_replace(stringOne, whiteSpace, "");
        stringTwo = std::regex_replace(stringTwo, whiteSpace, "");
    }
    /**
     * @brief First solution implies the logic that
     * if the strings are permutation of each other
     * then if we sort both of them and then compare
     * the sorted strings then if they are not equal
     * then they are not. Takes approx O(n log N) +
     * O(n log N) + O(n) => O(3n + 2log N) => O(n log N)
     */
    auto solution = [](std::string stringOne, std::string stringTwo)
    {
        std::sort(stringOne.begin(), stringOne.end());
        std::sort(stringTwo.begin(), stringTwo.end());
        return stringOne == stringTwo;
    };
    /**
     * @brief Second solution implies that the count of each
     * characters in both the string should be same.
     */
    auto solutionOpt = [stringOne, stringTwo]()
    {
        std::array<int, 128> charCnts;
        std::fill(charCnts.begin(), charCnts.end(), 0);

        for (const auto& chaar : stringOne)
            charCnts[chaar]++;

        for (const auto& chaar : stringTwo)
        {
            charCnts[chaar]--;
            if (charCnts[chaar] < 0)
                return false;
        }
        return true;
    };
    return solution(stringOne, stringTwo) && solutionOpt();
}

bool AlgoProblems::palindromePermutation(std::string theString)
{
    if (theString.empty())
        return false;

    /**
     * What does it take to be able to write a set of characters the same way forwards and backwards? We need to
     * have an even number of almost all characters, so that half can be on one side and half can be on the other
     * side. At most one character (the middle character) can have an odd count.
     * 
     * To be more precise, strings with even length (after removing ail non-letter characters) must have
     * all even counts of characters. Strings of an odd length must have exactly one character with
     * an odd count. Of course, an "even" string can't have an odd number of exactly one character,
     * otherwise it wouldn't be an even-length string (an odd number + many even numbers = an odd
     * number). Likewise, a string with odd length can't have all characters with even counts (sum of
     * evens is even). It's therefore sufficient to say that, to be a permutation of a palindrome, a string
     * can have no more than one character that is odd. This will cover both the odd and the even cases.
     */
    // First of all remove any whitespcaes for simplicity of operations
    std::regex ws("\\s");
    theString = std::regex_replace(theString, ws, "");

    // Convert all the letters either in upper case or lower case for more simplicity
    for (auto& letter : theString)
        letter = std::tolower(letter);

    /**
     * @brief So the first solution is to make a hash table of characters
     * avilable in the string with each of their count and find if there is
     * any characater having an odd count more than once. O(N) time
     */
    auto firstSolution = [theString]()
    {
        std::unordered_map<char, int> charMap;
        for (const auto& charecter : theString)
        {
            auto itr = charMap.find(charecter);
            if (itr != charMap.end())
                itr->second++;
            else
                charMap[charecter] = 1;
        }
        auto oddCnt = 0;
        for (const auto& itr : charMap)
        {
            if (itr.second % 2 > 0)
                oddCnt++;
        }
        return oddCnt <= 1;
    };
    /**
     * @brief Second solution is also of O(N) but slight optimization
     * over the first. First solution was actually of O(2N) here it
     * would be only O(N). P.S. Not counting the sorting and converting
     * to upper/lower case as those are common to all        
     */
    auto secondSolution = [theString]()
    {
        std::unordered_map<char, int> charMap;
        auto oddCnt = 0;
        for (const auto& charecter : theString)
        {
            auto itr = charMap.find(charecter);
            if (itr != charMap.end())
                itr->second++;
            else
                charMap[charecter] = 1;

            if (charMap[charecter] %2 > 0)
                ++oddCnt;
            else
                --oddCnt;
        }
        return oddCnt <= 1;
    };
    /**
     * @brief If you think more deeply about this problem, you might notice that we don't actually need to know the
     * counts. We just need to know if the count is even or odd. Think about flipping a light on/off (that is initially
     * off). If the light winds up in the off state, we don't know how many times we flipped it, but we do know it
     * was an even count,
     * Given this, we can use a single integer (as a bit vector). When we see a letter, we map it to an integer
     * between 0 and 26 (assuming an English alphabet). Then we toggle the bit at that value. At the end of the
     * iteration, we check that at most one bit in the integer is set to 1.
     * 
     * We can easily check that no bits in the integer are 1: just compare the integer to 0. There is actually a very
     * elegant way to check that an integer has exactly one bit set to 1.
     * 
     * Picture an integer like 00010000. We could of course shift the integer repeatedly to check that there's only
     * a single 1. Alternatively, if we subtract 1 from the number, we'll get 00001111. What's notable about this
     * is that there is no overlap between the numbers (as opposed to say 00101000, which, when we subtract 1
     * from, we get 00100111.) So, we can check to see that a number has exactly one 1 because if we subtract 1
     * from it and then AND it with the new number, we should get 0.
     * 
     * 00010000 - 1 = 00001111
     * 00010000 & 00001111 = 0
     */
    auto thirdSolution = [theString]()
    {
        std::bitset<26> alphabets;
        char smallA = 'a';
        for (const auto& alpha : theString)
        {
            auto idx = static_cast<int>(alpha - smallA);
            alphabets[idx].flip();
        }
        return !(alphabets.count() > 1);
    };
    //return firstSolution();
    //return secondSolution();
    //return thirdSolution();
    return firstSolution() && secondSolution() && thirdSolution();
}

bool AlgoProblems::oneAway(std::string firstString, std::string secondString)
{
    if (firstString.empty() || secondString.empty())
        return false;

    /**
     * @brief There is a "brute force" algorithm to do this. We could check all possible strings that are one edit away by
     * testing the removal of each character (and comparing), testing the replacement of each character (and
     * comparing), and then testing the insertion of each possible character (and comparing).
     * 
     * That would be too slow, so let's not bother with implementing it.
     * 
     * This is one of those problems where it's helpful to think about the "meaning" of each of these operations.
     * What does it mean for two strings to be one insertion, replacement, or removal away from each other?
     * 
     * Replacement: Consider two strings, such as bale and pale, that are one replacement away. Yes, that
     * does mean that you could replace a character in bale to make pale. But more precisely, it means that
     * they are different only in one place.
     * 
     * Insertion: The strings apple and aple are one insertion away. This means that if you compared the
     * strings, they would be identical-except for a shift at some point in the strings.
     * 
     * Removal: The strings apple and aple are also one removal away, since removal is just the inverse of
     * insertion.
     */

    auto oneInsertOrDeleteAway = [firstString, secondString]()
    {
        auto& longString = (firstString.size() > secondString.size()) ? firstString : secondString;
        auto& shortString = (firstString.size() < secondString.size()) ? firstString : secondString;
        auto diffCnt = 0;
        size_t idxSS = 0;
        size_t idxLS = 0;

        while (idxSS < shortString.size() && idxLS < longString.size())
        {
            if (shortString[idxSS] != longString[idxLS])
            {
                ++diffCnt;
                if (diffCnt > 1)
                    return false;

                ++idxLS;
                continue;
            }
            ++idxLS;
            ++idxSS;
        }
        return true; // Don't need to check the status of diffFound as the last character of one of the string is what extra if it reaches here
    };
    auto oneEditAway = [firstString, secondString]()
    {
        auto foundDiff = false;
        for (size_t idx = 0; idx < firstString.size(); ++idx)
        {
            if (firstString[idx] != secondString[idx])
            {
                if (foundDiff)
                    return false;
                foundDiff = true;
            }
        }
        if (foundDiff)
            return true;
        return false;
    };

    if ((firstString.size() == secondString.size() - 1) || (firstString.size() - 1 == secondString.size()))
        return oneInsertOrDeleteAway();
    else if (firstString.size() == secondString.size())
        return oneEditAway();
    return false;
}

std::string AlgoProblems::compressString(std::string theString)
{
    if (theString.empty())
        return std::string{};

    if (theString.size() < 2)
        return theString;

    /**
     * @brief The logic is actually quite straigtforward. We iterate through the string
     * and check if two consequtive characters are same or not. If they are same we increase
     * the repeat count, otherwise we set it back to 1 for the next character. We also move
     * the current matching character to the next one in anticipation to find a repeat for
     * the next sequence. We start iterating from the 2nd character of the string as first is
     * already been considered before the loop. Time complexity is O(N) approx by negelecting
     * the inbuilt function's ones
     */
    size_t repCnt = 1;
    std::string retVal;
    char current = theString[0];
    for (size_t idx = 1; idx < theString.size(); ++idx)
    {
        auto next = theString[idx];
        if (current == next)
        {
            repCnt++;
        }
        else
        {            
            retVal.append(std::string(1, current).append(std::to_string(repCnt)));
            repCnt = 1;
        }
        current = next;
    }
    auto builtString = std::string(1, current).append(std::to_string(repCnt));
    retVal.append(builtString);
    return retVal;
}

bool AlgoProblems::isRotation(std::string_view S1, std::string_view S2)
{
    /**
     * If we imagine that S2 is a rotation of S1, then we can ask what the rotation point is. For example, if you
     * rotate waterbottle after wat, you get erbottlewat. In a rotation, we cut S1 into two parts, x and y,
     * and rearrange them to get S2.
     * 
     * S1 = xy = waterbottle
     * x = wat
     * y = erbottle
     * S2 = yx = erbottlewat
     * 
     * So, we need to check if there's a way to split s1 into x and y such that xy = s1 and yx = s2. Regardless of
     * where the division between x and y is, we can see that yx will always be a substring of xyxy.That is, s2 will
     * always be a substring of s1s1.
     * 
     * And this is precisely how we solve the problem: simply do isSubstring(slsl, s2).
     */
    auto isSubString = [](std::string_view S1S1, std::string_view S2)
    {
        if (S1S1.empty())
            return false;
        else
            return S1S1.find(S2) != std::string_view::npos;
    };
    if (S1.empty() || S2.empty())
        return false;

    if (S1.size() != S2.size())
        return false;

    std::string S1S1 = S1.data();
    S1S1 += S1;
    return isSubString(S1S1, S2);
}

void AlgoProblems::setZeros(std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty())
        return;

    using Matrix = std::vector<std::vector<int>>;

    auto nullifyRow = [](Matrix& matrix, size_t row)
    {
        for (size_t col = 0; col < matrix[row].size(); ++col)
            matrix[row][col] = 0;
    };
    auto nullifyColumn = [](Matrix& matrix, size_t col)
    {
        for (size_t row = 0; row < matrix.size(); ++row)
            matrix[row][col] = 0;
    };
    /**
     * @brief It takes O(MxN) time as each of the elements
     * in the matrix needs to be checked at least once.
     * But it also takes O(M+N) space as we are keeping
     * tow arrays for rows and columns.
     */
    auto solution = [&nullifyRow, &nullifyColumn](Matrix& matrix)
    {
        // Take two arrays which will hold the rwo and column
        // indexes respectively which has a value zero
        std::vector<bool> rowsWithZero(matrix.size(), false);
        std::vector<bool> columnsWithZero(matrix[0].size(), false);
        // Iterate through the matrix and identify the row and col
        // indexes with zeros
        for (size_t row = 0; row < matrix.size(); ++row)
        {
            for (size_t col = 0; col < matrix[row].size(); ++col)
            {
                if (matrix[row][col] == 0)
                {
                    rowsWithZero[row] = true;
                    columnsWithZero[col] = true;
                }
            }
        }
        // Now check which rows have zeros in the row array and make
        // the columns for that row to zero
        for (size_t row = 0; row < rowsWithZero.size(); ++row)
        {
            if (rowsWithZero[row])
                nullifyRow(matrix, row);
        }
        // Now check which columns have zeros in the row array and make
        // the rows for that column to zero
        for (size_t col = 0; col < columnsWithZero.size(); ++col)
        {
            if (columnsWithZero[col])
                nullifyColumn(matrix, col);
        }
        return matrix;
    };
    solution(matrix);
}
