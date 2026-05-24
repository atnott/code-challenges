#pragma once
#include "node.hpp"

class Graph {
    std::set<Node*> nodes;
    Node* find_node(const std::string& name) const;
public:

    Graph() = default;
    Graph(const std::string& file_name);
    ~Graph();

    void add_node(Node* node) {nodes.insert(node);}
    void add_edge(Node* node1, Node* node2);
    void remove_node(Node* node);

    using node_iterator = std::set<Node*>::const_iterator;
    node_iterator begin() const {return nodes.begin();}
    node_iterator end() const {return nodes.end();}

};
