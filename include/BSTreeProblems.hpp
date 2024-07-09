#include "BSTTest.hpp"

#include <list>

class BSTreeProblems : public BSTTest
{
    public:
        /**
         * @brief List of Depths
         * Given a binary tree, design an algorithm which creates a linked list of all the nodes
         * at each depth (e.g., if you have a tree with depth D, you'll have D linked lists).
         */
        static std::vector<std::list<TreeNode*>> createLinkedListAtEachLevel(const BSTree& tree) noexcept;
        /**
         * @brief Check Balanced
         * Implement a function to check if a binary tree is balanced. For the purposes of
         * this question, a balanced tree is defined to be a tree such that the heights of the
         * two subtrees of any node never differ by more than one.
         */
        static bool checkBalanced(const BSTree& tree);

    private:
        static int checkBalanced(const TreeNode* pNode);
};

