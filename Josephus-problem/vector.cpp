#include <iostream>
#include "vector.h"
using namespace std;

Array::Array(int startCapacity)
{
    if (startCapacity <= 0)
        capacity = DEFAULT_CAPACITY;
    else
        capacity = startCapacity;
    ptr = new int[capacity];
    size = 0;
}

Array::~Array()
{
    delete[] ptr;
}

Array::Array(const Array &other)
{
    ptr = new int[other.capacity];
    size = other.size;
    capacity = other.capacity;
    for (int i = 0; i < size; i++)
        ptr[i] = other.ptr[i];
}

Array& Array::operator =(const Array& other)
{
    if (this==&other)
        return *this;

    if (capacity != other.capacity)
    {
        delete[] ptr;
        ptr = new int[other.capacity];
        capacity = other.capacity;
    }
    size = other.size;
    for (int i=0; i<size; i++)
        ptr[i] = other.ptr[i];
    return *this;
}

int &Array::operator [] (int index) {
    if (index >= size or index < 0) {
        throw ArrayException();
    } else return ptr[index];
}

void Array::insert(int elem, int index) {
    if (index > size or index < 0) {
        throw ArrayException();
    }
    if (size == capacity)
        increaseCapacity(size+1);
    for (int i = size - 1; i >= index; i--)
        ptr[i + 1] = ptr[i];
    size++;
    ptr[index] = elem;
}

void Array::insert(int elem) {
    insert(elem, size);
}

void Array::increaseCapacity(int newCapacity) {
    capacity = newCapacity > capacity * 2 ? newCapacity : capacity * 2;
    int* newPtr = new int[capacity];
    for (int i = 0; i < size; i++)
        newPtr[i] = ptr[i];
    delete[] ptr;
    ptr = newPtr;
}
void Array::remove(int index) {
    for (int i = index; i < size - 1; i++)
        ptr[i] = ptr[i+1];
    ptr[size - 1] = 0;
    size--;
}

int Array::getSize() const {
    return size;
}

ostream& operator <<(ostream& out, const Array &arr) {
    out << "Total size: " << arr.size << endl;
    for (int i=0; i < arr.size; i++)
        out << arr.ptr[i] << endl;
    return out;
}

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