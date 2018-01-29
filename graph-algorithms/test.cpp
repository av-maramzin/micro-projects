/*
 * Author: Aleksandr Maramzin (av-maramzin)
 * Graph construction test
 *
 */

#include <ctime>

#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

#include "graph.h"
using namespace graph_type;

enum class Vertex_Color {
    colorless = 0,
    grey,
    black,
    white
};

class Vertex_Data {
    
    public:
        Vertex_Data()
            : vertex_color(Vertex_Color::colorless), num(0) {}

        Vertex_Data(Vertex_Color vc, uint64_t n)
            : vertex_color(vc), num(n) {}

        Vertex_Color vertex_color;
        uint64_t num;
};

class Edge_Data {
    public:
        Edge_Data()
            : weight(0) {}

        Edge_Data(uint64_t w)
            : weight(w) {}

        uint64_t weight;
};

int main() {
    uint64_t n_vertices;
    uint64_t n_edges;
    vector<Vertex_Data> vertices_data;
    vector<Edge_Data> edges_data;

    cout << "Graph construction test!" << endl;
    
    cout << "Enter the number of vertices: "; 
    cin >> n_vertices;
    cout << endl;
    cout << "Number of vertices: " << n_vertices << endl; 
    
    cout << "Enter the number of edges: ";
    cin >> n_edges;
    cout << endl;
    cout << "Number of edges: " << n_edges << endl; 
  
    std::srand(std::time(nullptr));

    for (uint64_t i = 0; i < n_vertices; i++)
        vertices_data.push_back( Vertex_Data(Vertex_Color::white, rand()%100) );

    for (uint64_t i = 0; i < n_vertices; i++)
        edges_data.push_back( Edge_Data(rand()%1000) );

//    Graph<Vertex_Data, Edge_Data>* graph = new Adj_Matrix_Impl<Vertex_Data, Edge_Data>();

//    delete graph;

    return 0;
}
