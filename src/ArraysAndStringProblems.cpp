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