#include <iostream>
#include <climits>
#include <string>

template <typename T>
Dijkstra<T>::Dijkstra(const Graph<T>& graph) : graph(graph) {}

template <typename T>
Dijkstra<T>::~Dijkstra() {
    delete[] parent;
    delete[] distance;
    delete[] sptSet;
}

template <typename T>
void Dijkstra<T>::dijkstraAdjacencyList(int startingVertex) {
    this->startingVertex = startingVertex;

    parent = new int[graph.getVerticesNumber()];
    distance = new int[graph.getVerticesNumber()];
    sptSet = new bool[graph.getVerticesNumber()];

    MinHeap<T> heap(graph);

    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
        sptSet[i] = false;
    }

    heap.add(new Edge<T>(0, startingVertex, 0));
    distance[startingVertex] = 0;

    while (!heap.isEmpty()) {
        Edge<T> vertex = heap.poll();
        if (sptSet[vertex.destination])
            continue;
        sptSet[vertex.destination] = true;

        auto neighbour = graph.getAdjacencyList()[vertex.destination].head;
        while (neighbour != graph.getNullEdge()) {
            if (!sptSet[neighbour->destination]) {
                relax(neighbour->source, neighbour->destination, neighbour->weight, heap);
            }
            neighbour = neighbour->next;
        }
    }

    print();
}

template <typename T>
void Dijkstra<T>::dijkstraAdjacencyMatrix(int startingVertex) {
    this->startingVertex = startingVertex;

    parent = new int[graph.getVerticesNumber()];
    distance = new int[graph.getVerticesNumber()];
    sptSet = new bool[graph.getVerticesNumber()];

    MinHeap<T> heap(graph);

    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        parent[i] = i;
        distance[i] = INT_MAX;
        sptSet[i] = false;
    }

    heap.add(new Edge<T>(0, startingVertex, 0));
    distance[startingVertex] = 0;

    while (!heap.isEmpty()) {
        Edge<T> vertex = heap.poll();
        if (sptSet[vertex.destination])
            continue;
        sptSet[vertex.destination] = true;

        for (int j = 0; j < graph.getVerticesNumber(); ++j) {
            auto neighbour = graph.getAdjacencyMatrix()[vertex.destination][j];
            if (neighbour != graph.getNullEdge() && !sptSet[neighbour->destination]) {
                relax(neighbour->source, neighbour->destination, neighbour->weight, heap);
            }
        }
    }

    print();
}

template <typename T>
void Dijkstra<T>::relax(int u, int v, int weight, MinHeap<T>& heap) {
    if (distance[v] > distance[u] + weight) {
        distance[v] = distance[u] + weight;
        parent[v] = u;
        heap.add(new Edge<T>(0, v, distance[v]));
    }
}

template <typename T>
void Dijkstra<T>::print() {
    std::cout << "\nPaths from vertex " << startingVertex << ":\n";
    for (int i = 0; i < graph.getVerticesNumber(); ++i) {
        if (i == startingVertex) continue;

        std::string path = std::to_string(i);
        int vertex = i;

        while (parent[vertex] != vertex) {
            path = std::to_string(parent[vertex]) + "->" + path;
            vertex = parent[vertex];
        }

        std::cout << path << " Distance: " << distance[i] << "\n";
    }
}
