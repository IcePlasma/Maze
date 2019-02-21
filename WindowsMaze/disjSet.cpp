#include "disjSet.h"

//Disjoint set that is implemented with an array and unioning by rank.
disjSet::disjSet(int numElements, int initial)
{
	//Creating the disjoint sets and initializing them to their default values.
	sets = new nodey[numElements];
	for (int x = 0; x < numElements; x++)
	{
		(sets + x)->parentIndex = -1;
		(sets + x)->value = initial;
		(sets + x)->rank = 0;
	}
}
disjSet::~disjSet()
{
	delete[] sets;
}

//This function finds the root of a set and is used to test whether two sets are disjoint. It returns the index of the 
//root. This function also has path compression implemented.
int disjSet::find(int& current)
{
	if((sets + current)->parentIndex != -1)
	{
		(sets + current)->parentIndex = find((sets + current)->parentIndex);
		return (sets + current)->parentIndex;
	}
	return current;
}


//This function unions two sets if they aren't in the same set. Returns true if a union was made.
bool disjSet::unionDisjSet(int set1, int set2)
{
	int temp1 = find(set1);
	int temp2 = find(set2);
	//Determines if nodes are in the same set.
	if (temp1 != temp2)
	{
		//Determines which set has a larger rank and unions the smaller rank to the larger one. 
		if ((sets + temp1)->rank == (sets + temp2)->rank)
		{
			(sets + temp2)->parentIndex = temp1;
			((sets + temp1)->rank)++;
		}
		else if ((sets + temp1)->rank > (sets + temp2)->rank)
		{
			(sets + temp2)->parentIndex = temp1;
		}
		else
		{
			(sets + temp1)->parentIndex = temp2;
		}
		return true;
	}
	else
	{
		return false;
	}
}
