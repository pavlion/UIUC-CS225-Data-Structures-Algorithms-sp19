/* Your code here! */
/**
 * @file dsets.h
 * Implementation of Disjoint Sets.
 */

#include "dsets.h"
#include <iostream>

using std::cout;
using std::endl;

void DisjointSets::addelements(int num){
	for (int i=0; i<num; ++i)
		elems.push_back(-1);
}
	
int DisjointSets::find(int elem){
	if ( elems[elem] < 0) return elem;
	
	//path compression
	int root = find( elems[elem] );
	elems[elem] = root;
	return root;
}

void DisjointSets::setunion(int a,int b){
	int root1 = find(a);
	int root2 = find(b);
	int newSize = elems[root1] + elems[root2];// should be negative
	
	// root1 has more nodes: since we store the negative height in the array.
	if (elems[root1] <= elems[root2]){ 
		elems[root2] = root1;
		elems[root1] = newSize;
	}
	
	else{
		elems[root1] = root2;
		elems[root2] = newSize;
	}
}

int DisjointSets::size(int elem){
	int root = find(elem);
	return -elems[root];
}