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
    , m_pLeft(std::move(rhs.m_pLeft))
    , m_pRight(std::move(rhs.m_pRight))
{
    rhs.m_data = 0;
}

TreeNode& TreeNode::operator=(TreeNode&& rhs) noexcept
{
    if (&rhs != this)
    {
        m_data = rhs.m_data;
        m_pLeft = std::move(rhs.m_pLeft);
        m_pRight = std::move(rhs.m_pRight);
        rhs.m_data = 0;
    }
    return *this;
}

