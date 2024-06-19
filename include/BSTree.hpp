/**
 * @file BSTree.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-10
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef _BS_TREE_H_
#define _BS_TREE_H_

#include <memory>

struct TreeNode
{
    /**
     * @brief Constructors and Destructors
     */
    TreeNode() = default;
    ~TreeNode() = default;
    explicit TreeNode(const int val) noexcept;
    TreeNode(const TreeNode& rhs) noexcept;
    TreeNode& operator=(const TreeNode& rhs) noexcept;
    TreeNode(TreeNode&& rhs) noexcept;
    TreeNode& operator=(TreeNode&& rhs) noexcept;

    inline void setData(const int val) noexcept { m_data = val; }
    inline int getData() const noexcept { return m_data; }


    int m_data = 0;
    std::unique_ptr<TreeNode> m_pLeft;
    std::unique_ptr<TreeNode> m_pRight;
};

#endif  //_BS_TREE_H_