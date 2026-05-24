#include"list.hpp"
#include<iostream>
#include<chrono>
#include<fstream>

int find_last(int n, int step) {
    List<int> list;
    for (int i{1}; i <= n; i++) list.push_back(i);

    auto* current = list.head;

    while (current->p_next != list.head) {
        current = current->p_next;
    }

    while (list.get_size() != 1) {
        for (int i{0}; i < step - 1; i++) {
            current = current->p_next;
        }
        list.remove_after(current);
    }
    return current->data;
}

int main() {
    using namespace std;
    ofstream fout;
    fout.open("../../data/result_list.txt");
    int array[]{1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int i : array) {
        auto start = chrono::high_resolution_clock::now();
        int result = find_last(i, 2);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        fout << i << ' ' <<  duration <<  ' ' << result << endl;
        cout << i << ' ' << duration <<  ' ' << result << endl;
    }
    cout << "finished" << endl;
}