#include"vector.h"
#include<chrono>
#include<fstream>
#include<iostream>
using namespace std;

int find_last(int n, int step) {
    Array arr(n);
    for (int i=0; i < n; i++) arr.insert((i + 1), i);

    int last_index = 0;
    while (arr.size > 1) {
        last_index = (last_index + step -  1) % arr.size;
        arr.remove(last_index);
    }
    return arr[0];
};

int main() {
    ofstream fout;
    fout.open("../../data/result_array.txt");
    int array[]{1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int x : array) {
        auto start = chrono::high_resolution_clock::now();
        int result = find_last(x, 2);
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
        fout << x << ' ' <<  duration <<  ' ' << result << endl;
        cout << x << ' ' << duration <<  ' ' << result << endl;
    }
    cout << "finished" << endl;
}