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