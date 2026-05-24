#pragma once
#include <iostream>
using namespace std;

const int DEFAULT_CAPACITY = 10;
class ArrayException {

};

class Array {
public:
    int *ptr, capacity, size;
    explicit Array(int startCapacity=DEFAULT_CAPACITY);

    ~Array();

    int& operator[] (int index);

    void insert(int elem, int index);

    void insert(int elem);

    void remove(int index);

    Array(const Array& arr);

    Array& operator =(const Array& arr);

    int operator [](int index) const;

    void increaseCapacity(int newCapacity);

    int getSize() const;

    friend ostream& operator <<(ostream& out, const Array& arr);
};

int find_last(int n, int step);