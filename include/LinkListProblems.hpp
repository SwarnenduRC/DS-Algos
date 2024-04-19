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
         * @brief Remove Dups
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
         * lnput:the node c from the linked list a->b->c->d->e->f
         * Result: nothing is returned, but the new linked list looks like a ->b->d- >e- >f
         */
        static bool deleteMiddle(SinglyNode* pNode);
};

#endif  //_LINK_LIST_PROBLEMS_H_

