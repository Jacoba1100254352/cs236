#pragma once

#include <set>

#ifndef LAB_5_NODE_H
#define LAB_5_NODE_H

#include <set>
#include <sstream>

class Node {
public:
	Node() = default;

	void addEdge(unsigned adjacentNodeID) {
		adjacentNodeIDs.insert(adjacentNodeID);
	}
	const std::set<unsigned>& getAdjacentNodeIDs() const {
		return adjacentNodeIDs;
	}

	void markVisited() {
		visited = true;
	}
	bool isVisited() const {
		return visited;
	}

	std::string toString() const {
		std::stringstream out;
		for (const unsigned& ID : adjacentNodeIDs)
			out << "R" << ID << ((&ID != &*(--adjacentNodeIDs.end())) ? "," : "");
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::set<unsigned> adjacentNodeIDs;
	bool visited = false;
};


#endif //LAB_5_NODE_H
