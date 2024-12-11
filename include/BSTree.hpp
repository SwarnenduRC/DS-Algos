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
     * @brief Getters and setters
     */
    inline void setData(const int val) noexcept { m_data = val; }
    inline int getData() const noexcept { return m_data; };
    /**
     * @brief Class members of the tree node
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
        /**
         * @brief Clears a BST.
         *        It clears the tree and
         *        frees all the allocate nodes.
         *
         *        Throws no exception
         */
        void clear() noexcept;
        /**
         * @brief Inserts an element into the tree.
         *        Inserts an element into the tree
         *        at the right position while maintaining
         *        the property of a BST. If the element
         *        to be inserted is already in the tree
         *        it does nothing.
         *
         * @param [in] data The element to be inserted
         */
        void insert(const int data) noexcept;
        /**
         * @brief Erases a data from the tree.
         *        Erases an element from the tree.
         *        If the element is not present in the
         *        tree then it does nothing. Throws no exception.
         *
         * @param [in] data The data to be erased.
         */
        void erase(const int data) noexcept;
        /**
         * @brief Erases a node from the tree.
         *        Erases a node from the tree.
         *        If the node is not present in the
         *        tree then it does nothing. Throws no exception.
         *
         * @param [in] pNode The node to be erased.
         */
        void erase(TreeNode* pNode) noexcept;
        // Getters and checkers
        /**
         * @brief Finds a data in the tree if present.
         *        Throws no exception
         *
         * @param [in] data The data to find.
         * @return TreeNode* The node which contains the data.
         */
        TreeNode* find(const int data) noexcept;
        /**
         * @brief Gets the height of the tree. Throws no exception.
         *
         * @return size_t Height of the tree
         */
        inline size_t height() const noexcept { return m_height; }
        /**
         * @brief Gets the size or total no of nodes in the tree.
         *        Throws no exception.
         *
         * @return size_t Size of the tree
         */
        inline size_t size() const noexcept { return m_size; }
        /**
         * @brief Gets the Root object of the tree.
         *
         * @return TreeNode* The pointer pointing to the root of the tree
         */
        inline TreeNode* getRoot() const noexcept { return m_pRoot.get(); }
        /**
         * @brief Checks if the tree is empty or not.
         *
         * @return true If the tree is empty.
         * @return false If the tree is not empty.
         */
        inline bool empty() const noexcept { return m_size == 0; }

    protected:
        // Internal functions to help public methods
        /**
         * @brief Clears a tree or subtree.
         *        Clears a tree or sub tree denoted
         *        by the root node it received. Private member.
         *
         * @param [inout] pRoot The root of the tree or sub tree.
         */
        void clearInternal(std::unique_ptr<TreeNode>& pRoot) noexcept;
        /**
         * @brief Inserts a data into tree while maintaining it's property.
         *        Inserts a data element into the tree while maintaining
         *        the property of the BST.
         *
         * @param [inout] pRoot The root of the tree.
         * @param [in] data The data to be inserted
         */
        void insertInternal(TreeNode* pRoot, const int data) noexcept;
        /**
         * @brief Erases/deletes a node from the BST.
         *        Erases or deletes a node from the BST
         *        and re arranges the tree accordingly.
         *
         * @param [in] pNode The node to be deleted
         * @param [in] pParent The parent node of the to be deleted node.
         */
        void eraseInternal(TreeNode* pNode, std::unique_ptr<TreeNode>& pParent) noexcept;
        /**
         * @brief Finds an element (if present) in the BST. Returns NULL if not found.
         *
         * @param [in] pRoot The root of the BST
         * @param [in] data The data to be searched for
         * @return TreeNode* The node which contains the data otherwise NULL
         */
        TreeNode* findInternal(TreeNode* pRoot, const int data) noexcept;

    private:
        /**
         * @brief Claculates the height of the tree denoted by root passed in.
         *        Recursive in nature.
         * @param [in] pRoot The root of the tree
         * @return size_t The calculated height.
         */
        [[nodiscard]] size_t calculateHeight(TreeNode* pRoot) const noexcept;
        /**
         * @brief Makes a tree out of a list of nodes. Recursive in nature.
         *
         * @param [in] startIdx The start index of the list of nodes
         * @param [in] endIdx The end index of the list of nodes.
         * @return TreeNode* The root of the constructed tree
         */
        TreeNode* makeTree(const int startIdx, const int endIdx) noexcept;
        /**
         * @brief Finds the inorder successor of a node in the tree.
         *        Recursive in nature.
         * @param [in] pRightNode The right child/node of the node for which we need to find
         *                        the in order successor.
         * @return std::unique_ptr<TreeNode> The node which contains the in order successor.
         */
        std::unique_ptr<TreeNode> findInorderSuccessor(std::unique_ptr<TreeNode>& pRightNode) noexcept;
        /**
         * @brief Finds the inorder predessor of a node in the tree.
         *        Recursive in nature.
         * @param [in] pLefttNode The left child/node of the node for which we need to find
         *                        the in order successor.
         * @return std::unique_ptr<TreeNode> The node which contains the in order successor.
         */
        std::unique_ptr<TreeNode> findInorderPredecessor(std::unique_ptr<TreeNode>& pLefttNode) noexcept;

        /**
         * @brief Class members of the BST
         *
         */
        size_t m_height = 0;
        size_t m_size = 0;
        std::unique_ptr<TreeNode> m_pRoot;
        std::vector<int> m_dataVec = {};    //Necessary to construct from std::initializer list constructor
};

#endif  //_BS_TREE_H_

