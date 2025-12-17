#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
using namespace std;

// A custom Dynaimc Array to replace Vector

template <typename T>
class DynamicArray
{
private:
    T *data;
    int capacity, count;

    void resize(int newCapacity)
    {
        T *newData = new T[newCapacity];
        for (int i = 0; i < count; i++)
        {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    DynamicArray(int initCap = 10)
    {
        capacity = initCap;
        count = 0;
        data = new T[capacity];
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    void add(T element)
    {
        if (count == capacity)
        {
            resize(capacity * 2);
        }
        data[count++] = element;
    }

    T &get(int index)
    {
        if (index < 0 || index >= count)
        {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    T &operator[](int index)
    {
        return data[index];
    }

    int size() const
    {
        return count;
    }

    // Ecpose raw poiner for sorting algorithms that expet T array[]
    T *getRawArray()
    {
        return data;
    }

    void display()
    {
        for (int i = 0; i < count; i++)
        {
            cout << data[i] << "\n";
        }
    }
};

#endif