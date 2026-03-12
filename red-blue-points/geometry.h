#pragma once
using namespace std;

struct Point {
    int x, y;
};

double getDistance(Point p1, Point p2);
double findMinDist(Point* BluePoints, Point* RedPoints, int blueIndex, bool* usedRed, int size);
void cinPoint(Point* BluePoints, Point* RedPoints, int N);
void printArray(Point* array, int size);
