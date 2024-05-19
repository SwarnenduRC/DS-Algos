/**
 * @file StackProblems.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-14
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "StackProblems.hpp"

void StackProblems::SetOfStacks::push(const int val) noexcept
{
    auto makeNewStackAndPush = [this](const int val)
    {
        std::stack<int> stack;
        stack.push(val);
        m_stackList.emplace_front(stack);
    };
    if (m_stackList.empty())
    {
        makeNewStackAndPush(val);
    }
    else
    {
        auto& stack = m_stackList.front();
        if (stack.size() == m_stackMaxSize)
            makeNewStackAndPush(val);
        else
            stack.push(val);
    }
}

void StackProblems::push(const int val) noexcept
{
    m_stackSets.push(val);
}

int StackProblems::SetOfStacks::pop() noexcept
{
    if (m_stackList.empty())
        return INT_MAX;

    auto itr = m_stackList.begin();
    auto retVal = itr->top();
    itr->pop();
    if (itr->empty())
        m_stackList.pop_front();
    
    return retVal;
}

int StackProblems::pop() noexcept
{
    return m_stackSets.pop();
}

size_t StackProblems::SetOfStacks::getPlatesCount() const noexcept
{
    if (m_stackList.empty())
        return 0;
    
    size_t retVal = 0;
    for (const auto& stack : m_stackList)
        retVal += stack.size();

    return retVal;
}

size_t StackProblems::getPlatesCount() const noexcept
{
    return m_stackSets.getPlatesCount();
}

size_t StackProblems::SetOfStacks::getStacksCount() const noexcept
{
    return m_stackList.size();
}

size_t StackProblems::getStacksCount() const noexcept
{
    return m_stackSets.getStacksCount();
}

int StackProblems::SetOfStacks::popAt(const int index)
{
    if (m_stackList.empty() || m_stackList.size() < static_cast<size_t>(index))
        throw std::runtime_error("Not enough stacks available");

    auto itr = m_stackList.begin();
    auto cnt = 1;
    while (itr != m_stackList.end())
    {
        if (index == cnt)
        {
            auto retVal = itr->top();
            itr->pop();
            if (itr->empty())
                m_stackList.remove(*itr);
            return retVal;
        }
        ++cnt;
        ++itr;
    }
    return INT_MAX;
}

int StackProblems::popAt(const int index)
{
    return m_stackSets.popAt(index);
}

