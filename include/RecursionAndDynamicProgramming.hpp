/**
 * @file RecursionAndDynamicProgramming.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-05-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _RECURSION_AND_DYNAMIC_PROGRAMMING_HPP_
#define _RECURSION_AND_DYNAMIC_PROGRAMMING_HPP_

#include <gtest/gtest.h>

class RADP : public ::testing::Test
{
    public:
        /**
         * @brief Fibonacci Numbers
         * Find the the Fibonacci number for an unsigned integer n
         */
        static size_t findFibonacciBruteForce(size_t number) noexcept;
        static size_t findFibonacciDP1(size_t number) noexcept;
        static size_t findFibonacciDP2(size_t number) noexcept;
};

#endif //_RECURSION_AND_DYNAMIC_PROGRAMMING_HPP_