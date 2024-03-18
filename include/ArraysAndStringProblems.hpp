#ifndef _AARAYS_AND_STRING_PROBLEMS_H_
#define _AARAYS_AND_STRING_PROBLEMS_H_

#include <gtest/gtest.h>

class AlgoProblems : public ::testing::Test
{
    public:
        /**
         * @brief Is Unique: Implement an algorithm to determine if a string has all unique characters. What if you
         *        cannot use additional data structures? 
         */
        bool isUnique(std::string theString, const bool caseSensitive = false, const bool additionalDataStructuresAllowed = true);

        /**
         * @brief Check Permutation: Given two strings, write a method to decide if one is a permutation of the other.
         */
        bool checkPermutation(std::string stringOne, 
                                    std::string stringTwo, 
                                    const bool ignoreWhitespace = false, 
                                    const bool ignoreCaseSensitivity = true);
};

#endif //_AARAYS_AND_STRING_PROBLEMS_H_
