#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

// Template Min Heap
template <typename T>
class MinHeap
{
private:
    T *heap;      // array to store heap elements
    int capacity; // max size
    int size;     // current size

    // Get parent and children indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Swap two values
    void swap(T &a, T &b)
    {
        T temp = a;
        a = b;
        b = temp;
    }

    // Heapify upwards
    void heapifyUp(int i)
    {
        while (i > 0 && heap[parent(i)] > heap[i])
        {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    // Heapify downwards
    void heapifyDown(int i)
    {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < size && heap[l] < heap[smallest])
            smallest = l;

        if (r < size && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    // Constructor
    MinHeap(int cap = 50)
    {
        capacity = cap;
        size = 0;
        heap = new T[capacity];
    }

    // Destructor
    ~MinHeap()
    {
        delete[] heap;
    }

    // Insert element
    void insert(T value)
    {
        if (size == capacity)
        {
            cout << "Heap is full!\n";
            return;
        }

        heap[size] = value;
        heapifyUp(size);
        size++;
    }

    // Remove minimum element
    T extractMin()
    {
        if (size <= 0)
            throw runtime_error("Heap is empty");

        T root = heap[0];
        heap[0] = heap[size - 1];
        size--;
        heapifyDown(0);
        return root;
    }

    // Get minimum element
    T getMin()
    {
        if (size <= 0)
            throw runtime_error("Heap is empty");
        return heap[0];
    }

    // Check if empty
    bool isEmpty()
    {
        return size == 0;
    }

    // Display heap
    void display()
    {
        for (int i = 0; i < size; i++)
            cout << heap[i] << " ";
        cout << "\n";
    }
};

#endif
