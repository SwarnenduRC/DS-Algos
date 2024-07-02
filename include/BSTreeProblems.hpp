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
};