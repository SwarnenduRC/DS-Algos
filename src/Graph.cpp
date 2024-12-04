#include "Graph.hpp"

#include <queue>
#include <stack>

using swarnendu::Graph;

Graph::Graph(const std::vector<StdPair>& data, const bool zeroBased)
{
    fill(data, zeroBased);
}

Graph::Graph(Graph&& rhs) noexcept
    : m_nodeCnt(rhs.m_nodeCnt)
    , m_edgeCnt(rhs.m_edgeCnt)
    , m_bZeroBased(rhs.m_bZeroBased)
    , m_adjacencyMatrix(std::move(rhs.m_adjacencyMatrix))
{
    rhs.m_nodeCnt = 0;
    rhs.m_edgeCnt = 0;
    rhs.m_bZeroBased = false;
}

Graph& Graph::operator=(Graph&& rhs) noexcept
{
    if (this != &rhs)
    {
        m_nodeCnt = rhs.m_nodeCnt;
        m_edgeCnt = rhs.m_edgeCnt;
        m_bZeroBased = rhs.m_bZeroBased;
        m_adjacencyMatrix = std::move(rhs.m_adjacencyMatrix);

        rhs.m_nodeCnt = 0;
        rhs.m_edgeCnt = 0;
        rhs.m_bZeroBased = false;
    }
    return *this;
}

void Graph::fill(const std::vector<StdPair>& data, const bool zeroBased)
{
    if (data.empty() || data.size() < 2)
        return;

    /**
         * @brief The first element of the vector depicts a pair of total no of
         * nodes and the edges present in the graph, e.g; the graph represented
         * by this data object having total 10 nodes and 7 edges (a connection)
         * between each two nodes is called an edge. In all Leetcode/Hackerrank
         * problems a graph is described in this way only. The subsequent elements
         * of the vector depicts each edge or the connections between various nodes.
         * A zero based graph means that the node 0 should not be counted for the
         * purposes of indexing
         *
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
         */
    m_nodeCnt = static_cast<size_t>(data[0].first);
    m_edgeCnt = static_cast<size_t>(data[0].second);
    m_bZeroBased = zeroBased;
    
    size_t idx = 1; // It is 1 because the first index of the data vector which is 0 represents node and edge counts.
    if (m_bZeroBased)
    {
        m_adjacencyMatrix.resize(m_nodeCnt);    //Setting the matrix size equals to total nodes available.
    }
    else
    {
        m_adjacencyMatrix.resize(m_nodeCnt + 1);    //If it is a non zero based array then total indexes should be total node cnt + 1
        m_adjacencyMatrix[0].resize(0); //No neighbours for the node 0 for non zero based matrix
    }
    while (idx < data.size())   // Loop through the data vector populate the matrix
    {
        auto node = data[idx].first;
        auto neighbour = data[idx].second;
        m_adjacencyMatrix[node].emplace_back(neighbour);
        m_adjacencyMatrix[neighbour].emplace_back(node);
        ++idx;
    }
}

void Graph::clear() noexcept
{
    if (!m_adjacencyMatrix.empty())
    {
        for (auto& neighbours : m_adjacencyMatrix)
            neighbours.clear();

        m_adjacencyMatrix.clear();        
    }
}

void Graph::addEdge(const StdPair& data) noexcept
{
    if (!m_adjacencyMatrix.empty() && 
        data.first <= static_cast<int>(m_adjacencyMatrix.size()) && 
        data.second <= static_cast<int>(m_adjacencyMatrix.size()))
    {
        if (std::find(m_adjacencyMatrix[data.first].cbegin(), m_adjacencyMatrix[data.first].cend(), data.second) 
            == m_adjacencyMatrix[data.first].cend())
        {
            auto node = data.first;
            auto neighbour = data.second;
            m_adjacencyMatrix[node].emplace_back(neighbour);
            m_adjacencyMatrix[neighbour].emplace_back(node);
            ++m_edgeCnt;
        }
    }
}

void Graph::addEdges(const std::vector<StdPair>& data) noexcept
{
    if (!data.empty() && !m_adjacencyMatrix.empty())
    {
        for (const auto& dataItm : data)
            addEdge(dataItm);
    }
}

void Graph::removeEdge(const StdPair& data) noexcept
{
    if (!m_adjacencyMatrix.empty())
    {
        auto secondNode = std::find(m_adjacencyMatrix[data.first].cbegin(), m_adjacencyMatrix[data.first].cend(), data.second);
        auto firstNode = std::find(m_adjacencyMatrix[data.second].cbegin(), m_adjacencyMatrix[data.second].cend(), data.first);
        
        if (secondNode != m_adjacencyMatrix[data.first].cend() && firstNode != m_adjacencyMatrix[data.second].cend())
        {
            m_adjacencyMatrix[data.first].erase(secondNode);
            m_adjacencyMatrix[data.second].erase(firstNode);
            --m_edgeCnt;
        }
    }
}

void Graph::removeEdges(const std::vector<StdPair>& data) noexcept
{
    if (!data.empty() && !m_adjacencyMatrix.empty())
    {
        for (const auto& dataItm : data)
            removeEdge(dataItm);
    }
}

std::vector<int> Graph::getBFSList() const noexcept
{
    if (!getNodeCnt() || !getEdgeCnt())
        return std::vector<int>{};

    std::queue<int> nodeQ;
    std::vector<int> outVec;
    auto arrSize = m_adjacencyMatrix.size();
    bool visitedArr[arrSize];
    std::fill(visitedArr, visitedArr + arrSize, false);
    size_t idx = m_bZeroBased ? 0 : 1;
    nodeQ.push(idx);

    while (idx < arrSize)
    {
        while (!nodeQ.empty())
        {
            auto data = nodeQ.front();
            nodeQ.pop();
            if (!visitedArr[data])
            {
                visitedArr[data] = true;
                outVec.emplace_back(data);
            }
            for (const auto& neighbours : m_adjacencyMatrix[data])
            {
                if (!visitedArr[neighbours])
                    nodeQ.push(neighbours);
            }
        }
        ++idx;
        if (!visitedArr[idx])
            nodeQ.push(idx);
    }
    return outVec;
}

std::vector<int> Graph::getDFSList() const noexcept
{
    if (!getNodeCnt() || !getEdgeCnt())
        return std::vector<int>{};

    std::stack<int> nodeStack;
    std::vector<int> outVec;
    auto arrSize = m_adjacencyMatrix.size();
    bool visitedArr[arrSize];
    std::fill(visitedArr, visitedArr + arrSize, false);
    size_t idx = m_bZeroBased ? 0 : 1;
    nodeStack.push(idx);

    while (idx < arrSize)
    {
        while (!nodeStack.empty())
        {
            auto data = nodeStack.top();
            nodeStack.pop();
            if (!visitedArr[data])
            {
                visitedArr[data] = true;
                outVec.emplace_back(data);
            }
            for (const auto& neighbours : m_adjacencyMatrix[data])
            {
                if (!visitedArr[neighbours])
                    nodeStack.push(neighbours);
            }
        }
        ++idx;
        if (!visitedArr[idx])
            nodeStack.push(idx);
    }
    return outVec;
}

