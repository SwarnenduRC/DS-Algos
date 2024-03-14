#include "ArraysAndStringProblems.hpp"


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