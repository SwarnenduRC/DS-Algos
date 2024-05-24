/**
 * @file StackProblems.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _STACK_PROBLEMS_HPP_
#define _STACK_PROBLEMS_HPP_

#include <stack>
#include <list>

using StackList = std::list<std::stack<int>>;

class StackProblems
{
    public:
        /**
         * @brief Imagine a (literal) stack of plates. If the stack gets too high, it might topple. 
         * Therefore, in real life, we would likely start a new stack when the previous stack exceeds 
         * some threshold. Implement a data structure SetOfStacks that mimics this. SetOfStacks should 
         * be composed of several stacks and should create a new stack once the previous one exceeds 
         * capacity. SetOfStacks.push() and SetOfStacks.pop() should behave identically to a single 
         * stack (that is, pop() should return the same values as it would if there were just a single stack).
         * 
         * FOLLOW UP
         * Implement a function popAt(int index) which performs a pop operation on a specific sub-stack.
         */
        StackProblems() = default;
        StackProblems(const StackProblems& rhs) = default;
        StackProblems& operator=(const StackProblems& rhs) = default;
        StackProblems(StackProblems&& rhs) = default;
        StackProblems& operator=(StackProblems&& rhs) = default;
        ~StackProblems() = default;

        StackProblems(const size_t maxSize) : m_stackSets(maxSize) {}
        void push(const int val) noexcept;
        int pop() noexcept;
        int popAt(const int idx);

        size_t getPlatesCount() const noexcept;
        size_t getStacksCount() const noexcept;

    private:
        class SetOfStacks
        {
            public:
                SetOfStacks() = default;
                SetOfStacks(const SetOfStacks& rhs) = default;
                SetOfStacks& operator=(const SetOfStacks& rhs) = default;
                SetOfStacks(SetOfStacks&& rhs) = default;
                SetOfStacks& operator=(SetOfStacks&& rhs) = default;
                ~SetOfStacks() = default;

                SetOfStacks(const size_t maxSize) : m_stackMaxSize(maxSize) {}

                void push(const int val) noexcept;
                int pop() noexcept;
                int popAt(const int idx);
                size_t getPlatesCount() const noexcept;
                size_t getStacksCount() const noexcept;

            private:
                StackList m_stackList = {};
                size_t m_stackMaxSize = 5;
        };
        SetOfStacks m_stackSets;
};



#endif  // _STACK_PROBLEMS_HPP_