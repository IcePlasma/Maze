#ifndef DISJSET_H
#define DISJSET_H

#include "define.h"
#include <iostream>
using namespace std;
class disjSet
{
public:
	disjSet(int, int);
	~disjSet();

	//Mutator for value in a node.
	void changeValue(char newValue, int index)
	{
		(sets + index)->value += newValue;
	}
	//Union by rank. The ints that are passed to this function represent the index of a node in a set that is being united.
	bool unionDisjSet(int, int);
	//Accessor for value in a node.
	char getValue(int index) const
	{
		return (sets + index)->value;
	}


private:
	//These are the nodes that represent disjoint sets.
	struct nodey
	{
		char value;
		int rank, parentIndex;
	};
	nodey* sets;

	//find with path compression.
	int find(int& current);
};

#endif
