#ifndef UTILITY_NETWORK_H
#define UTILITY_NETWORK_H

#include <vector>
#include <map>
#include <string>

class UtilityNetwork {
public:
    UtilityNetwork(const std::string &type);
    void addNode(int id, const std::string &name);
    void addEdge(int from, int to, double length);
    void generateNetwork(int nodes, int edges);
    void printNetwork() const;

private:
    std::string networkType;

    struct Node {
        int id;
        std::string name;
    };

    struct Edge {
        int from;
        int to;
        double length;
    };

    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::map<int, std::vector<Edge>> adjacencyList;
};

#endif // UTILITY_NETWORK_H
