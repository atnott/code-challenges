#include"algorithms.hpp"
#include <queue>
#include <fstream>
#include <iostream>
#include<unordered_map>

namespace graph_algo {
    using std::set;
    Graph get_component_bfs(Node* start, set<Node*>& unvisited) {
        Graph component; // хранение узлов текущего графа
        std::queue<Node*> q; // очередь для bfs

        std::unordered_map<Node*, Node*> old_to_new;

        q.push(start);
        unvisited.erase(start);

        Node* new_start = new Node(start->get_name());
        component.add_node(new_start);
        old_to_new[start] = new_start;

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            Node* new_curr = old_to_new[curr];

            // перебор соседей текущего узла
            for (auto it = curr->nb_begin(); it != curr->nb_end(); ++it) {
                Node* neighbor = *it;

                // если сосед еще не посещен
                if (old_to_new.find(neighbor) == old_to_new.end()) {
                    Node* new_neighbor = new Node(neighbor->get_name());
                    component.add_node(new_neighbor);
                    old_to_new[neighbor] = new_neighbor;

                    if (unvisited.find(neighbor) != unvisited.end()) {
                        unvisited.erase(neighbor);
                        q.push(neighbor);
                    }
                }

                if (curr->get_name() < neighbor->get_name()) {
                    component.add_edge(new_curr, old_to_new[neighbor]);
                }
            }
        }
        return component;
    }

    void solve_task(const Graph& g, const std::string& output) {
        set<Node*> unvisited;
        for (auto it = g.begin(); it != g.end(); ++it) {
            unvisited.insert(*it);
        }

        int index = 1;

        while (!unvisited.empty()) {
            Node* start_node = *unvisited.begin();
            Graph component = get_component_bfs(start_node, unvisited);

            std::string file_name = output + "_part_" + std::to_string(index++) + ".txt";
            std::ofstream file(file_name);

            if (file.is_open()) {
                file << "source \t target\n";

                for (auto it_u = component.begin(); it_u != component.end(); ++it_u) {
                    Node* u = *it_u;
                    for (auto it_v = u->nb_begin(); it_v != u->nb_end(); ++it_v) {
                        Node* neighbor = *it_v;

                        if (u->get_name() < neighbor->get_name()) {
                            file << u->get_name() << "\t" << neighbor->get_name() << std::endl;
                        }
                    }
                }
                file.close();
            }
        }
    }
}