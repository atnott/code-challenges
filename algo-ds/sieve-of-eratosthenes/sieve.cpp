#include<iostream>
using namespace std;
int main() {
    cout << "До какого числа найти простые числа? Введите число: ";
    int n; cin >> n;
    bool sieve[n + 1];
    for (int i = 2; i <= n; i++) {sieve[i] = true;}
    int x = 2;
    while (x * x <= n) {
        for (int i = x * x; i <= n; i += x) {
            sieve[i] = false;
        }
        x++;
    }
    for (int x = 1; x <= n; x++) {
        if (sieve[x]) cout << x << "\t";
    }
}