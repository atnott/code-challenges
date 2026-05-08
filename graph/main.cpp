#include <iostream>
#include"graph.hpp"
using namespace std;

int main() {
    Graph graph("testgraph.txt");

    int cnt_node = 0;
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        cnt_node++;
    }
    cout << cnt_node << endl;
}