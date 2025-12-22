#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include "linkedlist.h"
using namespace std;

template <typename T>
class Queue
{
private:
    LinkedList<T> list; // internal linked list

public:
    Queue() {}

    // Check if queue is empty
    bool isEmpty() const
    {
        return list.isEmpty();
    }

    // Add element to the end (enqueue)
    void enqueue(T val)
    {
        list.insertEnd(val);
    }

    // Remove element from the front (dequeue)
    T dequeue()
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty");
        }

        T frontVal = list.head->data;
        list.remove(frontVal); // remove the first element
        return frontVal;
    }

    // Peek front element without removing
    T front()
    {
        if (isEmpty())
            throw runtime_error("Queue is empty");

        return list.head->data;
    }

    // Display the queue
    void display() const
    {
        cout << "Front -> ";
        list.display();
    }
};

#endif
