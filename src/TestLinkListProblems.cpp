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

TEST_F(LinkListAlgos, testGetSum)
{
    {
        SinglyLinkedList list1 = { 1, 2, 3, 4, 5, 6 };  //654321 (LSB first at head)
        SinglyLinkedList list2 = { 1, 2, 3, 4, 3, 2 };  //234321 (LSB first at head)
        SinglyLinkedList expList = { 2, 4, 6, 8, 8, 8 }; // 888642 = 654321 + 234321 (LSB first at head)

        auto resultList = getSum(list1, list2);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1 = { 1, 2, 3, 9, 9, 6 };  //699321 (LSB first at head)
        SinglyLinkedList list2 = { 9, 7, 8 };  //879 (LSB first at head)
        SinglyLinkedList expList = { 0, 0, 2, 0, 0, 7 }; // 700200 = 654321 + 234321 (LSB first at head)

        auto resultList = getSum(list1, list2);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list2 = { 1, 2, 3, 9, 9, 6 };  //699321 (LSB first at head)
        SinglyLinkedList list1 = { 9, 7, 8 };  //879 (LSB first at head)
        SinglyLinkedList expList = { 0, 0, 2, 0, 0, 7 }; // 700200 = 654321 + 234321 (LSB first at head)

        auto resultList = getSum(list1, list2);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1 = { 1, 2, 3, 9, 9, 6 };  //699321 (LSB first at head)
        SinglyLinkedList list2 = {};

        auto resultList = getSum(list1, list2);
        ASSERT_EQ(list1.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = list1.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list2 = { 1, 2, 3, 9, 9, 6 };  //699321 (LSB first at head)
        SinglyLinkedList list1 = {};

        auto resultList = getSum(list1, list2);
        ASSERT_EQ(list2.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = list2.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1;
        SinglyLinkedList list2;
        ASSERT_TRUE(getSum(list1, list2).empty());
    }
    
    
    {
        SinglyLinkedList list1 = { 6, 5, 4, 3, 2, 1 };  //654321 (MSB first at head)
        SinglyLinkedList list2 = { 2, 3, 4, 3, 2, 1 };  //234321 (MSB first at head)
        SinglyLinkedList expList = { 8, 8, 8, 6, 4, 2 }; // 888642 = 654321 + 234321 (MSB first at head)

        auto resultList = getSum(list1, list2, true);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1 = { 6, 9, 9, 3, 2, 1 };  //699321 (MSB first at head)
        SinglyLinkedList list2 = { 8, 7, 9 };  //879 (MSB first at head)
        SinglyLinkedList expList = { 7, 0, 0, 2, 0, 0 }; // 700200 = 699321 + 879 (MSB first at head)

        auto resultList = getSum(list1, list2, true);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list2 = { 6, 9, 9, 3, 2, 1 };  //699321 (MSB first at head)
        SinglyLinkedList list1 = { 8, 7, 9 };  //879 (MSB first at head)
        SinglyLinkedList expList = { 7, 0, 0, 2, 0, 0 }; // 700200 = 654321 + 234321 (MSB first at head)

        auto resultList = getSum(list1, list2, true);
        ASSERT_EQ(expList.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = expList.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1 = { 6, 9, 9, 3, 2, 1 };  //699321 (MSB first at head)
        SinglyLinkedList list2 = {};

        auto resultList = getSum(list1, list2, true);
        ASSERT_EQ(list1.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = list1.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list2 = { 6, 9, 9, 3, 2, 1 };  //699321 (MSB first at head)
        SinglyLinkedList list1 = {};

        auto resultList = getSum(list1, list2, true);
        ASSERT_EQ(list2.size(), resultList.size());

        auto pResultHead = resultList.getHead();
        auto pExpHead = list2.getHead();
        while (pExpHead)
        {
            EXPECT_EQ(pResultHead->m_element, pExpHead->m_element);
            pResultHead = pResultHead->m_pNext;
            pExpHead = pExpHead->m_pNext;
        }
        ASSERT_EQ(nullptr, pResultHead);
    }
    {
        SinglyLinkedList list1;
        SinglyLinkedList list2;
        ASSERT_TRUE(getSum(list1, list2, true).empty());
    }
}

TEST_F(LinkListAlgos, testIsPalindrome)
{
    {
        SinglyLinkedList list = { 1, 2, 3, 4, 3, 2, 1 };
        EXPECT_TRUE(isPalindrome(list));
    }
    {
        SinglyLinkedList list = { 1, 2, 3, 4, 4, 3, 2, 1 };
        EXPECT_TRUE(isPalindrome(list));
    }
    {
        SinglyLinkedList list = { 1, 2, 3, 4, 3, 5, 1 };
        EXPECT_FALSE(isPalindrome(list));
    }
}
