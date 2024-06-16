/**
 * @file LinkListProblems.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef _LINK_LIST_PROBLEMS_H_
#define _LINK_LIST_PROBLEMS_H_

#include "LinkedList.hpp"

#include <gtest/gtest.h>

using nodes::SinglyNode;
using linked_list::SinglyLinkedList;

class LinkListAlgos : public ::testing::Test
{
    public:
        /**
         * @brief Remove Duplicates
         * Write code to remove duplicates from an unsorted linked list.
         * FOLLOW UP
         * How would you solve this problem if a temporary buffer is not allowed?
         */
        static SinglyLinkedList removeDuplicate(const SinglyLinkedList& list);
        /**
         * @brief Return Kth to Last
         * Implement an algorithm to find the kth to last element of a singly linked list.
         * Assume that you don't know the size of the list
         */
        static void* returnKthToLast(const SinglyLinkedList& list, const size_t k);
        /**
         * @brief Delete Middle Node
         * Implement an algorithm to delete a node in the middle
         * (i.e., any node but the first and last node, not necessarily the exact middle)
         * of a singly linked list, given only access to that node
         * 
         * EXAMPLE
         * Input: The node c from the linked list a->b->c->d->e->f
         * Result: Nothing is returned, but the new linked list looks like a->b->d->e->f
         */
        static bool deleteMiddle(SinglyNode* pNode);
        /**
         * @brief Sum Lists
         * You have two numbers represented by a linked list, where each node contains a single
         * digit. The digits are stored in reverse order, such that the 1 's digit is at the head 
         * of the list. Write a function that adds the two numbers and returns the sum as a linked list.
         * 
         * EXAMPLE
         * 
         * Input: (7-> 1 -> 6) + (5 -> 9 -> 2).That is,617 + 295.
         * Output: 2 -> 1 -> 9. That is, 912
         * 
         * FOLLOW UP
         * 
         * Suppose the digits are stored in forward order. Repeat the above problem.
         * 
         * Input: (6 -> 1 -> 7) + (2 -> 9 -> 5).That is,617 + 295.
         * 
         * Output: 9 -> 1 -> 2. That is, 912.
         */
        static SinglyLinkedList getSum(const SinglyLinkedList& list1, const SinglyLinkedList& list2, const bool msbFirst = false);
        /**
         * @brief Palindrome
         * Implement a function to check if a linked list is a palindrome.
         *
         * To approach this problem, we can picture a palindrome like
         * 0 - > 1 - > 2 - > 1 - > 0. We know that, since it's a palindrome
         * the list must be the same backwards and forwards.
         *
         * We don't know the size of the list
         */
        static bool isPalindrome(const SinglyLinkedList& list);
};

#endif  //_LINK_LIST_PROBLEMS_H_

