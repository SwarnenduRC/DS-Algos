#include "RecursionAndDynamicProgramming.hpp"

size_t RADP::findFibonacciBruteForce(size_t number) noexcept
{
    if (number == 0)
        return 0;

    if (number == 1)
        return 1;
    
    return findFibonacciBruteForce(number - 1) + findFibonacciBruteForce(number - 2);
}

size_t RADP::findFibonacciDP1(size_t number) noexcept
{
    if (number == 0)
        return 0;

    if (number == 1)
        return 1;
    
    static std::vector<size_t> memoTable(number, 0);
    if (memoTable[number] == 0)
        memoTable[number] = findFibonacciDP1(number - 2) + findFibonacciDP1(number - 1);

    return memoTable[number];
}

size_t RADP::findFibonacciDP2(size_t number) noexcept
{
    if (number == 0)
        return 0;

    size_t a = 0;
    size_t b = 1;
    /**
     * This is basically storing the results from the last two Fibonacci values into a and b. At each iteration, we
     * compute the next value ( c = a + b) and then move ( b, c = a + b) into (a, b).
     */
    for (size_t itr = 2; itr < number; ++itr)
    {
        auto c = a + b;
        a = b;
        b = c;
    }
    return a + b;
}
