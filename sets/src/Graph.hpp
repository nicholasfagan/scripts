//
// Created by nfagan on 10/20/19.
//

#ifndef SETS_GRAPH_HPP
#define SETS_GRAPH_HPP

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <bits/stdc++.h>
#include <functional>
#include "sets.hpp"

template<class Data, class Weight=double>
class Graph {
public:
    class Edge {
    public:
        Data from;
        Data to;
        Weight weight;
        Edge(Data from, Data to, Weight weight) : from(from), to(to), weight(weight) {}
        Edge() = default;
        ~Edge() = default;
        /// Defines its own hash function
        size_t operator()(const Edge& other) const noexcept {
            return std::hash<Data>{}(other.from) ^ std::hash<Data>{}(other.to) ^ std::hash<Weight>{}(other.weight);
        }
        bool operator==(const Edge&b) const noexcept {
            return from == b.from && to == b.to && weight == b.weight;
        }
        friend std::ostream& operator<<(std::ostream& s, const Edge& e) {
            return s << std::string("(") << e.from << " <-> " << e.to << ", " << e.weight << ")";
        }
    };
    Graph() : vertices(), edges() {}
    ~Graph() = default;

    void add(Data vertex);
    void edge(Data a, Data b, Weight w = 1);

    Graph<Data, Weight> minimumSpanningTree() const {
        std::vector<Edge> ordered;
        std::copy(edges.begin(), edges.end(), std::back_inserter(ordered));
        sort(ordered.begin(), ordered.end(), std::function<bool(const Edge&,const Edge&)>([](const Edge& a, const Edge& b){
            return a.weight < b.weight;
        }));
        Graph<Data, Weight> tree;
        for(auto& v : vertices) tree.add(v);
        sets::DisjointSets<Data> forest;
        for(auto& edge : ordered) {
            sets::Node<Data>* from = forest.find(edge.from);
            sets::Node<Data>* to = forest.find(edge.to);
            if( !to || from != to) {
                forest.create(edge.from);
                forest.create(edge.to);
                forest.join(edge.from, edge.to);
                tree.edges.emplace(edge);
            }
        }

        return tree;
    }


    Graph<Data, Weight> minimumSpanningTreeWith(std::vector<Edge> needed) const {
        std::vector<Edge> ordered;
        std::copy(edges.begin(), edges.end(), std::back_inserter(ordered));
        sort(ordered.begin(), ordered.end(), std::function<bool(const Edge&,const Edge&)>([](const Edge& a, const Edge& b){
            return a.weight < b.weight;
        }));
        Graph<Data, Weight> tree;
        for(auto& v : vertices) tree.add(v);
        sets::DisjointSets<Data> forest;

        for(auto& edge : needed) {
              forest.create(edge.from);
              forest.create(edge.to);
              forest.join(edge.from, edge.to);
              tree.edges.emplace(edge);
        }

        for(auto& edge : ordered) {
            sets::Node<Data>* from = forest.find(edge.from);
            sets::Node<Data>* to = forest.find(edge.to);
            if( !to || from != to) {
                forest.create(edge.from);
                forest.create(edge.to);
                forest.join(edge.from, edge.to);
                tree.edges.emplace(edge);
            }
        }

        return tree;
    }

    Graph<Data, Weight> merge() {

        typedef struct LNode {
            Data vertex;
            Weight w;
            LNode* next;
        } LNode;
        // Create Adjacency-list representation

        return Graph();
    }

    size_t operator()(const Graph& other) const noexcept {
        return std::hash<std::unordered_set<Data>>{}(other.vertices) ^ std::hash<std::unordered_set<Edge, Edge>>{}(other.edges);
    }
    bool operator==(const Graph&b) const noexcept {
        return vertices == b.vertices && edges == b.edges;
    }
    friend std::ostream& operator<<(std::ostream& s, const Graph& e) {
        s << std::string("Graph [");
        for(auto& d : e.vertices)
            s << d << ", " ;
        for(auto& ed : e.edges)
            s << std::endl << ed ;
        return s << "]";
    }

private:
    std::unordered_set<Data> vertices;
    std::unordered_set<Edge, Edge> edges;

};

template<class Data, class Weight>
void Graph<Data, Weight>::add(Data vertex) {
    vertices.emplace(std::move(vertex));
}

template<class Data, class Weight>
void Graph<Data, Weight>::edge(Data a, Data b, Weight w) {
    edges.emplace(a,b,w);
}



#endif //SETS_GRAPH_HPP
