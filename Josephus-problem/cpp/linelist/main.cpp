#include"list.hpp"
#include<iostream>
#include<chrono>
#include<fstream>

int main() {
    using namespace std;
    ofstream fout;
    fout.open("../../data/result_list.txt");
    for (int i = 1000; i <= 1500000; i *= 1.5) {
        auto start = chrono::high_resolution_clock::now();
        int result = find_last(i, 2);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        fout << i << ' ' <<  duration <<  ' ' << result << endl;
    }
    cout << "finished" << endl;
}