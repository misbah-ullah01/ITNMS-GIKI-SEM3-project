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
    void enqueue(const T &val)
    {
        list.insertEnd(val);
    }

    // STL-style aliases
    void push(const T &val) { enqueue(val); }

    // Remove element from the front (dequeue)
    T dequeue()
    {
        if (isEmpty())
        {
            cerr << "Error: Queue is empty" << endl;
            static T defaultVal;
            return defaultVal;
        }

        T frontVal = list.head->data;
        // remove first node directly
        ListNode<T> *tmp = list.head;
        list.head = list.head->next;
        delete tmp;
        list.count--;
        return frontVal;
    }

    // STL-style alias: pop returns void like std::queue
    void pop()
    {
        (void)dequeue();
    }

    // Peek front element without removing
    T front() const
    {
        if (isEmpty())
        {
            cerr << "Error: Queue is empty" << endl;
            static T defaultVal;
            return defaultVal;
        }

        return list.head->data;
    }

    bool empty() const { return isEmpty(); }

    int size() const { return list.size(); }

    // Display the queue
    void display() const
    {
        cout << "Front -> ";
        list.display();
    }
};

#endif
