#include<iostream>
#include"geometry.h"
#include<cmath>

double getDistance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double findMinDist(Point* BluePoints, Point* RedPoints, int blueIndex, bool* usedRed, int size) {
    double minSum = 10000 * 10000;
    if (blueIndex == size) return 0;
    for (int i = 0; i < size; i++) {
        if (usedRed[i] == false) {
            usedRed[i] = true;

            double temp = getDistance(RedPoints[i], BluePoints[blueIndex]);
            temp += findMinDist(BluePoints, RedPoints, blueIndex + 1, usedRed, size);

            minSum = (temp < minSum) ? temp : minSum;
            usedRed[i] = false;
        }
    }
    return minSum;
}

void cinPoint(Point* BluePoints, Point* RedPoints, int N) {
    int lastIndexBlue = 0, lastIndexRed = 0, cnst = N;
    while (N > 0) {
        char color;
        cout << "enter color for point: "; cin >> color;
        if (color == 'r' && lastIndexRed < cnst/2) {
            Point temp;
            cout << "enter X: "; cin >> temp.x;
            cout << "enter Y: "; cin >> temp.y;
            RedPoints[lastIndexRed++] = temp;
            N--;
        }
        else if (color == 'b' && lastIndexBlue < cnst/2) {
            Point temp;
            cout << "enter X: "; cin >> temp.x;
            cout << "enter Y: "; cin >> temp.y;
            BluePoints[lastIndexBlue++] = temp;
            N--;
        }
        else {
            cout << "full! enter another color" << endl;
        }
    }
}

void printArray(Point* array, int size) {
    for (int i = 0; i < size; i++) cout << "x: " << array[i].x << '\t' << "y: " << array[i].y << endl;
}


