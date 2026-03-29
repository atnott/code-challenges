#include "vector.h"
#include <chrono>
#include <fstream>
#include <iostream>
using namespace std;

int main() {
    ofstream fout;
    fout.open("result2.txt");
    for (int i = 1000; i <= 500000; i *= 1.5) {
        auto start = chrono::high_resolution_clock::now();
        int result = find_last(i, 2);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        fout << i << ' ' <<  duration <<  ' ' << result << endl;
    }
    cout << "finished" << endl;
}