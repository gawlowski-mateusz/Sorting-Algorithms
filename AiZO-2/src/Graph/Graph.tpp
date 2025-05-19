#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <string>

// Constructor
template <typename T>
Graph<T>::Graph() {
    vertices_number = 0;
    edge_number = 0;
    NULL_EDGE = new Edge<T>(0, 0, 0);
    NULL_EDGE->next = nullptr;
    adjacency_list = nullptr;
    adjacency_matrix = nullptr;
}

// Create graph structure with specified number of vertices
template <typename T>
void Graph<T>::createGraph(int vertices) {
    // Clean up existing graph if any
    // deleteGraph();
    
    NULL_EDGE = new Edge<T>(0, 0, 0);
    NULL_EDGE->next = nullptr;
    vertices_number = vertices;
    
    adjacency_list = new VertexList<T>[vertices];
    for (int i = 0; i < vertices; i++) {
        adjacency_list[i].head = NULL_EDGE;
    }

    adjacency_matrix = new Edge<T>**[vertices];
    for (int i = 0; i < vertices; i++) {
        adjacency_matrix[i] = new Edge<T>*[vertices];
    }

    for (int i = 0; i < vertices_number; i++) {
        for (int j = 0; j < vertices_number; j++) {
            adjacency_matrix[i][j] = NULL_EDGE;
        }
    }
}

// Add an undirected edge to the graph
template <typename T>
void Graph<T>::addUndirectedEdge(int src, int dst, T weight) {
    Edge<T>* previous_head;

    previous_head = adjacency_list[src].head;
    adjacency_list[src].head = new Edge<T>(src, dst, weight);
    adjacency_list[src].head->next = previous_head;

    previous_head = adjacency_list[dst].head;
    adjacency_list[dst].head = new Edge<T>(dst, src, weight);
    adjacency_list[dst].head->next = previous_head;

    adjacency_matrix[src][dst] = new Edge<T>(src, dst, weight);
    adjacency_matrix[dst][src] = new Edge<T>(dst, src, weight);
    edge_number += 2;
}

// Add a directed edge to the graph
template <typename T>
void Graph<T>::addDirectedEdge(int src, int dst, T weight) {
    Edge<T>* previous_head;

    previous_head = adjacency_list[src].head;
    adjacency_list[src].head = new Edge<T>(src, dst, weight);
    adjacency_list[src].head->next = previous_head;

    adjacency_matrix[src][dst] = new Edge<T>(src, dst, weight);
    edge_number += 1;
}

// Print the adjacency matrix representation
template <typename T>
void Graph<T>::printMatrix() {
    std::cout << std::endl << " ";

    for (int i = 0; i < vertices_number; ++i) {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < vertices_number; i++) {
        std::cout << i << "|";
        for (int j = 0; j < vertices_number; j++) {
            std::cout << adjacency_matrix[i][j]->weight << " ";
        }
        std::cout << std::endl;
    }
}

// Generate an undirected graph with given vertices and density
template <typename T>
void Graph<T>::generateUndirectedGraph(int numberOfVertices, int density) {
    std::srand(std::time(NULL));
    createGraph(numberOfVertices);

    double V = numberOfVertices;
    double D = density;
    double edgesToAdd = floor((V * (V - 1) * (D / 100)) / 2);
    
    for (int i = 0; i + 1 <= V - 1; ++i) {
        addUndirectedEdge(i, i + 1, static_cast<T>(std::rand() % 10 + 1));
    }
    
    int remainingEdges = edgesToAdd - numberOfVertices + 1;
    int src, dst;
    T wght;
    
    for (int i = 0; i < remainingEdges; ++i) {
        src = std::rand() % numberOfVertices;
        dst = std::rand() % numberOfVertices;
        
        if (adjacency_matrix[src][dst] != NULL_EDGE || src == dst) {
            i--;
            continue;
        }
        
        if (std::is_same<T, int>::value) {
            wght = static_cast<T>(std::rand() % 20 + 1);
        }
        else if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            wght = static_cast<T>((std::rand() % 2000 + 1) / 100.0);
        }
        else {
            wght = static_cast<T>(std::rand() % 20 + 1);
        }
        
        addUndirectedEdge(src, dst, wght);
    }
}

// Remove a directed edge from the graph
template <typename T>
bool Graph<T>::removeDirectedEdge(int src, int dst) {
    auto edge = adjacency_list[src].head;
    auto prevEdge = edge;
    
    while (edge->destination != dst && edge != NULL_EDGE) {
        prevEdge = edge;
        edge = edge->next;
    }
    
    if (edge == NULL_EDGE)
        return false;
        
    prevEdge->next = edge->next;
    delete edge;

    edge = adjacency_matrix[src][dst];
    adjacency_matrix[src][dst] = NULL_EDGE;
    delete edge;
    edge_number -= 1;
    
    return true;
}

// Remove an undirected edge from the graph
template <typename T>
bool Graph<T>::removeUndirectedEdge(int src, int dst) {
    if (removeDirectedEdge(src, dst)) {
        removeDirectedEdge(dst, src);
        return true;
    }
    return false;
}

// Generate a directed graph with given vertices and density
template <typename T>
void Graph<T>::generateDirectedGraph(int number_of_vertices, int density) {
    std::srand(std::time(NULL));
    createGraph(number_of_vertices);
    
    double V = number_of_vertices;
    double D = density;
    double edges_to_add = 2 * floor((V * (V - 1) * (D / 100)) / 2);

    for (int i = 0; i + 1 <= V - 1; ++i) {
        addDirectedEdge(i, i + 1, static_cast<T>(std::rand() % 10 + 1));
    }

    int edges_remaining = edges_to_add - number_of_vertices + 1;
    int source, destination;
    T weight;

    for (int i = 0; i < edges_remaining; ++i) {
        source = std::rand() % number_of_vertices;
        destination = std::rand() % number_of_vertices;
        
        if (adjacency_matrix[source][destination] != NULL_EDGE || source == destination) {
            i--;
            continue;
        }
        
        if (std::is_same<T, int>::value) {
            weight = static_cast<T>(std::rand() % 20 + 1);
        }
        else if (std::is_same<T, float>::value || std::is_same<T, double>::value) {
            weight = static_cast<T>((std::rand() % 2000 + 1) / 100.0);
        }
        else {
            weight = static_cast<T>(std::rand() % 20 + 1);
        }
        
        addDirectedEdge(source, destination, weight);
    }
}

// Print the entire graph (both list and matrix representations)
template <typename T>
void Graph<T>::print() {
    printList();
    printMatrix();
}

// Print the adjacency list representation
template <typename T>
void Graph<T>::printList() {
    Edge<T>* edge_vertex;
    
    for (int i = 0; i < vertices_number; i++) {
        std::cout << std::endl << i << '|';
        edge_vertex = adjacency_list[i].head;
        
        while (edge_vertex != NULL_EDGE) {
            std::cout << "->[" << edge_vertex->destination << " " << edge_vertex->weight << "]";
            edge_vertex = edge_vertex->next;
        }
    }
    
    std::cout << std::endl;
}

// Delete the adjacency list
template <typename T>
void Graph<T>::deleteList() {
    if (!adjacency_list) return;
    
    for (int i = 0; i < vertices_number; ++i) {
        Edge<T>* previous_head;
        
        while (adjacency_list[i].head != NULL_EDGE) {
            previous_head = adjacency_list[i].head;
            adjacency_list[i].head = adjacency_list[i].head->next;
            delete previous_head;
        }
    }
    
    delete[] adjacency_list;
    adjacency_list = nullptr;
}

// Delete the adjacency matrix
template <typename T>
void Graph<T>::deleteMatrix() {
    if (!adjacency_matrix) return;
    
    for (int i = 0; i < vertices_number; ++i) {
        for (int j = 0; j < vertices_number; ++j) {
            if (adjacency_matrix[i][j] != NULL_EDGE) {
                delete adjacency_matrix[i][j];
            }
        }
        delete[] adjacency_matrix[i];
    }
    
    delete[] adjacency_matrix;
    adjacency_matrix = nullptr;
}

// Delete the entire graph
template <typename T>
void Graph<T>::deleteGraph() {
    deleteList();
    deleteMatrix();
    delete NULL_EDGE;
    NULL_EDGE = nullptr;
    vertices_number = 0;
    edge_number = 0;
}

// Load a graph from a file in MST format
template <typename T>
void Graph<T>::loadFromFileMst(const std::string& fileName) {
    deleteGraph();
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return;
    }

    int edges;
    file >> edges >> vertices_number;
    createGraph(vertices_number);
    
    int source, destination;
    T weight;

    for (int i = 0; i < edges; i++) {
        file >> source >> destination;
        
        if (std::is_same<T, int>::value) {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, float>::value) {
            float temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, double>::value) {
            double temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        
        addUndirectedEdge(source, destination, weight);
    }
    
    file.close();
}

// Load a graph from a file with floating-point numbers
template <typename T>
int* Graph<T>::loadFromFloat(const std::string& fileName) {
    deleteGraph();
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return nullptr;
    }

    static int start_end[2];
    int edges, vertex_start, vertex_end;
    file >> edges >> vertices_number >> vertex_start >> vertex_end;
    createGraph(vertices_number);
    
    int source, destination;
    T weight;

    for (int i = 0; i < edges; i++) {
        file >> source >> destination;
        
        if (std::is_same<T, int>::value) {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, float>::value) {
            float temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, double>::value) {
            double temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        
        addDirectedEdge(source, destination, weight);
    }

    start_end[0] = vertex_start;
    start_end[1] = vertex_end;
    file.close();
    
    return start_end;
}

// Load a graph from a file in the shortest path format
template <typename T>
int Graph<T>::loadFromSP(const std::string& fileName) {
    deleteGraph();
    std::ifstream file(fileName);

    if (!file.is_open()) {
        std::cout << "Cannot open file" << std::endl;
        return -1;
    }

    int edges;
    int vertex_start;
    file >> edges >> vertices_number >> vertex_start;
    createGraph(vertices_number);
    
    int source, destination;
    T weight;

    for (int i = 0; i < edges; i++) {
        file >> source >> destination;
        
        if (std::is_same<T, int>::value) {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, float>::value) {
            float temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else if (std::is_same<T, double>::value) {
            double temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        else {
            int temp_weight;
            file >> temp_weight;
            weight = static_cast<T>(temp_weight);
        }
        
        addDirectedEdge(source, destination, weight);
    }
    
    file.close();
    return vertex_start;
}

// Destructor
template <typename T>
Graph<T>::~Graph() {
    deleteGraph();
}