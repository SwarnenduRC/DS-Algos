/**
 * @file LinkedList.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-04-07
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _LINKED_LIST_HPP_
#define _LINKED_LIST_HPP_

#include <utility>

namespace nodes
{
    struct SinglyNode
    {
        int m_element = 0;
        SinglyNode* m_pNext = nullptr;

        SinglyNode() = default;
        explicit SinglyNode(const int val) noexcept
            : m_element(val)
            , m_pNext(nullptr)
        {}
        ~SinglyNode() noexcept
        {
            m_element = 0;
            if (m_pNext)
                delete m_pNext;
            m_pNext = nullptr;
        }
        SinglyNode(const SinglyNode& rhs) noexcept
            : m_element(rhs.m_element)
            , m_pNext(nullptr)
        {
            if (rhs.m_pNext)
                m_pNext = new SinglyNode(*rhs.m_pNext);
        }
        SinglyNode& operator=(const SinglyNode& rhs) noexcept
        {
            if (this != &rhs)
            {
                if (m_pNext)
                    delete m_pNext;
                m_pNext = nullptr;
                m_element = rhs.m_element;
                if (rhs.m_pNext)
                    m_pNext = new SinglyNode(*rhs.m_pNext);
            }
            return *this;
        }
        SinglyNode(SinglyNode&& rhs) noexcept
            : m_element(std::move_if_noexcept(rhs.m_element))
            , m_pNext(std::move_if_noexcept(rhs.m_pNext))
        {
            rhs.m_element = 0;
            rhs.m_pNext = nullptr;
        }
        SinglyNode& operator=(SinglyNode&& rhs) noexcept
        {
            if (this != &rhs)
            {
                if (m_pNext)
                    delete m_pNext;
                
                m_pNext = std::move_if_noexcept(rhs.m_pNext);
                m_element = std::move_if_noexcept(rhs.m_element);
                rhs.m_element = 0;
                rhs.m_pNext = nullptr;
            }
            return *this;
        }
    };
};

namespace linked_list
{
    using nodes::SinglyNode;

    class SinglyLinkedList
    {
        public:
            SinglyLinkedList() = default;
            SinglyLinkedList(const std::initializer_list<int>& list);
            ~SinglyLinkedList();
            SinglyLinkedList(const SinglyLinkedList& rhs) noexcept;
            SinglyLinkedList(SinglyLinkedList&& rhs) noexcept;
            SinglyLinkedList& operator=(const SinglyLinkedList& rhs) noexcept;
            SinglyLinkedList& operator=(SinglyLinkedList&& rhs) noexcept;

            void clear();            
            void push_front(const int val);
            void push_back(const int val);
            void push_at(const size_t pos, const int val);
            void push_middle(const int val);
            /**
             * @brief Makes the list cyclic.
             *        This function makes the linked list
             *        a cyclic one by making next of tail
             *        pointer pointing back to head
             */
            void makeCyclic();
            /**
             * @brief Reverses a linked list
             *        Reverses a linked list in O(N) time
             */
            void reverse();

            int pop_front();
            int pop_back();
            int pop_at(const size_t pos);
            int pop_middle();

            void copy(const SinglyLinkedList& rhs);
            int* find(const int val) const noexcept;
            inline bool empty() const noexcept { return m_size ? false : true; }
            inline size_t size() const noexcept { return m_size; }
            inline SinglyNode* getHead() const noexcept { return m_pHead; }
            inline SinglyNode* getTail() const noexcept { return m_pTail; }
            /**
             * @brief Removes a particular node from a list.
             *        A static function to remove a node from
             *        a list and re adjusting its head and tail
             *        pointers accordingly.
             * 
             * @param [in/out] list The list from which the node to be deleted
             * @param pNode The node which would be deleted from the list
             * @return Returns nothing 
             */
            static void remove(SinglyLinkedList& list, SinglyNode* pNode) noexcept;

            /**
             * @brief Detects whether the given linked list is cyclic in nature or not.
             *        A static function to detect whether the given linked list is
             *        cyclic in nature or not. It uses two pointers solution or 
             *        Floyd's cycle finding algorithm, also known as "tortoise and hare"
             *        algorithm
             * 
             * @param pHead The head of the linked list
             * @return true If the list is cyclic, 
             * @return false otherwise
             */
            static bool isCyclic(SinglyNode* pHead);

            /**
             * @brief Checks if there is an intersection between the two linked lists.
             *        A static function to check if the linked lists in question are
             *        intersected or not. Throws a std runtime exception if one of the
             *        given list cyclic in nature
             * 
             * @param pHead1 The head pointer of the first list
             * @param pHead2 The head pointer of the second list
             * @return true If the lists are inter connected, 
             * @return false otherwise
             */
            static bool areListsIntersected(SinglyNode* pHead1, SinglyNode* pHead2);

        private:
            SinglyNode* m_pHead = nullptr;
            SinglyNode* m_pTail = nullptr;
            size_t m_size = 0;
    };
};
#endif  // _LINKED_LIST_HPP_