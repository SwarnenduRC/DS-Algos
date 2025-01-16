#include "LinkedList.hpp"

#include <gtest/gtest.h>

using nodes::SinglyNode;

class SinglyNodeTest : public ::testing::Test
{
    protected:
        SinglyNode m_defaultNode;

};

using linked_list::SinglyLinkedList;

class SinglyLinkedListTest : public ::testing::Test
{
    protected:
        SinglyLinkedList m_sList;
};