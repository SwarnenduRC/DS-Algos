#include "ArraysAndStringProblems.hpp"

TEST_F(AlgoProblems, testIsUnique)
{
    std::string data = "abc%$7Gg";
    EXPECT_TRUE(isUnique(data));
    EXPECT_TRUE(isUnique(data, false, false));
    EXPECT_FALSE(isUnique(data, true));
    EXPECT_FALSE(isUnique(data, true, false));
}