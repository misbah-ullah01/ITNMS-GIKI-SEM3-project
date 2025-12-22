#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
using namespace std;

// Custom exception handling without STL
#define INT_MAX_VALUE 2147483647

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
    void add(const T &element)
    {
        if (count == capacity)
        {
            resize(capacity * 2); // double capacity
        }
        data[count++] = element;
    }

    // STL-style alias
    void push_back(const T &element) { add(element); }

    // Get element with bounds checking
    T &get(int index)
    {
        if (index < 0 || index >= count)
        {
            cerr << "Error: Index " << index << " out of bounds (size: " << count << ")" << endl;
            static T defaultVal;
            return defaultVal;
        }
        return data[index];
    }

    const T &get(int index) const
    {
        if (index < 0 || index >= count)
        {
            cerr << "Error: Index " << index << " out of bounds (size: " << count << ")" << endl;
            static T defaultVal;
            return defaultVal;
        }
        return data[index];
    }

    // Operator[]: no bounds checking for speed
    T &operator[](int index)
    {
        return data[index];
    }

    const T &operator[](int index) const
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

    const T *getRawArray() const
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

    bool empty() const { return count == 0; }

    // Erase element at index (shifts left)
    void erase(int index)
    {
        if (index < 0 || index >= count)
        {
            cerr << "Error: Cannot erase - index out of bounds" << endl;
            return;
        }
        for (int i = index; i < count - 1; i++)
            data[i] = data[i + 1];
        count--;
    }

    // Swap contents with another array
    void swap(DynamicArray &other)
    {
        T *tmpData = data;
        data = other.data;
        other.data = tmpData;

        int tmpCap = capacity;
        capacity = other.capacity;
        other.capacity = tmpCap;

        int tmpCount = count;
        count = other.count;
        other.count = tmpCount;
    }
};

#endif
