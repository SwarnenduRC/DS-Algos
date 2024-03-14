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
};

#endif //_AARAYS_AND_STRING_PROBLEMS_H_
