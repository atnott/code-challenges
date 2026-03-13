#include<iostream>
using namespace std;
int main() {
    int array[]{1, 4, 6, 8, 2, 3};
    bool is_sorted = false;
    while (!is_sorted) {
        int i = 0;
        is_sorted = true;
        while (i < sizeof(array) / sizeof(array[0]) - 1) {
            if (array[i] > array[i + 1]) {
                is_sorted = false;
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
            i++;
        }
    }
    for (int k = 0; k < sizeof(array) / sizeof(array[0]); k++) cout << array[k] << '\t';
    return 0;
}