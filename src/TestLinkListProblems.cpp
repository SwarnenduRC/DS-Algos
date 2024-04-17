/**
 * @file TestLinkListProblems.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-08
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "LinkListProblems.hpp"

TEST_F(LinkListAlgos, testRemoveDuplicate)
{
    SinglyLinkedList list = { 1, 3, 5, 1, 7, 3 };
    SinglyLinkedList expList = { 1, 3, 5, 7 };

    auto resultList = removeDuplicate(list);
    EXPECT_EQ(resultList.size(), expList.size());

    auto pHeadExpList = expList.getHead();
    auto pHeadResultList = resultList.getHead();

    while (pHeadExpList && pHeadResultList)
    {
        EXPECT_EQ(pHeadExpList->m_element, pHeadResultList->m_element);
        pHeadExpList = pHeadExpList->m_pNext;
        pHeadResultList = pHeadResultList->m_pNext;
    }
    EXPECT_EQ(nullptr, pHeadExpList);
    EXPECT_EQ(nullptr, pHeadResultList);
}