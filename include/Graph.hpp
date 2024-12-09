#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <vector>

namespace swarnendu
{
    using StdPair = std::pair<int, int>;
    using Matrix = std::vector<std::vector<int>>;
    class Graph
    {
        public:
            /**
             * @brief Construct a new Graph object (Default)
             *
             */
            Graph() = default;
            /**
             * @brief Destroy the Graph object (Default)
             *
             */
            ~Graph() = default;
            /**
             * @brief Copy Construct a new Graph object (Default)
             *
             * @param [in] rhs The object to be copied over
             */
            Graph(const Graph& rhs) = default;
            /**
             * @brief Assignment operator
             *
             * @param [in] rhs The object to be assigned to
             * @return Graph& The re assigned object
             */
            Graph& operator=(const Graph& rhs) = default;
            /**
             * @brief Move constructor of Graph object
             *
             * @param [inout] rhs The object to be moved out
             */
            Graph(Graph&& rhs) noexcept;
            /**
             * @brief Move assignment operator
             *
             * @param [inout] rhs The object to be moved out
             * @return Graph& The modified this pointer
             */
            Graph& operator=(Graph&& rhs) noexcept;
            /**
             * @brief Construct a new Graph object.
             *        Constructs a new graph from the input data
             *        which is a vector of pairs depicting the nodes
             *        interconnected.
             *
             * @param [in] data The input data comprising nodes and edges
             * @param [in] zeroBased Whether the matrix is starting at index 0 or not
             */
            Graph(const std::vector<StdPair>& data, const bool zeroBased = false);

            /**
             * @brief Fills the matrix with graph data.
             *        Fills the matrix with the data depicting
             *        the nodes and edges of the graph
             *
             * @param [in] data The input data comprising nodes and edges
             * @param [in] zeroBased Whether the matrix is starting at index 0 or not
             */
            void fill(const std::vector<StdPair>& data, const bool zeroBased = false);
            /**
             * @brief Clears the matrix aka graph
             *
             */
            void clear() noexcept;
            /**
             * @brief Adds an edge between two nodes.
             *        Adds an edge between two nodes passed
             *        as argument to the method.
             *
             * @param [in] data A std pair containg the nodes
             */
            void addEdge(const StdPair& data) noexcept;
            /**
             * @brief Add edges between nodes.
             *        Adds edges between various nodes.
             *
             * @param [in] data A vector of std pairs containg nodes
             */
            void addEdges(const std::vector<StdPair>& data) noexcept;
            /**
             * @brief Removes an edge between two nodes.
             *
             * @param [in] data A pair of nodes for which the edge between them.
             *                  has to be removed.
             */
            void removeEdge(const StdPair& data) noexcept;
            /**
             * @brief Removes edges between a list of nodes
             *
             * @param [in] data A list of nodes for which the edges connecting them have to be removed.
             */
            void removeEdges(const std::vector<StdPair>& data) noexcept;
            /**
             * @brief Returns the nodes of the graph in a Breadth-First-Search fashion
             *
             * @return std::vector<int> A list of nodes if we travel the graph in a BFS style
             */
            std::vector<int> getBFSList() const noexcept;
            /**
             * @brief Returns the nodes of the graph in a Depth-First-Search fashion
             *
             * @return std::vector<int> A list of nodes if we travel the graph in a DFS style
             */
            std::vector<int> getDFSList() const noexcept;

            inline size_t getNodeCnt()      const noexcept   { return m_nodeCnt;         }
            inline size_t getEdgeCnt()      const noexcept   { return m_edgeCnt;         }
            inline bool   zeroBased()       const noexcept   { return m_bZeroBased;      }
            inline Matrix getAdjMatrix()    const noexcept   { return m_adjacencyMatrix; }

        private:
            /**
             * @brief Nodes count of the matrix
             *        Represents total no of nodes in the matrix
             */
            size_t m_nodeCnt = 0;
            /**
             * @brief Edges count of the matrix
             *        Represents total no of edges in the matrix
             */
            size_t m_edgeCnt = 0;
            /**
             * @brief Depicts whether the matrix is zero based
             *        If the matrix is zero based
             */
            bool m_bZeroBased = false;
            /**
             * @brief The matrix itself
             *        A matrix or vector of vectors
             */
            Matrix m_adjacencyMatrix;
    };
}   // namespace swarnendu

#endif  // _GRAPH_H_