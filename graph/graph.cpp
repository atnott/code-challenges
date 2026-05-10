#include"graph.hpp"
#include<fstream>
#include<sstream>

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

Graph::Graph(const std::string &file_name) {
    using namespace std;
    ifstream file(file_name);
    std::string line;

    if (!file.is_open()) return;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string u_name, v_name;

        if (ss >> u_name >> v_name) {
            Node* u = find_node(u_name);
            if (u == nullptr) {
                u = new Node(u_name);
                add_node(u);
            }
            Node* v = find_node(v_name);
            if (v == nullptr) {
                v = new Node(v_name);
                add_node(v);
            }
            add_edge(u, v);
        }
    }
}