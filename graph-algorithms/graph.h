/*
 * Author: Aleksandr Maramzin (av-maramzin)
 * Graph type
 * 
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>

namespace graph_type {

template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge;

template <typename V, typename E>
class Graph;

template <typename V, typename E>
class Graph_Impl;

template <typename V, typename E>
class Adj_Matrix_Impl; 

template <typename V, typename E>
class Depth_First_Iterator;

template <typename V, typename E>
class Vertex {

    public:
        Vertex();
        Vertex(Graph<V,E>& g, V* vd);
        
        Vertex& connect(Vertex& to_vertex, E* edge_data); 

    private:
        V* vertex_data;
        Graph<V,E>& graph; // cannot create vertex independent of the graph
        uint64_t vertex_id;
};

template <typename V, typename E>
class Edge {

    public:
        Edge();
        Edge(Graph<V,E>& g, E* ed);
        Edge(Graph<V,E>& g, E* ed, Vertex<V,E>& to, Vertex<V,E>& from);

    private:
        E* edge_data;
        Graph<V,E>& graph; // cannot create edge independent of the graph
        Vertex<V,E>& from;
        Vertex<V,E>& to;
        uint64_t edge_id;
};

template <typename V, typename E>
class Graph {
    
    public:
        Graph();
        virtual ~Graph();

        virtual uint64_t assign_new_vertex_id() = 0;
        virtual uint64_t assign_new_edge_id() = 0;
        
        virtual void connect_vertices(uint64_t from_id, uint64_t to_id, E* edge_data) = 0;

        friend class Depth_First_Iterator<V,E>;
        typedef Depth_First_Iterator<V,E> depth_iterator;
        
        virtual depth_iterator begin() = 0;
        virtual depth_iterator end() = 0;
};

template <typename V, typename E>
class Graph_Impl : public Graph<V,E> {

    public:
        Graph_Impl(); 
        Graph_Impl(const uint64_t n_vertices); 
        Graph_Impl(const uint64_t n_vertices, const uint64_t n_edges);
        ~Graph_Impl(); 
        
        uint64_t assign_new_vertex_id() override final;
        uint64_t assign_new_edge_id() override final;
        
        virtual void connect_vertices(uint64_t from_id, uint64_t to_id, E* edge_data);

    private:
        static const uint16_t default_num_vertices;
        static const uint16_t default_num_edges;
        uint64_t num_vertices;
        uint64_t num_edges;
        uint64_t vertex_id;
        uint64_t edge_id;

        Vertex<V,E>* vertices;
        Edge<V,E>*   edges;
};

template <typename V, typename E>
class Adj_Matrix_Impl : public Graph_Impl<V,E> 
{
    public:
        Adj_Matrix_Impl(uint64_t num_vertices);
        
        void connect_vertices(uint64_t from_id, uint64_t to_id, E* edge_data) override final;
        
        ~Adj_Matrix_Impl(); 
        
    private:
        uint8_t* adjacency_matrix;
        uint64_t adjacency_matrix_size;
};

template <typename V, typename E>
class Depth_First_Iterator {
    
    public:
        Depth_First_Iterator();
        ~Depth_First_Iterator();

        Vertex<V,E>& operator*();
        
    private:
        Graph<V,E>& graph;

};

}

#endif // #ifndef GRAPH_H
