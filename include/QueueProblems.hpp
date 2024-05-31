/**
 * @file QueueProblems.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-24
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _QUEUE_PROBLEMS_H_
#define _QUEUE_PROBLEMS_H_

#include <stack>

/**
 * @brief Queue via Stacks
 *        Implement a MyQueue class which implements a queue using two stacks.
 */

using Stack = std::stack<int>;

class MyQueue
{
    public:
        void push(const int val) noexcept;
        int pop() noexcept;
        inline size_t size() const noexcept { return m_primary.size() + m_secondary.size(); }
        inline bool empty() const noexcept { return m_primary.empty() && m_secondary.empty(); }
    
    private:
        void transfer() noexcept;

        Stack m_primary;
        Stack m_secondary;
};

#endif  //_QUEUE_PROBLEMS_H_