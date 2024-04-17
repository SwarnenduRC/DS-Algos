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