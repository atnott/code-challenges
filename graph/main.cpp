#include <iostream>
#include"algorithms.hpp"

int main() {
    using namespace std;

    try {
        Graph graph_test("testgraph.txt");
        Graph graph_1000("1000.csv");

        graph_algo::solve_task(graph_test, "result_test");
        graph_algo::solve_task(graph_1000, "result_1000");
    }
    catch (exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}