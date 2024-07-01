#include "Graph.h"

#include <gtest/gtest.h>

using swarnendu::Graph;

class GraphAlgos : public ::testing::Test
{
    public:
        /**
         * @brief Route Between Nodes
         * Given a directed graph, design an algorithm to find out whether there is a
         * route between two nodes.
         */
        static bool isThereRoute(const Graph& graph, const int firstNode, const int secondNode) noexcept;
};