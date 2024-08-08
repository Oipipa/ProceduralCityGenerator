#include "utility_network.h"
#include <iostream>
#include <cstdlib>

UtilityNetwork::UtilityNetwork(const std::string &type) : networkType(type) {}

void UtilityNetwork::addNode(int id, const std::string &name) {
    nodes.push_back({id, name});
}

void UtilityNetwork::addEdge(int from, int to, double length) {
    edges.push_back({from, to, length});
    adjacencyList[from].push_back({from, to, length});
    adjacencyList[to].push_back({to, from, length}); // Assuming undirected graph for simplicity
}

void UtilityNetwork::generateNetwork(int nodes, int edges) {
    for (int i = 0; i < nodes; ++i) {
        addNode(i, networkType + " Node " + std::to_string(i));
    }

    for (int i = 0; i < edges; ++i) {
        int from = rand() % nodes;
        int to;
        do {
            to = rand() % nodes;
        } while (to == from);
        double length = rand() % 100 + 1;
        addEdge(from, to, length);
    }
}

void UtilityNetwork::printNetwork() const {
    std::cout << networkType << " Network:" << std::endl;
    for (const auto &node : nodes) {
        std::cout << "Node " << node.id << ": " << node.name << std::endl;
        for (const auto &edge : adjacencyList.at(node.id)) {
            std::cout << "  connects to Node " << edge.to << " with length " << edge.length << std::endl;
        }
    }
}
