#include <iostream>
#include "Prim.h"
#include "../Graph/Graph.h"
#include "../MinHeap/MinHeap.h"

Prim::Prim(Graph graph) {
	this->graph = graph;
}

void Prim::primAdjacencyList() {
	Edge edgesIncluded[graph.getVerticesNumber() - 1];
	int mstSet[graph.getVerticesNumber()];
	for (int i = 0; i < graph.getVerticesNumber(); i++)
		mstSet[i] = false;
	MinHeap minHeap(graph);
	int lastAddedVertex = 0;
	Edge addedEdge;
	for (int i = 0; i < graph.getVerticesNumber() - 1; i++) {
		auto vEdges = graph.getAdjacencyList()[lastAddedVertex].head;
		for (int v = 0; vEdges != graph.getNullEdge(); v++) {
			if (mstSet[vEdges->dst] == false && vEdges->weight > 0)
				minHeap.add(vEdges);
			vEdges = vEdges->next;
		}
		mstSet[lastAddedVertex] = true;
		do {
			addedEdge = minHeap.poll();
		} while (mstSet[addedEdge.dst] == true);
		lastAddedVertex = addedEdge.dst;
		edgesIncluded[i] = addedEdge;
	}
	printMST(edgesIncluded);
}


void Prim::printMST(Edge edgesIncluded[]) {
	std::printf("Src|Dst|Wght\n");
	for (int i = 0; i < graph.getVerticesNumber() - 1; ++i) {
		std::printf("  %d|  %d|   %d\n", edgesIncluded[i].src, edgesIncluded[i].dst, edgesIncluded[i].weight);
	}
	int result =0;
	for (int i = 0; i < graph.getVerticesNumber()-1; ++i) {
		result+=edgesIncluded[i].weight;
	}
	std::cout<<result<<std::endl;
}


void Prim::primAdjacencyMatrix() {
	Edge edgesIncluded[graph.getVerticesNumber() - 1];
	int mstSet[graph.getVerticesNumber()];
	for (int i = 0; i < graph.getVerticesNumber(); i++)
		mstSet[i] = false;
	MinHeap minHeap(graph);
	int lastAddedVertex = 0;
	Edge addedEdge;
	for (int i = 0; i < graph.getVerticesNumber() - 1; i++) {
		auto vEdges = graph.getAdjacencyMatrix()[lastAddedVertex];
		for (int v = 0; v < graph.getVerticesNumber(); v++) {
			if (mstSet[v] == false && vEdges[v]->weight > 0)
				minHeap.add(vEdges[v]);
		}
		mstSet[lastAddedVertex] = true;
		do {
			addedEdge = minHeap.poll();
		} while (mstSet[addedEdge.dst] == true);
		lastAddedVertex = addedEdge.dst;
		edgesIncluded[i] = addedEdge;
	}

	printMST(edgesIncluded);
}
