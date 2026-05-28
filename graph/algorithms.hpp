#pragma once
#include"graph.hpp"
#ibclude<vector>

namespace graph_algo {
    Graph get_component_bfs(Node* start, std::set<Node*>& unvisited);
    std::vector<Graph> find_all_components(const Graph& g);
    void solve_task(const Graph& g, const std::string& output);
}