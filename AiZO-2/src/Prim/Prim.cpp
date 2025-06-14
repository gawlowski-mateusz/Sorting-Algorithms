#include <iostream>
#include <iomanip>
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
    std::cout << "Minimum Spanning Tree Edges:\n";
    std::cout << std::setw(5) << "Src" 
              << std::setw(6) << "Dst" 
              << std::setw(9) << "Weight\n";
    std::cout << "---------------------------\n";

    int totalWeight = 0;
    int V = graph.getVerticesNumber();

    for (int i = 0; i < V - 1; ++i) {
        std::cout << std::setw(5) << edgesIncluded[i].src
                  << std::setw(6) << edgesIncluded[i].dst
                  << std::setw(8) << edgesIncluded[i].weight << "\n";
        totalWeight += edgesIncluded[i].weight;
    }

    std::cout << "---------------------------\n";
    std::cout << "Total Weight of MST: " << totalWeight << "\n";
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
