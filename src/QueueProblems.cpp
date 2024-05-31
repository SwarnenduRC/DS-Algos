/**
 * @file QueueProblems.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "QueueProblems.hpp"

void MyQueue::push(const int val) noexcept
{
    m_primary.push(val);
    if (m_secondary.empty())
        transfer();
}

int MyQueue::pop() noexcept
{
    if (empty())
        return INT_MAX;
    
    if (m_secondary.empty())    // Get the data from the primary stack if the secondary is empty
        transfer();

    if (m_secondary.empty())    // No data in the primary stack either
        return INT_MAX;

    auto retVal = m_secondary.top();
    m_secondary.pop();
    return retVal;
}

void MyQueue::transfer() noexcept
{
    if (m_primary.empty())
        return;

    while (!m_primary.empty())
    {
        m_secondary.push(m_primary.top());
        m_primary.pop();
    }
}
