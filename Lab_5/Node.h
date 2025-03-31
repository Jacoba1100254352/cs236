#ifndef LAB_5_NODE_H
#define LAB_5_NODE_H

#include <set>
#include <sstream>

class Node {
public:
    void addEdge(unsigned adjacentNodeID) {
        adjacentNodeIDs.insert(adjacentNodeID);
    }
    void markVisited() {
        visited = true;
    }
    void addPostorderNumber(unsigned poNumber) {
        postorderNumber = poNumber;
        if (!visited) throw std::logic_error("Node should have been marked visited first");
    }
    std::string toString() const {
        std::stringstream out;
        for (const unsigned & nodeID : adjacentNodeIDs)
            out << "R" << nodeID << ((&nodeID != &*(--adjacentNodeIDs.end())) ? "," : "");
        return out.str();
    }

private:
    std::set<unsigned> adjacentNodeIDs;
    bool visited = false;
    unsigned postorderNumber = 0;
};


#endif //LAB_5_NODE_H
