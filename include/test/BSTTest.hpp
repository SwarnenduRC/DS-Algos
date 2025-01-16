/**
 * @file BSTTest.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-06-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "BSTree.hpp"

#include <gtest/gtest.h>

using IntVector = std::vector<int>;
using IntMatrix = std::vector<std::vector<TreeNode*>>;

class BSTTest : public ::testing::Test
{
    public:
        static IntVector getElementsPreOrder(const BSTree& tree) noexcept;
        static IntVector getElementsInOrder(const BSTree& tree) noexcept;
        static IntVector getElementsPostOrder(const BSTree& tree) noexcept;
        static IntMatrix getElementsLevelOrder(const BSTree& tree) noexcept;
        static void testTree(const BSTree& tree) noexcept;
    
    protected:
        BSTree m_tree;
};