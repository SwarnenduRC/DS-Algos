#include "BSTTest.hpp"

#include <stack>

//Pre order means root->left->right
IntVector BSTTest::getElementsPreOrder(const BSTree& tree) noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode*> nodeStack;
    auto pRootNode = tree.getRoot();
    nodeStack.push(pRootNode);
    while (!nodeStack.empty())
    {
        auto pCurrentNode = nodeStack.top();
        nodeStack.pop();
        if (pCurrentNode)
        {
            retVec.emplace_back(pCurrentNode->getData());
            //Now push the right node first so that it gets processed after left node
            if (pCurrentNode->m_pRight)
                nodeStack.push(pCurrentNode->m_pRight.get());
            //Now push the left child
            if (pCurrentNode->m_pLeft)
                nodeStack.push(pCurrentNode->m_pLeft.get());
        }
    }
    return retVec;
}

//In order means left->root->right
IntVector BSTTest::getElementsInOrder(const BSTree& tree) noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode*> nodeStack;
    auto pCurrNode = tree.getRoot();
    while (pCurrNode || !nodeStack.empty())
    {
        //Keep going through the left sub tree 
        if (pCurrNode)
        {
            nodeStack.push(pCurrNode);  //Push the current node before moving to it's left sub tree
            pCurrNode = pCurrNode->m_pLeft.get();
            continue;
        }
        pCurrNode = nodeStack.top();    //No more left node, so process the current one i.e; root of the sub tree
        nodeStack.pop();
        retVec.emplace_back(pCurrNode->getData());
        pCurrNode = pCurrNode->m_pRight.get();  //Now move to the right sub tree of the root.
    }
    return retVec;
}

//Post order means left->right->root
IntVector BSTTest::getElementsPostOrder(const BSTree& tree) noexcept
{
    if (!tree.getRoot())
        return IntVector{};

    IntVector retVec;
    std::stack<TreeNode*> nodeStack;
    auto pCurrNode = tree.getRoot();
    TreeNode* pLastVisitedNode = nullptr;
    while (pCurrNode || !nodeStack.empty())
    {
        if (pCurrNode)
        {
            nodeStack.push(pCurrNode);      //First push the root node of the tree
            pCurrNode = pCurrNode->m_pLeft.get();   //Then keep traversing to its left sub trees till we reach the leaf node
            continue;
        }
        //Now start backtracking
        auto pProcessNode = nodeStack.top();
        //While backtracking check if it has any right sub tree and it is not visited already
        if (pProcessNode->m_pRight && pProcessNode->m_pRight.get() != pLastVisitedNode)
        {
            pCurrNode = pProcessNode->m_pRight.get();
            continue;
        }
        else
        {
            retVec.emplace_back(pProcessNode->getData());   //No right node or even if it has one but already visited, process it
            pLastVisitedNode = nodeStack.top(); //Mark it as last/latest visited as this node might be the right child of the next node in the stack
            nodeStack.pop();
        }
    }
    return retVec;
}

// Level order traversal
IntMatrix BSTTest::getElementsLevelOrder(const BSTree& tree) noexcept
{
    if (!tree.getRoot())
        return IntMatrix{};

    IntMatrix retVal = {};
    std::vector<TreeNode*> levelVec = {tree.getRoot()}; //Get the root node of the tree first
    //During each iteration check whether the list is having some data or not
    while (!levelVec.empty())
    {
        retVal.emplace_back(levelVec);
        //Convert the current level as prior level before we move to the next level
        auto parents = levelVec;
        //Reset it for the next level/iteration
        levelVec.clear();
        //Check for children of the current level nodes
        for (const auto& pParentNode : parents)
        {
            if (pParentNode->m_pLeft)
                levelVec.emplace_back(pParentNode->m_pLeft.get());

            if (pParentNode->m_pRight)
                levelVec.emplace_back(pParentNode->m_pRight.get());
        }
    }
    return retVal;
}

void BSTTest::testTree(const BSTree& tree) noexcept
{
    constexpr size_t expectedHeight = 4;
    constexpr size_t expectedSize = 9;
    EXPECT_EQ(expectedHeight, tree.height());
    EXPECT_EQ(expectedSize, tree.size());

    //The in-order traversal of a balanced BST always
    //should give the tree elements in a sorted order (guranteed)
    /*
        A balanced BST constructed from the elements ranges 1:9
        either form a BST like below
                5
               / \
              3   7
             / \ / \
            2  4 6  8
           /         \
          1           9

        or another like below one which also a balanced BST
                        5
                       / \
                      2    7
                     / \  / \
                    1   3 6  8
                         \    \
                          4    9
    */
    IntVector treeItemsInOrder = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    auto inOrderList = getElementsInOrder(tree);
    for (size_t idx = 0; idx < treeItemsInOrder.size(); ++idx)
        EXPECT_EQ(treeItemsInOrder[idx], inOrderList[idx]);

    /**
     * @brief This level order validation totally depends on the above two
     * possible tree structures (for testing the logic whereas the logic itself
     * stands valid for any BS tree with any level).
     *
     * A level order traversal of the above tree (which might have two alternate
     * set of elements at each level) would give us the following
     *
     * Level-0: 5
     * Level-1: Either { 3, 7 } or { 2, 7 }
     * Level-2: Either { 2, 4, 6, 8 } or { 1, 3, 6, 8 }
     * Level-3: Either { 1, 9 } or { 4, 9 }
     */
    auto levelOrder = getElementsLevelOrder(tree);
    ASSERT_EQ(4, static_cast<int>(levelOrder.size()));

    EXPECT_EQ(static_cast<int>(levelOrder[0].size()), 1);
    EXPECT_EQ(static_cast<int>(levelOrder[1].size()), 2);
    EXPECT_EQ(static_cast<int>(levelOrder[2].size()), 4);
    EXPECT_EQ(static_cast<int>(levelOrder[3].size()), 2);

    EXPECT_EQ(levelOrder[0][0]->getData(), 5);
    {
        auto secondLevelElements = levelOrder[1];
        std::vector<int> firstProbability = { 3, 7 };
        std::vector<int> secondProbability = { 2, 7 };
        for (size_t idx = 0; idx < firstProbability.size(); idx++)
        {
            if (0 == idx)
                EXPECT_TRUE((firstProbability[idx] == secondLevelElements[idx]->getData()) || (secondProbability[idx] == secondLevelElements[idx]->getData()));
            else
                EXPECT_EQ(firstProbability[idx], secondLevelElements[idx]->getData());
        }
    }
    {
        auto thirdLevelElements = levelOrder[2];
        std::vector<int> firstProbability = { 2, 4, 6, 8 };
        std::vector<int> secondProbability = { 1, 3, 6, 8 };
        for (size_t idx = 0; idx < firstProbability.size(); idx++)
        {
            if (0 == idx || 1 == idx)
                EXPECT_TRUE((firstProbability[idx] == thirdLevelElements[idx]->getData()) || (secondProbability[idx] == thirdLevelElements[idx]->getData()));
            else
                EXPECT_EQ(firstProbability[idx], thirdLevelElements[idx]->getData());
        }
    }
    {
        auto fourthLevelElements = levelOrder[3];
        std::vector<int> firstProbability = { 4, 9 };
        std::vector<int> secondProbability = { 1, 9 };
        for (size_t idx = 0; idx < firstProbability.size(); idx++)
        {
            if (0 == idx)
                EXPECT_TRUE((firstProbability[idx] == fourthLevelElements[idx]->getData()) || (secondProbability[idx] == fourthLevelElements[idx]->getData()));
            else
                EXPECT_EQ(firstProbability[idx], fourthLevelElements[idx]->getData());
        }
    }
}

TEST_F(BSTTest, testDefaultConstructor)
{
    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_tree.getRoot());
    ASSERT_EQ(expectedVal, m_tree.size());
    ASSERT_EQ(expectedVal, m_tree.height());

    m_tree.insert(2);
    ASSERT_NE(nullptr, m_tree.getRoot());
    EXPECT_EQ(2, m_tree.getRoot()->getData());
    EXPECT_EQ(expectedVal + 1, m_tree.size());
    EXPECT_EQ(expectedVal + 1, m_tree.height());
}

TEST_F(BSTTest, testInsertItems)
{
    constexpr size_t expectedSize = 3;
    constexpr size_t expectedHeight = 2;
    m_tree.insert(2);
    m_tree.insert(3);
    m_tree.insert(1);

    ASSERT_NE(nullptr, m_tree.getRoot());
    EXPECT_EQ(expectedSize, m_tree.size());
    EXPECT_EQ(expectedHeight, m_tree.height());

    //Test the tree by traversing in pre order
    {
        auto items = getElementsPreOrder(m_tree);
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(2, items[0]);
        EXPECT_EQ(1, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing in order
    {
        auto items = getElementsInOrder(m_tree);
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(1, items[0]);
        EXPECT_EQ(2, items[1]);
        EXPECT_EQ(3, items[2]);
    }
    //Test the tree by traversing post order
    {
        auto items = getElementsPostOrder(m_tree);
        EXPECT_FALSE(items.empty());
        EXPECT_EQ(expectedSize, items.size());
        EXPECT_EQ(1, items[0]);
        EXPECT_EQ(3, items[1]);
        EXPECT_EQ(2, items[2]);
    }
}

TEST_F(BSTTest, testInitializerListConstructor)
{
    /*
        The purpose of this test case is to test
        initializer list constructor of the BST
        class which builds a balanced BST tree
        by calling internally makeTree method
    */
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);
}

TEST_F(BSTTest, testCopyConstructor)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    auto copyTree = tree;
    testTree(copyTree);
    testTree(tree);
}

TEST_F(BSTTest, testAssignment)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);
    
    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_tree.getRoot());
    ASSERT_EQ(expectedVal, m_tree.size());
    ASSERT_EQ(expectedVal, m_tree.height());

    m_tree = tree;
    testTree(m_tree);
}

TEST_F(BSTTest, testMoveConstructor)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);

    auto copyTree = std::move(tree);
    testTree(copyTree);

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());
}

TEST_F(BSTTest, testMoveAssignment)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, m_tree.getRoot());
    ASSERT_EQ(expectedVal, m_tree.size());
    ASSERT_EQ(expectedVal, m_tree.height());

    m_tree = std::move(tree);
    testTree(m_tree);

    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());
}

TEST_F(BSTTest, testClearTree)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);

    tree.clear();

    constexpr size_t expectedVal = 0;
    ASSERT_EQ(nullptr, tree.getRoot());
    ASSERT_EQ(expectedVal, tree.size());
    ASSERT_EQ(expectedVal, tree.height());

}

TEST_F(BSTTest, testErase)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);

    constexpr size_t originalSize = 9;

    EXPECT_NE(tree.find(5), nullptr);
    EXPECT_EQ(originalSize, tree.size());

    tree.erase(5);

    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_EQ(originalSize - 1, tree.size());
}
