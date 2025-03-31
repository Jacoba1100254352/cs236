#ifndef LAB_5_GRAPH_H
#define LAB_5_GRAPH_H

#include <map>
#include <stack>

#include "Node.h"
#include "DatalogProgram.h"

class Graph {
public:
	///   Constructor   ///
	explicit Graph(unsigned size) {
		for (unsigned nodeID = 0; nodeID < size; nodeID++)
			nodes[nodeID] = Node();
	}

	///   Add Edge Function   ///
	void addEdge(unsigned fromNodeID, unsigned toNodeID) {
		nodes.at(fromNodeID).addEdge(toNodeID);
	}

	// REVERSE Graph
	void DFS(unsigned startNode) {
		if (nodes.at(startNode).isVisited())
			return;

		nodes.at(startNode).markVisited();
		for (const unsigned& child : nodes.at(startNode).getAdjacentNodeIDs())
			if (!nodes.at(child).isVisited())
				DFS(child);

		workingStack.push(startNode);
	}
	std::stack<unsigned> DFSForrest() {
		// Find groups by traveling down lines until all have groups with visited
		for (unsigned startNode = 0; startNode < nodes.size(); startNode++)
			if (!nodes.at(startNode).isVisited())
				DFS(startNode);

		return workingStack;
	}

	// FORWARD Graph
	std::set<unsigned> DFS_SCC(unsigned startNode) {
		if (nodes.at(startNode).isVisited())
			return {};

		std::set<unsigned> result;

		nodes.at(startNode).markVisited();
		result.insert(startNode);
		for (const unsigned& child : nodes.at(startNode).getAdjacentNodeIDs())
			if (!nodes.at(child).isVisited()) {
				std::set<unsigned> tempResult = DFS_SCC(child);
				result.insert(tempResult.begin(), tempResult.end());
			}

		workingStack.push(startNode);
		return result;
	}
	std::vector<std::set<unsigned>> DFSForrest_SCC(std::stack<unsigned> priorQueue) { // pass in DFSForrest as argument
		std::set<unsigned> result;
		std::vector<std::set<unsigned>> SCCs;
		while (!priorQueue.empty()) {
			unsigned top = priorQueue.top();
			if (!nodes.at(top).isVisited()) {
				std::set<unsigned> tempResult = DFS_SCC(top);
				result.insert(tempResult.begin(), tempResult.end());
			} else {
				SCCs.push_back(result);
				result.clear();
				priorQueue.pop();
			}
		}
		return SCCs;
	}

	///   Print Function   ///
	std::string toString() {
		std::stringstream out;
		out << "Dependency Graph\n";
		for (const std::pair<const unsigned, Node>& pair : nodes)
			out << 'R' << pair.first << ':' << pair.second.toString() << '\n';
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::map<unsigned, Node> nodes;
	std::stack<unsigned> workingStack{};
};


#endif //LAB_5_GRAPH_H
