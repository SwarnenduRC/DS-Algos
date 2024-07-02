#include "BSTreeProblems.hpp"

using VecOfList = std::vector<std::list<TreeNode*>>;

/*static*/ VecOfList BSTreeProblems::createLinkedListAtEachLevel(const BSTree& tree) noexcept
{
    if (tree.empty())
        return VecOfList{};

    VecOfList retVal{};

    std::list<TreeNode*> currLvlNodes = {tree.getRoot()};
    while (!currLvlNodes.empty())
    {
        retVal.emplace_back(currLvlNodes);
        auto parentLvlNodes = currLvlNodes;
        currLvlNodes.clear();
        for (const auto& pNode : parentLvlNodes)
        {
            if (pNode->m_pLeft)
                currLvlNodes.emplace_back(pNode->m_pLeft.get());
            
            if (pNode->m_pRight)
                currLvlNodes.emplace_back(pNode->m_pRight.get());
        }
    }
    return retVal;
}

TEST_F(BSTreeProblems, testListOfDepth)
{
    std::initializer_list<int> iList = { 5, 3, 7, 2, 4, 6, 8, 1, 9 };
    BSTree tree(iList);
    testTree(tree);

    /**
     * @see BSTTest::testTree
     * for details baout how level order traversal is verified
     */
    auto levelOrder = getElementsLevelOrder(tree);
    auto levelOrderList = createLinkedListAtEachLevel(tree);
    ASSERT_EQ(levelOrder.size(), levelOrderList.size());

    EXPECT_EQ(static_cast<int>(levelOrderList[0].size()), 1);
    EXPECT_EQ(static_cast<int>(levelOrderList[1].size()), 2);
    EXPECT_EQ(static_cast<int>(levelOrderList[2].size()), 4);
    EXPECT_EQ(static_cast<int>(levelOrderList[3].size()), 2);

    EXPECT_EQ(levelOrderList[0].front()->getData(), 5);
    
    {
        auto secondLevelElements = levelOrderList[1];
        std::list<int> firstProbability = { 3, 7 };
        std::list<int> secondProbability = { 2, 7 };

        auto itrSecondLevelElements = secondLevelElements.begin();
        auto itrFirstProbability = firstProbability.begin();
        auto itrSecondProbability = secondProbability.begin();

        while (itrSecondLevelElements != secondLevelElements.end() && 
                itrFirstProbability != firstProbability.end() &&
                itrSecondProbability != secondProbability.end())
        {
            ASSERT_NE(*itrSecondLevelElements, nullptr);
            EXPECT_TRUE(((*itrSecondLevelElements)->getData() == *itrFirstProbability) || ((*itrSecondLevelElements)->getData() == *itrSecondProbability));

            ++itrSecondLevelElements;
            ++itrFirstProbability;
            ++itrSecondProbability;
        }
    }
    {
        auto thirdLevelElements = levelOrderList[2];
        std::list<int> firstProbability = { 2, 4, 6, 8 };
        std::list<int> secondProbability = { 1, 3, 6, 8 };

        auto itrThirdLevelElements = thirdLevelElements.begin();
        auto itrFirstProbability = firstProbability.begin();
        auto itrSecondProbability = secondProbability.begin();

        while (itrThirdLevelElements != thirdLevelElements.end() && 
                itrFirstProbability != firstProbability.end() &&
                itrSecondProbability != secondProbability.end())
        {
            ASSERT_NE(*itrThirdLevelElements, nullptr);
            EXPECT_TRUE(((*itrThirdLevelElements)->getData() == *itrFirstProbability) || ((*itrThirdLevelElements)->getData() == *itrSecondProbability));

            ++itrThirdLevelElements;
            ++itrFirstProbability;
            ++itrSecondProbability;
        }
    }
    {
        auto fourthLevelElements = levelOrderList[3];
        std::list<int> firstProbability = { 4, 9 };
        std::list<int> secondProbability = { 1, 9 };

        auto itrFourthLevelElements = fourthLevelElements.begin();
        auto itrFirstProbability = firstProbability.begin();
        auto itrSecondProbability = secondProbability.begin();

        while (itrFourthLevelElements != fourthLevelElements.end() && 
                itrFirstProbability != firstProbability.end() &&
                itrSecondProbability != secondProbability.end())
        {
            ASSERT_NE(*itrFourthLevelElements, nullptr);
            EXPECT_TRUE(((*itrFourthLevelElements)->getData() == *itrFirstProbability) || ((*itrFourthLevelElements)->getData() == *itrSecondProbability));

            ++itrFourthLevelElements;
            ++itrFirstProbability;
            ++itrSecondProbability;
        }
    }
}
