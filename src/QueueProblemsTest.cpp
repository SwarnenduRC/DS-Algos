#include "QueueProblemsTest.hpp"

TEST_F(QueueProblemsTest, testMyQueueClass)
{
    for (auto val = 1; val <= 10; val++)
        m_queue.push(val);

    for (auto val = 1; val <= 10; val++)
        EXPECT_EQ(val, m_queue.pop());

    EXPECT_TRUE(m_queue.empty());
}