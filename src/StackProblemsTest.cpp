#include "StackProblemsTest.hpp"

TEST_F(StackProblemsTest, testStackOfPlates)
{
    size_t maxStackThresholdSize = 5;
    StackProblems stacks(maxStackThresholdSize);

    for (auto idx = 1; idx <= 25; ++idx)
        stacks.push(idx);

    size_t expStacks = 5;
    EXPECT_EQ(expStacks, stacks.getStacksCount());

    auto popVal = stacks.pop();
    EXPECT_EQ(25, popVal);

    for (auto idx = 0; idx < 4; idx++)
        popVal = stacks.pop();

    EXPECT_EQ(21, popVal);
    EXPECT_EQ(expStacks - 1, stacks.getStacksCount());
}

TEST_F(StackProblemsTest, testStackOfPlatesPopAt)
{
    size_t maxStackThresholdSize = 5;
    StackProblems stacks(maxStackThresholdSize);

    for (auto idx = 1; idx <= 25; ++idx)
        stacks.push(idx);

    size_t expStacks = 5;
    EXPECT_EQ(expStacks, stacks.getStacksCount());

    auto index = 6;
    EXPECT_THROW(stacks.popAt(index), std::runtime_error);

    index = 2;
    auto popVal = stacks.popAt(index);
    EXPECT_EQ(20, popVal);

    index = 3;
    popVal = stacks.popAt(index);
    EXPECT_EQ(15, popVal);
}

