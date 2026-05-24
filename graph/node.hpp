#pragma once
#include <set>
#include <string>

class Node {
    std::string name;
    std::set<Node*> neighbors;

    void add_neighbor(Node* neighbor) {neighbors.insert(neighbor);}
    void remove_neighbor(Node* neighbor) {neighbors.erase(neighbor);}

public:
    Node (const std::string& name) : name(name) {}
    const std::string get_name() const {return name;}

    using node_iterator = std::set<Node*>::const_iterator;
    node_iterator nb_begin() const {return neighbors.begin();}
    node_iterator nb_end() const {return neighbors.end();}

    friend class Graph;
};
