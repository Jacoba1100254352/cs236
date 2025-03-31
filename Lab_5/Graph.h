#ifndef LAB_5_GRAPH_H
#define LAB_5_GRAPH_H

#include <map>

#include "Node.h"

class Graph {
public:
    explicit Graph(unsigned size) {
        for (unsigned nodeID = 0; nodeID < size; nodeID++)
            nodes[nodeID] = Node();
    }
    void addEdge(unsigned fromNodeID, unsigned toNodeID) {
        nodes[fromNodeID].addEdge(toNodeID);
    }
    std::string toString() {
        std::stringstream out;
        for (const std::pair<const unsigned, Node> & pair : nodes)
            out << "R" << pair.first << ":" << pair.second.toString() << '\n';
        return out.str();
    }

private:
    std::map<unsigned,Node> nodes;
};


#endif //LAB_5_GRAPH_H
