#ifndef PRIM_H
#define PRIM_H


#include "../Graph/Graph.h"

class Prim {
public:
	Prim(Graph graph);

	Graph graph;
	void primAdjacencyMatrix();
	void primAdjacencyList();

	void printMST(Edge edgesIncluded[]);
};


#endif //PRIM_H
