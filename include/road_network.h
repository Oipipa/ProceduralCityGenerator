#ifndef ROAD_NETWORK_H
#define ROAD_NETWORK_H

#include <vector>
#include <map>
#include <string>

class RoadNetwork {
public:
    RoadNetwork();
    void addNode(int id, const std::string &name);
    void addEdge(int from, int to, double length);
    void generateNetwork(int nodes, int edges);
    void printNetwork() const;

private:
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
};

#endif // ROAD_NETWORK_H
