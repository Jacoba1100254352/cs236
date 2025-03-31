#ifndef PROJECT_3_DATABASE_H
#define PROJECT_3_DATABASE_H

#include "Relation.h"
#include <map>

class Database {
public:
	///   Get Map Functions   ///
	Relation& getRelationByRef(const std::string& relName) {
		return dataMap.at(relName);
	}
	Relation getRelationCopy(const std::string& relName) {
		return dataMap.at(relName);
	}

	///   Insert Functions   ///
	void insert(const Relation& r) {
		dataMap.insert({r.getName(), r});
	}

	///   Size Functions   ///
	unsigned size() { // can also be called numTuples
		unsigned i = 0;
		for (const std::pair<const std::string, Relation>& p : dataMap)
			i += p.second.size();
		return i;
	}

	///   Print Function   ///
	std::string toString() {
		std::stringstream out;
		for (std::pair<std::string, Relation> relationEntry : dataMap)
			out << relationEntry.first << std::endl << relationEntry.second.toString();
		return out.str();
	}

	/************************
	*   PRIVATE VARIABLES   *
	************************/
private:
	std::map<std::string, Relation> dataMap;
};


#endif //PROJECT_3_DATABASE_H
