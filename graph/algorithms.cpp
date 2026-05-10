#include"algorithms.hpp"
#include <queue>
#include <fstream>
#include <iostream>

namespace graph_algo {
    using std::set;
    set<Node*> get_component_bfs(Node* start, set<Node*>& unvisited) {
        set<Node*> component; // хранение узлов текущего графа
        std::queue<Node*> q; // очередь для bfs

        q.push(start);
        unvisited.erase(start);
        component.insert(start);

        while (!q.empty()) {
            Node* curr = q.front();
            q.pop();

            // перебор соседей текущего узла
            for (auto it = curr->nb_begin(); it != curr->nb_end(); ++it) {
                Node* neighbor = *it;

                // если сосед еще не посещен
                if (unvisited.find(neighbor) != unvisited.end()) {
                    unvisited.erase(neighbor);
                    component.insert(neighbor);
                    q.push(neighbor);
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
            set<Node*> component = get_component_bfs(start_node, unvisited);

            std::string file_name = output + "_part_" + std::to_string(index++) + ".txt";
            std::ofstream file(file_name);

            if (file.is_open()) {
                file << "source \t target\n";

                set<std::pair<Node*, Node*>> seen;

                for (Node* u : component) {
                    // перебираем всех соседей узла
                    for (auto it = u->nb_begin(); it != u->nb_end(); ++it) {
                        Node* neighbor = *it;
                        if (seen.find({neighbor, u}) == seen.end()) {
                            file << u->get_name() << "\t" << neighbor->get_name() << std::endl;
                            seen.insert({u, neighbor});
                        }
                    }
                }
                file.close();
            }
        }
    }
}