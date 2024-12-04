#include "GraphProblemsTest.hpp"

#include <queue>
#include <stack>
#include <array>

bool GraphAlgos::isThereRoute(const Graph& graph, const int firstNode, const int secondNode) noexcept
{
    auto adjMatrix = graph.getAdjMatrix();
    if (adjMatrix.empty())
        return false;

    auto totalNodeCnt = adjMatrix.size();
    auto findViaBFS = [&](const int firstNode, const int secondNode)
    {
        std::queue<int> nodesQueue;
        bool visitedNodesArr[totalNodeCnt];
        std::fill(visitedNodesArr, visitedNodesArr + totalNodeCnt, false);  //Set all false before start visiting nodes
        nodesQueue.push(firstNode);

        while (!nodesQueue.empty())
        {
            auto node = nodesQueue.front();
            nodesQueue.pop();
            if (visitedNodesArr[node] == false)
            {
                visitedNodesArr[node] = true;
                if (node == secondNode)
                    return true;

                for (const auto neighbours : adjMatrix[node])
                    nodesQueue.push(neighbours);
            }
        }
        return false;
    };
    auto findViaDFS = [&](const int firstNode, const int secondNode)
    {
        std::stack<int> nodesStack;
        bool visitedNodesArr[totalNodeCnt];
        std::fill(visitedNodesArr, visitedNodesArr + totalNodeCnt, false);  //Set all false before start visiting nodes
        nodesStack.push(firstNode);

        while (!nodesStack.empty())
        {
            auto node = nodesStack.top();
            nodesStack.pop();
            if (visitedNodesArr[node] == false)
            {
                visitedNodesArr[node] = true;
                if (node == secondNode)
                    return true;

                for (const auto neighbours : adjMatrix[node])
                    nodesStack.push(neighbours);
            }
        }
        return false;
    };
    return findViaBFS(firstNode, secondNode) && findViaDFS(firstNode, secondNode);
}

TEST_F(GraphAlgos, testRoute)
{
    {
        /**
         * @brief The first element of the vector depicts a pair of total no of
         * nodes and the edges present in the graph, e.g; the graph represented
         * by this data object having total 10 nodes and 7 edges (a connection)
         * between each two nodes is called an edge. In all Leetcode/Hackerrank
         * problems a graph is described in this way only. The subsequent elements
         * of the vector depicts each edge or the connections between various nodes.
         * A zero based graph means that the node 0 should not be counted for the
         * purposes of indexing
         */
        static std::vector<std::pair<int, int>> zeroBasedData = { 
                                                                    std::make_pair(10, 7),
                                                                    std::make_pair(1, 3),
                                                                    std::make_pair(2, 4),
                                                                    std::make_pair(5, 7),
                                                                    std::make_pair(6, 8),
                                                                    std::make_pair(9, 0),
                                                                    std::make_pair(8, 4),
                                                                    std::make_pair(6, 9)
                                                                };

        Graph graph(zeroBasedData);
        EXPECT_TRUE(isThereRoute(graph, 2, 9));
    }
    {
        /**
         * @brief The first element of the vector depicts a pair of total no of
         * nodes and the edges present in the graph, e.g; the graph represented
         * by this data object having total 10 nodes and 6 edges (a connection)
         * between each two nodes is called an edge. In all Leetcode/Hackerrank
         * problems a graph is described in this way only. The subsequent elements
         * of the vector depicts each edge or the connections between various nodes.
         * A zero based graph means that the node 0 should not be counted for the
         * purposes of indexing
         */
        static std::vector<std::pair<int, int>> zeroBasedData = { 
                                                                    std::make_pair(10, 6),
                                                                    std::make_pair(1, 3),
                                                                    std::make_pair(2, 4),
                                                                    std::make_pair(5, 7),
                                                                    std::make_pair(6, 8),
                                                                    std::make_pair(9, 0),
                                                                    std::make_pair(8, 4)
                                                                };

        Graph graph(zeroBasedData);
        EXPECT_FALSE(isThereRoute(graph, 2, 9));
    }
}