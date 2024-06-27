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
#include <initializer_list>
#include <vector>

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
    /**
     * @brief Getter and setter
     */
    inline void setData(const int val) noexcept { m_data = val; }
    inline int getData() const noexcept { return m_data; };
    /**
     * @brief Class members of the tree node
     *
     */
    int m_data = 0;
    std::unique_ptr<TreeNode> m_pLeft;
    std::unique_ptr<TreeNode> m_pRight;
};

class BSTree
{
    public:
        // Constructors and destructors
        BSTree() = default;
        ~BSTree() = default;
        BSTree(const BSTree& rhs) noexcept;
        BSTree& operator=(const BSTree& rhs) noexcept;
        BSTree(BSTree&& rhs) noexcept;
        BSTree& operator=(BSTree&& rhs) noexcept;
        BSTree(const std::initializer_list<int>& list) noexcept;
        // Modifiers
        void clear() noexcept;
        void insert(const int data) noexcept;
        void erase(const int data) noexcept;
        void erase(TreeNode* pNode) noexcept;
        // Getters and checkers
        TreeNode* find(const int data) noexcept;
        inline size_t height() const noexcept { return m_height; }
        inline size_t size() const noexcept { return m_size; }
        inline TreeNode* getRoot() const noexcept { return m_pRoot.get(); }
        inline bool empty() const noexcept { return m_size == 0; }

    private:
        // Internal functions to help public methods
        void clearInternal(std::unique_ptr<TreeNode>& pRoot) noexcept;
        void insertInternal(TreeNode* pRoot, const int data) noexcept;
        void eraseInternal(TreeNode* pNode, std::unique_ptr<TreeNode>& pParent) noexcept;
        TreeNode* findInternal(TreeNode* pRoot, const int data) noexcept;
        // Private helper methods
        [[nodiscard]] size_t calculateHeight(TreeNode* pRoot) const noexcept;
        TreeNode* makeTree(const int startIdx, const int endIdx) noexcept;
        std::unique_ptr<TreeNode> findInorderSuccessor(std::unique_ptr<TreeNode>& pRightNode) noexcept;
        std::unique_ptr<TreeNode> findInorderPredecessor(std::unique_ptr<TreeNode>& pLefttNode) noexcept;

        /**
         * @brief Class members of the BST
         *
         */
        size_t m_height = 0;
        size_t m_size = 0;
        std::unique_ptr<TreeNode> m_pRoot;
        std::vector<int> m_dataVec = {};
};

#endif  //_BS_TREE_H_

