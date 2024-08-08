#include "road_network.h"
#include <iostream>
#include <cstdlib>

RoadNetwork::RoadNetwork() {}

void RoadNetwork::addNode(int id, const std::string &name) {
    nodes.push_back({id, name});
}

void RoadNetwork::addEdge(int from, int to, double length) {
    edges.push_back({from, to, length});
}

void RoadNetwork::generateNetwork(int nodesCount, int edgesCount) {
    // Add nodes
    for (int i = 0; i < nodesCount; ++i) {
        addNode(i, "Node " + std::to_string(i));
    }

    // Add edges
    for (int i = 0; i < edgesCount; ++i) {
        int from = rand() % nodesCount;
        int to = rand() % nodesCount;
        double length = rand() % 100 + 1;
        addEdge(from, to, length);
    }
}

void RoadNetwork::printNetwork() const {
    for (const auto &node : nodes) {
        std::cout << "Node " << node.id << ": " << node.name << std::endl;
        for (const auto &edge : edges) {
            if (edge.from == node.id) {
                std::cout << "  connects to Node " << edge.to << " with length " << edge.length << std::endl;
            }
        }
    }
}
