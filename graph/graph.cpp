#include"graph.hpp"

Graph::~Graph() {
    for (Node* node : nodes) delete node;
    nodes.clear();
}

void Graph::add_edge(Node* node1, Node* node2) {
    if (nodes.find(node1) == nodes.end() || nodes.find(node2) == nodes.end()) return;
    node1->add_neighbor(node2);
    node2->add_neighbor(node1);
}

void Graph::remove_node(Node* node) {
    nodes.erase(node);
    for (Node* nd : nodes) nd->remove_neighbor(node);
    delete node;
}

Node* Graph::find_node(const std::string& name) const {
    for (Node* node : nodes) {
        if (node->get_name() == name) return node;
    }
    return nullptr;
}