/**
 * @file BSTree.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "BSTree.hpp"

#include <algorithm>

TreeNode::TreeNode(const int val) noexcept
    : m_data(val)
    , m_pLeft(nullptr)
    , m_pRight(nullptr)
{}

TreeNode::TreeNode(const TreeNode& rhs) noexcept
    : m_data(rhs.m_data)
    , m_pLeft(rhs.m_pLeft ? std::make_unique<TreeNode>(*rhs.m_pLeft) : nullptr)
    , m_pRight(rhs.m_pRight ? std::make_unique<TreeNode>(*rhs.m_pRight) : nullptr)
{}

TreeNode& TreeNode::operator=(const TreeNode& rhs) noexcept
{
    if (&rhs != this)
    {
        m_data = rhs.m_data;
        m_pLeft.reset(new TreeNode(*rhs.m_pLeft));
        m_pRight.reset(new TreeNode(*rhs.m_pRight));
    }
    return *this;
}

TreeNode::TreeNode(TreeNode&& rhs) noexcept
    : m_data(rhs.m_data)
    , m_pLeft(std::move_if_noexcept(rhs.m_pLeft))
    , m_pRight(std::move_if_noexcept(rhs.m_pRight))
{
    rhs.m_data = 0;
}

TreeNode& TreeNode::operator=(TreeNode&& rhs) noexcept
{
    if (&rhs != this)
    {
        m_data = rhs.m_data;
        m_pLeft = std::move_if_noexcept(rhs.m_pLeft);
        m_pRight = std::move_if_noexcept(rhs.m_pRight);
        rhs.m_data = 0;
    }
    return *this;
}

BSTree::BSTree(const BSTree& rhs) noexcept
    : m_height(rhs.m_height)
    , m_size(rhs.m_size)
    , m_pRoot(std::make_unique<TreeNode>(*(rhs.m_pRoot)))
{
}

BSTree& BSTree::operator=(const BSTree& rhs) noexcept
{
    if (this != &rhs)
    {
        if (!empty())
            clear();

        m_height = rhs.m_height;
        m_size = rhs.m_size;
        m_pRoot.reset(new TreeNode(*rhs.m_pRoot));
    }
    return *this;
}

BSTree::BSTree(BSTree&& rhs) noexcept
    : m_height(rhs.m_height)
    , m_size(rhs.m_size)
    , m_pRoot(std::move_if_noexcept(rhs.m_pRoot))
{
    rhs.m_height = 0;
    rhs.m_size = 0;
}

BSTree& BSTree::operator=(BSTree&& rhs) noexcept
{
    if (this != &rhs)
    {
        if (!empty())
            clear();

        m_height = rhs.m_height;
        m_size = rhs.m_size;
        m_pRoot = std::move_if_noexcept(rhs.m_pRoot);

        rhs.m_height = 0;
        rhs.m_size = 0;
    }
    return *this;
}

BSTree::BSTree(const std::initializer_list<int>& list) noexcept
{
    if (list.size() > 0)
    {
        m_dataVec = list;
        std::sort(m_dataVec.begin(), m_dataVec.end());
        m_pRoot.reset(makeTree(0, static_cast<int>(list.size() - 1)));
        m_size = m_dataVec.size();
        m_height = calculateHeight(m_pRoot.get());
        m_dataVec.clear();
    }
}

void BSTree::clear() noexcept
{
    clearInternal(m_pRoot);
    m_height = 0;
}

void BSTree::clearInternal(std::unique_ptr<TreeNode>& pRoot) noexcept
{
    if (pRoot)
    {
        clearInternal(pRoot->m_pLeft);  //Clear left sub tree
        clearInternal(pRoot->m_pRight); //Clear right sub tree
        pRoot.reset();  //Reset the root
        --m_size;
    }
}

void BSTree::insert(const int data) noexcept
{
    if (find(data))
        return; //A BST can't have duplicate data in normal scenario

    if (empty())
        m_pRoot = std::make_unique<TreeNode>(data);
    else
        insertInternal(m_pRoot.get(), data);
    
    ++m_size;
    m_height = calculateHeight(m_pRoot.get());
}

void BSTree::erase(const int data) noexcept
{
    auto pNode = find(data);
    if (pNode)
        erase(pNode);
}

void BSTree::erase(TreeNode* pNode) noexcept
{
    eraseInternal(pNode, m_pRoot);
    --m_size;
    m_height = calculateHeight(m_pRoot.get());
}

TreeNode* BSTree::find(const int data) noexcept
{
    if (empty())
        return nullptr;

    return findInternal(m_pRoot.get(), data);
}

TreeNode* BSTree::findInternal(TreeNode* pRoot, const int data) noexcept
{
    if (pRoot)
    {
        if (data == pRoot->getData())
            return pRoot;
        else if (data < pRoot->getData())
            return findInternal(pRoot->m_pLeft.get(), data);
        else if (data > pRoot->getData())
            return findInternal(pRoot->m_pRight.get(), data);
    }
    return nullptr;
}

void BSTree::insertInternal(TreeNode* pRoot, const int data) noexcept
{
    if (data < pRoot->getData())
    {
        if (pRoot->m_pLeft)
            insertInternal(pRoot->m_pLeft.get(), data);
        else
            pRoot->m_pLeft = std::make_unique<TreeNode>(data);
    }
    else
    {
        if (pRoot->m_pRight)
            insertInternal(pRoot->m_pRight.get(), data);
        else
            pRoot->m_pRight = std::make_unique<TreeNode>(data);
    }
}

void BSTree::eraseInternal(TreeNode* pNode, std::unique_ptr<TreeNode>& pParent) noexcept
{
    if (pNode)
    {
        /**
         * @brief Now while erasing a node from the BST there might be three
         * scenarios mainly;
         * 1) The node is a leaf node, i.e.; it has no children
         * 2) The node is having only either left or right child
         * 3) The node is having both the children
         */
        if (pParent->getData() == pNode->getData()) // The node to be deleted spotted
        {
            // Case1: The node is a leaf node
            if (pParent->m_pLeft == nullptr && pParent->m_pRight == nullptr)
            {
                pParent.reset();
                pNode = nullptr;
            }
            // Case2: The node is having only a left child
            else if (pParent->m_pLeft && pParent->m_pRight == nullptr)
            {
                auto pLeftChild = std::move(pParent->m_pLeft);
                pParent.reset();
                pParent = std::move(pLeftChild);
            }
            // Case3: The node is having only a right child
            else if (pParent->m_pLeft == nullptr && pParent->m_pRight)
            {
                auto pRightChild = std::move(pParent->m_pRight);
                pParent.reset();
                pParent = std::move(pRightChild);
            }
            // Case4: The parent have both the children
            else
            {
                /**
                 * In this case the node to be deleted can either be replaced 
                 * by it's inorder successor or inorder predessor to maintain
                 * the property of the BST.
                 */
                auto pSuccessor = findInorderSuccessor(pParent->m_pRight);
                pParent.reset();
                pParent = std::move(pSuccessor);
            }
        }
        else if (pNode->getData() < pParent->getData()) // The node resides to the left of it's parent
        {
            eraseInternal(pNode, pParent->m_pLeft);
        }
        else // The node resides to the right of its parent
        {
            eraseInternal(pNode, pParent->m_pRight);
        }
    }
}

size_t BSTree::calculateHeight(TreeNode* pRoot) const noexcept
{
    if (pRoot == nullptr)
        return 0;

    size_t leftTreeHeight = 0;
    size_t rightTreeHeight = 0;

    if (pRoot->m_pLeft)
        leftTreeHeight = calculateHeight(pRoot->m_pLeft.get());

    if (pRoot->m_pRight)
        rightTreeHeight = calculateHeight(pRoot->m_pRight.get());

    return 1 + std::max(leftTreeHeight, rightTreeHeight);
}

std::unique_ptr<TreeNode> BSTree::findInorderSuccessor(std::unique_ptr<TreeNode>& pRightNode) noexcept
{
    if (pRightNode == nullptr)
        return nullptr;

    if (pRightNode->m_pLeft)
    {
        return findInorderSuccessor(pRightNode->m_pLeft);
    }
    else
    {
        return std::move(pRightNode);
    }
}

std::unique_ptr<TreeNode> BSTree::findInorderPredecessor(std::unique_ptr<TreeNode>& pLefttNode) noexcept
{
    if (pLefttNode == nullptr)
        return nullptr;

    if (pLefttNode->m_pRight)
    {
        return findInorderSuccessor(pLefttNode->m_pRight);
    }
    else
    {
        return std::move(pLefttNode);
    }
}

TreeNode* BSTree::makeTree(const int startIdx, const int endIdx) noexcept
{
    if (startIdx > endIdx)  // Should be always startIdx > endIdx, endIdx > startIdx won't work
        return nullptr;
    
    auto midIdx = startIdx + (endIdx - startIdx) / 2;
    auto pRoot = new TreeNode(m_dataVec[midIdx]);
    pRoot->m_pLeft.reset(makeTree(startIdx, (midIdx - 1)));
    pRoot->m_pRight.reset(makeTree((midIdx + 1), endIdx));
    return pRoot;
}

