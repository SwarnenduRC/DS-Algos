/**
 * @file LinkListProblems.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "LinkListProblems.hpp"

#include <unordered_set>

SinglyLinkedList LinkListAlgos::removeDuplicate(const SinglyLinkedList& list)
{
    if (list.empty())
        return SinglyLinkedList{};

    /**
     * @brief The first solution uses a hash table
     * to keep track of values and whenever we find
     * any duplicate we just remove that node. Space
     * and time complexity both will be O(N)
     */
    auto firstSolution = [](const SinglyLinkedList& list)
    {
        auto listCopy = list;
        auto pHead = listCopy.getHead();
        std::unordered_set<int> hashTable;
        hashTable.insert(pHead->m_element);
        while (pHead && pHead->m_pNext)
        {
            if (hashTable.find(pHead->m_pNext->m_element) == hashTable.end())
            {
                hashTable.insert(pHead->m_pNext->m_element);
            }
            else
            {
                auto pDup = pHead->m_pNext;
                pHead->m_pNext = pDup->m_pNext;
                pDup->m_pNext = nullptr;
                delete pDup;
                listCopy.decrementSize();
            }
            pHead = pHead->m_pNext;
        }
        return listCopy;
    };
    /**
     * @brief The second solution delas with the brute force approach
     * where any temporary buffer is not allowed. Space complexity for
     * this brute force approach is O(N) but the time complexity is O(N^2)
     */
    /* auto secondSolution = [](const SinglyLinkedList& list)
    {
        auto listCopy = list;
        auto pHead = listCopy.getHead();
        while (pHead)
        {
            auto pNext = pHead->m_pNext;
            auto pCurrent = pHead;
            while (pNext)
            {
                if (pHead->m_element == pNext->m_element)
                {
                    auto pDel = pNext;
                    pCurrent->m_pNext = pDel->m_pNext;
                    pDel->m_pNext = nullptr;
                    delete pDel;
                    listCopy.decrementSize();
                }
                pCurrent = pNext;
                pNext = pNext->m_pNext;
            }
            pHead = pHead->m_pNext;
        }
        return listCopy;
    }; */
    return firstSolution(list);
    //return secondSolution(list);
}

void* LinkListAlgos::returnKthToLast(const SinglyLinkedList& list, const size_t k)
{
    if (list.empty())
        return nullptr;

    auto pHead = list.getHead();
    auto pRunner = list.getHead();

    /**
     * The logic is quite simple. We take two pointers.
     * Initially both are pointing to the head of the list.
     * Then at first step we move the second/runner pointer
     * by the count of K. On second step, we move both the
     * pointers at same space till the runner hits the last
     * node. For example, if k=5 i.e.; we need to return the
     * 5th last node (k=0 returns the last node), we move the
     * runner 5th position in advance before we start moving
     * both the pointer at same space. Time complexity is O(N)
     * and space complexity is O(1)
     */
    for (size_t cnt = 0; cnt < k; ++cnt)
        pRunner = pRunner->m_pNext;

    while (pRunner->m_pNext)
    {
        pHead = pHead->m_pNext;
        pRunner = pRunner->m_pNext;
    }
    return static_cast<void*>(pHead);
}

