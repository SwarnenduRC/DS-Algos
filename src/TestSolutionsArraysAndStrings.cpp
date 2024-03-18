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

