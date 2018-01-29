/*
 * Author: Aleksandr Maramzin (av-maramzin)
 * Graph type
 * 
 */

#include "graph.h"

#include <iostream>
using namespace std;

namespace graph_type {

template <typename V, typename E>
Vertex<V,E>::Vertex()
    : vertex_data(nullptr) 
{
    std::cout << "Vertex::Vertex()" << std::endl;
}

template <typename V, typename E>
Vertex<V,E>::Vertex(Graph<V,E>& g, V* vd)
    : graph(g), vertex_data(vd), vertex_id(g.assign_new_vertex_id()) 
{
    std::cout << "Vertex::Vertex()" << std::endl;
}
        
template <typename V, typename E>
Vertex<V,E>& Vertex<V,E>::connect(Vertex<V,E>& to_vertex, E* edge_data) 
{
    // connect this and to_vertex vertices with the given edge_data
    graph.connect_vertices(vertex_id, to_vertex.vertex_id, edge_data);
    return *this;
}

template <typename V, typename E>
Edge<V,E>::Edge() 
{
    std::cout << "Edge::Edge()" << std::endl;
}

template <typename V, typename E>
Edge<V,E>::Edge(Graph<V,E>& g, E* ed)
    : graph(g), edge_data(ed), edge_id(g.assign_new_edge_id())
{
    std::cout << "Edge::Edge()" << std::endl;
}

template <typename V, typename E>
Edge<V,E>::Edge(Graph<V,E>& g, E* ed, Vertex<V,E>& to, Vertex<V,E>& from)
    : graph(g), edge_data(ed), from(from), to(to), edge_id(g.assign_new_edge_id())
{
    std::cout << "Edge::Edge()" << std::endl;
}

template <typename V, typename E>
Graph<V,E>::Graph() 
{
    std::cout << "Graph::Graph()" << std::endl;
}

template <typename V, typename E>
Graph_Impl<V,E>::Graph_Impl()
    : num_vertices(default_num_vertices), num_edges(default_num_edges), vertex_id(0), edge_id(0)
{
    vertices = new Vertex<V,E>[num_vertices];
    edges = new Edge<V,E>[num_edges];
}

template <typename V, typename E>
Graph_Impl<V,E>::Graph_Impl(const uint64_t n_vertices) 
    : num_vertices(n_vertices), num_edges(default_num_edges), vertex_id(0), edge_id(0)
{
    vertices = new Vertex<V,E>[num_vertices];    
    edges = new Edge<V,E>[default_num_edges];
}

template <typename V, typename E>
Graph_Impl<V,E>::Graph_Impl(const uint64_t n_vertices, const uint64_t n_edges)
    : num_vertices(n_vertices), num_edges(n_edges), vertex_id(0), edge_id(0)
{
    vertices = new Vertex<V,E>[num_vertices];    
    edges = new Edge<V,E>[num_edges];
}

template <typename V, typename E>
uint64_t Graph_Impl<V,E>::assign_new_vertex_id()
{
    return vertex_id++;
}

template <typename V, typename E>
uint64_t Graph_Impl<V,E>::assign_new_edge_id()
{
    return edge_id++;
}

template <typename V, typename E>
Graph_Impl<V,E>::~Graph_Impl() 
{
    delete [] vertices;
    delete [] edges;
}

template <typename V, typename E>
const uint16_t Graph_Impl<V,E>::default_num_vertices = 1000;

template <typename V, typename E>
const uint16_t Graph_Impl<V,E>::default_num_edges = 100;

template <typename V, typename E>
Adj_Matrix_Impl<V,E>::Adj_Matrix_Impl(uint64_t num_vertices)
    : Graph_Impl<V,E>(num_vertices) 
{
    uint64_t adjacency_matrix_size = num_vertices / 8 + 1;
    adjacency_matrix = new uint8_t[adjacency_matrix_size];
            
    for(auto i = 0; i < adjacency_matrix_size; i++) {
        adjacency_matrix[i] = 0;
    }
}
        
template <typename V, typename E>
Adj_Matrix_Impl<V,E>::~Adj_Matrix_Impl() 
{
    delete [] adjacency_matrix;
}

}
