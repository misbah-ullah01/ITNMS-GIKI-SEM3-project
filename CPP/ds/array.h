#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
#include <stdexcept>
using namespace std;

// A custom Dynamic Array to replace std::vector

template <typename T>
class DynamicArray
{
private:
    T *data;      // pointer to array memory
    int capacity; // total allocated size
    int count;    // number of elements currently stored

    // Resize array when full
    void resize(int newCapacity)
    {
        T *newData = new T[newCapacity];
        for (int i = 0; i < count; i++)
        {
            newData[i] = data[i]; // copy old elements
        }
        delete[] data; // free old memory
        data = newData;
        capacity = newCapacity;
    }

public:
    // Constructor: default initial capacity = 10
    DynamicArray(int initCap = 10)
    {
        capacity = initCap;
        count = 0;
        data = new T[capacity];
    }

    // Destructor: free memory
    ~DynamicArray()
    {
        delete[] data;
    }

    // Add element at end
    void add(T element)
    {
        if (count == capacity)
        {
            resize(capacity * 2); // double capacity
        }
        data[count++] = element;
    }

    // Get element with bounds checking
    T &get(int index)
    {
        if (index < 0 || index >= count)
        {
            throw out_of_range("Index out of bounds");
        }
        return data[index];
    }

    // Operator[]: no bounds checking for speed
    T &operator[](int index)
    {
        return data[index];
    }

    // Current number of elements
    int size() const
    {
        return count;
    }

    // Expose raw pointer for sorting/searching
    T *getRawArray()
    {
        return data;
    }

    // Display all elements
    void display()
    {
        for (int i = 0; i < count; i++)
        {
            cout << data[i] << "\n";
        }
    }

    // Optional: clear array
    void clear()
    {
        count = 0; // reset size
    }
};

#endif
