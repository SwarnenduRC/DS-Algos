/**
 * @file ArraysAndStringProblems.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
        static bool isUnique(std::string theString, const bool caseSensitive = false, const bool additionalDataStructuresAllowed = true);

        /**
         * @brief Check Permutation: Given two strings, write a method to decide if one is a permutation of the other.
         */
        static bool checkPermutation(std::string stringOne,
                                    std::string stringTwo, 
                                    const bool ignoreWhitespace = false, 
                                    const bool ignoreCaseSensitivity = true);

        /**
         * @brief Palindrome Permutation: Given a string, write a function to check if it is a permutation of
         * a palindrome. A palindrome is a word or phrase that is the same forwards and backwards, A
         * permutation is a rearrangement of letters. The palindrome does not need to be limited to just
         * dictionary words. EXAMPLE Input: Tact Coa. Output: True (permutations: " tac o cat " " atc o cta" etc.)
         */
        static bool palindromePermutation(std::string theString);
        /**
         * @brief There are three types of edits that can be performed on strings: insert a character,
         * remove a character, or replace a character. Given two strings, write a function to check if they are
         * one edit (or zero edits) away.
         * EXAMPLE
         * pale, ple -> true
         * pales, pale -> true
         * pale, bale -> true
         * pale, bae -> false
         */
        static bool oneAway(std::string firstString, std::string secondString);
};

#endif //_AARAYS_AND_STRING_PROBLEMS_H_
