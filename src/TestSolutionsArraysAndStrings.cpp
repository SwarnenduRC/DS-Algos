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

TEST_F(AlgoProblems, testOneAway)
{
    {
        std::vector<std::pair<std::string, std::string>> dataSet;        
        // Examples of strings that are one insert away from each other to be equal
        dataSet.push_back({"algorithm", "lgorithm"});                // Insert 'a' at the beginning of the second string
        dataSet.push_back({"programming", "programing"});            // Insert 'm' in the middle of the second string
        dataSet.push_back({"integration", "integratio"});            // Insert 'n' at the end of the second string
        dataSet.push_back({"examination", "exmination"});            // Insert 'a' in the middle of the second string
        dataSet.push_back({"concentration", "concentrtion"});        // Insert 'a' in the middle of the second string
        dataSet.push_back({"university", "universty"});              // Insert 'i' in the middle of the second string
        dataSet.push_back({"extrapolation", "extrapolatin"});        // Insert 'o' at the end of the second string
        dataSet.push_back({"development", "developent"});            // Insert 'm' in the middle of the second string
        dataSet.push_back({"acceleration", "aceleration"});          // Insert 'c' in the middle of the second string
        dataSet.push_back({"difficulties", "dificulties"});          // Insert 'f' in the middle of the second string

        for (const auto& data : dataSet)
            EXPECT_TRUE(oneAway(data.first, data.second));

        for (const auto& data : dataSet)
            EXPECT_TRUE(oneAway(data.second, data.first));
    }
    {
        std::vector<std::pair<std::string, std::string>> dataSet;        
        // Examples of strings that are one insert away from each other to be equal but actually not
        dataSet.push_back({"algorithm", "lgorishm"});
        dataSet.push_back({"programming", "programimg"});
        dataSet.push_back({"integration", "integrateo"});
        dataSet.push_back({"examination", "exmimation"});
        dataSet.push_back({"concentration", "concentrsion"});
        dataSet.push_back({"university", "univercty"});
        dataSet.push_back({"extrapolation", "extrapolatim"});
        dataSet.push_back({"development", "developemt"});
        dataSet.push_back({"acceleration", "aseleration"});
        dataSet.push_back({"difficulties", "dipiculties"});

        for (const auto& data : dataSet)
            EXPECT_FALSE(oneAway(data.first, data.second));

        for (const auto& data : dataSet)
            EXPECT_FALSE(oneAway(data.second, data.first));
    }
    {
        std::vector<std::pair<std::string, std::string>> dataSet;        
        // Examples of strings that are one edit away from each other to be equal
        dataSet.push_back({"algorithm", "algorishm"});
        dataSet.push_back({"programming", "programmimg"});
        dataSet.push_back({"integration", "integratiom"});
        dataSet.push_back({"examination", "examimation"});
        dataSet.push_back({"concentration", "concentrasion"});
        dataSet.push_back({"university", "univercity"});
        dataSet.push_back({"extrapolation", "dxtrapolation"});
        dataSet.push_back({"development", "developmemt"});
        dataSet.push_back({"acceleration", "asceleration"});
        dataSet.push_back({"difficulties", "difficultigs"});

        for (const auto& data : dataSet)
            EXPECT_TRUE(oneAway(data.first, data.second));
    }
}

TEST_F(AlgoProblems, testCompressString)
{
    std::vector<std::pair<std::string, std::string>> dataSet = { {"aabcccccaaa", "a2b1c5a3"}
                                                                ,{"aabcccccaaad", "a2b1c5a3d1"}
                                                                ,{"zzzzzzzzzzz", "z11"}
                                                                ,{"yzzzzzzzzzzz", "y1z11"} };

    for (const auto& item : dataSet)
    {
        auto retVal = compressString(item.first);
        EXPECT_EQ(retVal, item.second) << item.first;
    }
}

