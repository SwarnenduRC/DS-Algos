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
#include <stack>
#include <queue>

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
        auto pCurr = listCopy.getHead();
        std::unordered_set<int> hashTable;
        while (pCurr)
        {
            if (hashTable.empty() || hashTable.find(pCurr->m_element) == hashTable.end())
            {
                hashTable.insert(pCurr->m_element);
            }
            else
            {
                auto pNext = pCurr->m_pNext;
                SinglyLinkedList::remove(listCopy, pCurr);
                pCurr = pNext;
                continue;
            }
            pCurr = pCurr->m_pNext;
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

bool LinkListAlgos::deleteMiddle(SinglyNode* pNode)
{
    if (pNode == nullptr)
        return false;

    if (pNode->m_pNext == nullptr)  //Last node so can't be deleted
        return false;

    /**
     * @brief The logic is quite simple. As we don't know the size of
     * the node, neither we know the head, so we loop through the list,
     * from the given node till the last node. And while looping, we
     * assign the next node's value to it's previous node till we reach
     * the last node. Once we reach the last node we set the second last
     * node's next pointer to NULL and delete the last node. 
     */
    while (pNode->m_pNext)  // Loop throgh the nodes and assign the next node's value to previous node
    {
        pNode->m_element = pNode->m_pNext->m_element;
        if (pNode->m_pNext->m_pNext == nullptr) //Last node found so delete it.
        {
            auto pLastNode = pNode->m_pNext;
            pNode->m_pNext = nullptr;
            delete pLastNode;
            pLastNode = nullptr;
            break;
        }
        pNode = pNode->m_pNext;
    }
    return true;
}

SinglyLinkedList LinkListAlgos::getSum(const SinglyLinkedList& list1, const SinglyLinkedList& list2, const bool msbFirst)
{
    if (list1.empty() && list2.empty())
        return SinglyLinkedList{};

    else if (list1.empty())
        return list2;

    else if (list2.empty())
        return list1;

    else
    {
        if (msbFirst)
        {
            auto fillStack = [](SinglyNode* pHead, std::stack<int>& theStack)
            {
                while (pHead)
                {
                    theStack.push(pHead->m_element);
                    pHead = pHead->m_pNext;
                }
            };
            /**
             * @brief Calculates the summation of the nodes.
             * This lambda calculates the summation of the nodes, takes
             * into account the carry for the next nodes summation from
             * the previous nodes addition, inserts the resultant nodes
             * into the result list.
             * 
             * This lambda can be used for both the cases where either
             * both the lists are equal in size or one of the list is
             * bigger than the other. The trick is to pass the
             * pointer of the shorter list as pStack1, as the loop within
             * the lambda while making calculation solely depends on the
             * variable pStack1. If both the lists are equal in size then pass
             * any stack pointer to any.  
             */
            auto calculateSum = [](int carry, SinglyLinkedList& sum, std::stack<int>* pStack1, std::stack<int>* pStack2)
            {
                while (!pStack1->empty())
                {
                    auto summation = carry + pStack1->top() + (pStack2 ? pStack2->top() : 0);
                    carry = summation / 10;
                    auto reminder = summation % 10;
                    sum.push_front(reminder);
                    pStack1->pop();
                    if (pStack2)
                        pStack2->pop();
                }
                return carry;
            };
            
            std::stack<int> stack1;
            std::stack<int> stack2;
            auto pH1 = list1.getHead();
            auto pH2 = list2.getHead();

            fillStack(pH1, stack1);
            fillStack(pH2, stack2);

            SinglyLinkedList sum;
            auto carry = 0;
            if (stack1.size() == stack2.size())
            {
                carry = calculateSum(carry, sum, &stack1, &stack2);
                if (carry > 0)
                    sum.push_front(carry);
            }
            else if (stack1.size() < stack2.size())
            {
                carry = calculateSum(carry, sum, &stack1, &stack2); //First calculate the sum for the common length nodes
                carry = calculateSum(carry, sum, &stack2, nullptr); //Now calculate the sum for the remaining nodes of the bigger list
                if (carry > 0)
                    sum.push_front(carry);
            }
            else
            {
                carry = calculateSum(carry, sum, &stack2, &stack1); //First calculate the sum for the common length nodes
                carry = calculateSum(carry, sum, &stack1, nullptr); //Now calculate the sum for the remaining nodes of the bigger list
                if (carry > 0)
                    sum.push_front(carry);
            }
            return sum;
        }
        else    //LSB is at the head node
        {
            /**
             * @brief This lambda calculates the summation of the nodes.
             * This lambda calculates the summation of the nodes, takes
             * into account the carry for the next nodes summation from
             * the previous nodes addition, inserts the resultant nodes
             * into the result list.
             * 
             * This lambda can be used for both the cases where either
             * both the lists are equal in size or one of the list is
             * bigger than the other. The trick is to pass the head
             * pointer of the shorter list as pH1 as the loop within
             * the lambda while making calculation solely depends on the
             * variable pH1. If both the lists are equal in size then pass
             * any head pointer to any.  
             */
            auto claculateSum = [](int carry, SinglyNode** pH1, SinglyNode** pH2, SinglyLinkedList& sum)
            {
                while (*pH1)
                {
                    auto summation = (*pH1)->m_element + (pH2 ? (*pH2)->m_element : 0) + carry;
                    auto reminder = summation % 10;
                    carry = summation / 10;
                    sum.push_back(reminder);
                    *pH1 = (*pH1)->m_pNext;
                    if (pH2)
                        *pH2 = (*pH2)->m_pNext;
                }
                return carry;
            };

            SinglyLinkedList sum;
            auto pHead1 = list1.getHead();
            auto pHead2 = list2.getHead();
            if (list1.size() == list2.size())
            {
                auto carry = 0;
                carry = claculateSum(carry, &pHead1, &pHead2, sum);
                if (carry > 0)
                    sum.push_back(carry);
            }
            else if (list1.size() < list2.size())
            {
                auto carry = 0;
                carry = claculateSum(carry, &pHead1, &pHead2, sum);     //First calculate the sum for the common length nodes
                carry = claculateSum(carry, &pHead2, nullptr, sum);     //Now calculate the sum for the remaining nodes of the bigger list
                if (carry > 0)  //Takes into account the final carry
                    sum.push_back(carry);
            }
            else if (list2.size() < list1.size())
            {
                auto carry = 0;
                carry = claculateSum(carry, &pHead2, &pHead1, sum);     //First calculate the sum for the common length nodes
                carry = claculateSum(carry, &pHead1, nullptr, sum);     //Now calculate the sum for the remaining nodes of the bigger list
                if (carry > 0)      //Takes into account the final carry
                    sum.push_back(carry);
            }
            return sum;
        }
    }
}

bool LinkListAlgos::isPalindrome(const SinglyLinkedList& list)
{
    if (list.empty())   //If the list is empty then return TRUE
        return true;

    auto pHead = list.getHead();
    if (pHead->m_pNext == nullptr)  //If the list has only one element then also it is a palindrome
        return true;

    /**
     * @brief As we don't know the size of the list thus
     * we take two pointers approach, one a runner and
     * the other one is a normal/slow.
     */
    auto pFast = list.getHead();
    std::stack<int> stack;

    /**
     * @brief Push elements from first half of linked list onto stack. When fast pointer or the runner
     * (which is moving at 2x speed) reaches the end of the linked list, then we know we're at the middle
     */
    while (pFast && pFast->m_pNext)
    {
        stack.push(pHead->m_element);
        pHead = pHead->m_pNext;
        pFast = pFast->m_pNext->m_pNext;
    }
    /**
     * @brief The list has odd no. of elements so advance the normal
     * pointer one step to skip the middle element.
     *
     * For example, suppose the list is like below
     * 1-->2-->0-->2-->1. So after the first iteration we have our
     * fast pointer pointing at 0 while the slow one at 2. We iterate
     * the next time. Now the fast is at 1 and the slow one is at 0 which
     * is middle element of the list. So we move forward the slow pointer
     * one step ahead to reach the first element of the rest of the list.
     *
     * If the list would have even number of elements like below
     * 1-->2-->2-->1, then the fast pointer would have reached to a NULL
     * after the second iteration.
     */
    if (pFast)
        pHead = pHead->m_pNext;

    while (pHead)
    {
        if (pHead->m_element != stack.top())
            return false;

        pHead = pHead->m_pNext;
        stack.pop();
    }
    return true;
}

