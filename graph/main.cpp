#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

class Node {
    string name;
    set<Node*> neighbors;

    void add_neighbor(Node* neighbor) {neighbors.insert(neighbor);}
    void remove_neighbor(Node* neighbor) {neighbors.erase(neighbor);}

public:
    Node (string& name) : name(name) {}
    const string get_name() const {return name;}

    using node_iterator = set<Node*>::const_iterator;
    node_iterator nb_begin() const {return neighbors.begin();}
    node_iterator nb_end() const {return neighbors.end();}

    friend class Graph;
};

class Graph {
    set<Node*> nodes;
public:
    void add_node(Node* node) {nodes.insert(node);}

    void add_edge(Node* node1, Node* node2) {
        if (nodes.find(node1) == nodes.end() || nodes.find(node2) == nodes.end()) return;
        node1->add_neighbor(node2);
        node2->add_neighbor(node1);
    }

    void remove_node(Node* node) {
        nodes.erase(node);
        for (Node* nd : nodes) nd->remove_neighbor(node);
    }

    using node_iterator = set<Node*>::const_iterator;
    node_iterator begin() const {return nodes.begin();}
    node_iterator end() const {return nodes.end();}

};