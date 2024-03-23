/**
 * @file TestSolutionsArraysAndStrings.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-03-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "ArraysAndStringProblems.hpp"

TEST_F(AlgoProblems, testIsUnique)
{
    std::string data = "abc%$7Gg";
    EXPECT_TRUE(isUnique(data));
    EXPECT_TRUE(isUnique(data, false, false));
    EXPECT_FALSE(isUnique(data, true));
    EXPECT_FALSE(isUnique(data, true, false));
}

TEST_F(AlgoProblems, testPermutation)
{
    {
        std::string data1 = "abc%$7Gg";
        std::string data2 = "%bacG7g$";
        EXPECT_TRUE(checkPermutation(data1, data2));
    }
    /**
     * @brief This one is inserting tabs at the beginning
     * and end for the two data respectively which ultimately
     * inserts 4 spaces for each tab
     */
    {
        std::string data1 = "abc%$7Gg   ";
        std::string data2 = "   %bacG7g$";
        EXPECT_TRUE(checkPermutation(data1, data2));
    }
    /**
     * @brief This one is inserting tabs at the end
     * for the first data and 4 spaces (which is equivalent
     * to 1 tab) at the beginning for the second data 
     * respectively.
     */
    {
        std::string data1 = "abc%$7Gg   ";
        std::string data2 = "   %bacG7g$";
        EXPECT_TRUE(checkPermutation(data1, data2));
    }
    {
        std::string data1 = "abc%$7Gg   ";
        std::string data2 = "%bacG7g$";
        EXPECT_FALSE(checkPermutation(data1, data2));
        EXPECT_TRUE(checkPermutation(data1, data2, true));
    }
    {
        std::string data1 = "abc%$7Gg   ";
        std::string data2 = "%bgac7g$";
        EXPECT_FALSE(checkPermutation(data1, data2));
        EXPECT_TRUE(checkPermutation(data1, data2, true));
        EXPECT_FALSE(checkPermutation(data1, data2, true, false));
    }
}

TEST_F(AlgoProblems, testPalindromePermutation)
{
    {
        std::vector<std::string> palindromes = { "radar", "level", "deified", "madam", "racecar", "noon", "civic", "rotor", "refer", "redder" };
        std::vector<std::string> palindormesPermutations;        
        for (auto item : palindromes)
        {
            std::sort(item.begin(), item.end());
            do
            {
                palindormesPermutations.emplace_back(item);
            } while (std::next_permutation(item.begin(), item.end()));            
        }
        for (const auto& item : palindormesPermutations)
            EXPECT_TRUE(palindromePermutation(item));
    }
    {
        std::vector<std::string> palindromes = { "radara", "wlevel", "edeified", "nmadam", "aacecar", "pmnoon", "mcivic", "mrotor", "trefer" };
        std::vector<std::string> palindormesPermutations;        
        for (auto item : palindromes)
        {
            std::sort(item.begin(), item.end());
            do
            {
                palindormesPermutations.emplace_back(item);
            } while (std::next_permutation(item.begin(), item.end()));            
        }
        for (const auto& item : palindormesPermutations)
            EXPECT_FALSE(palindromePermutation(item)) << "string = " << item;
    }
    // Commented as it takes super long to generate all the permutations
    /* {
        std::vector<std::string> palindromes = 
            { "a man a plan a canal panama"
                , "was it a car or a cat i saw"
                , "evil is a name of a foeman as i live"
                , "never odd or even"
                , "able was i saw elba"
                , "do geese see god"
                , "mr owl ate my metal worm"
                , "a Santa lived as a devil at NASA"
                , "step on no pets"
            };
        std::vector<std::string> palindormesPermutations;        
        for (auto item : palindromes)
        {
            std::sort(item.begin(), item.end());
            do
            {
                palindormesPermutations.emplace_back(item);
            } while (std::next_permutation(item.begin(), item.end()));            
        }
        for (const auto& item : palindormesPermutations)
            EXPECT_TRUE(palindromePermutation(item));
    } */
}

