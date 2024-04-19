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

TEST_F(LinkListAlgos, testReturnKthToLast)
{
    {
        SinglyLinkedList list = { 1, 3 };
        size_t k = 0;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(3, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5 };
        size_t k = 0;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(5, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5 };
        size_t k = 1;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(3, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5 };
        size_t k = 2;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(1, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        size_t k = 2;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(10, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        size_t k = 1;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(7, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        size_t k = 2;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(10, pNode->m_element);
    }
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        size_t k = 3;
        auto pNode = static_cast<SinglyNode*>(returnKthToLast(list, k));
        ASSERT_NE(nullptr, pNode);
        EXPECT_EQ(5, pNode->m_element);
    }
}

TEST_F(LinkListAlgos, testDeleteMiddle)
{
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        SinglyLinkedList expectedModifiedList = { 1, 3, 5, 10, 30 };
        auto pHead = list.getHead();
        while (pHead)
        {
            if (pHead->m_element == 7)
            {
                auto pNode = pHead;
                EXPECT_TRUE(deleteMiddle(pNode));
                break;
            }
            pHead = pHead->m_pNext;
        }
        {
            auto pHead = list.getHead();
            auto pRefHead = expectedModifiedList.getHead();
            while (pHead && pRefHead)
            {
                EXPECT_EQ(pHead->m_element, pRefHead->m_element);
                pHead = pHead->m_pNext;
                pRefHead = pRefHead->m_pNext;
            }
            ASSERT_EQ(nullptr, pRefHead);
            ASSERT_EQ(nullptr, pHead);
        }
    }
    {
        SinglyLinkedList list = { 1, 3, 5, 10, 7, 30 };
        auto pHead = list.getHead();
        while (pHead)
        {
            if (pHead->m_element == 30)
            {
                auto pNode = pHead;
                EXPECT_FALSE(deleteMiddle(pNode));
                break;
            }
            pHead = pHead->m_pNext;
        }
    }
    {
        SinglyNode *pNode = nullptr;
        EXPECT_FALSE(deleteMiddle(pNode));
    }
}
