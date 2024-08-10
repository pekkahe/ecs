#pragma once

#include <core/graph/Task.hpp>

#include <unordered_map>
#include <vector>

namespace ecs
{
    class Graph
    {
    public:
        using Node = Task*;

        Graph(const std::vector<Node>&)
        {
        }

        void addEdge(Node a, Node b);

        std::vector<Node> incoming(Node from) const;
        std::vector<Node> outgoing(Node from) const;
        std::vector<Node> roots() const; // Those with incoming.empty()

    private:
        size_t indexOf(Node v);

        bool hasEdge(Node a, Node b); // ?

        std::unordered_map<const char*, size_t> m_indexMap;

        std::vector<std::vector<Node>> m_adjacencyList;
    };
}