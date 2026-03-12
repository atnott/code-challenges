#include<iostream>
#include "geometry.h"

int main() {
    cout << "enter N: ";
    int N; cin >> N;
    Point BluePoints[N/2]; Point RedPoints[N/2]; bool usedRed[N/2]; int blueIndex = 0;
    for (int i = 0; i < N/2; i++) usedRed[i] = false;
    cinPoint(BluePoints, RedPoints, N);
    cout << findMinDist(BluePoints, RedPoints, blueIndex, usedRed, N/2) << endl;
    return 0;
}