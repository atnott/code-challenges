#pragma once
#include"graph.hpp"

namespace graph_algo {
    Graph get_component_bfs(Node* start, std::set<Node*>& unvisited);
    void solve_task(const Graph& g, const std::string& output);
}