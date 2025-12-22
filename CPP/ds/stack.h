#ifndef STACK_H
#define STACK_H

#include "linkedlist.h"

template <typename T>
class Stack
{
private:
    LinkedList<T> list;

public:
    void push(T val)
    {
        list.insertFront(val);
    }

    // Pop and return
    T pop()
    {
        if (!list.head)
        {
            cerr << "Error: Stack Empty" << endl;
            static T defaultVal;
            return defaultVal;
        }
        T val = list.head->data;
        ListNode<T> *temp = list.head;
        list.head = list.head->next;
        delete temp;
        list.count--;
        return val;
    }

    T peek() const
    {
        if (!list.head)
        {
            cerr << "Error: Stack Empty" << endl;
            static T defaultVal;
            return defaultVal;
        }
        return list.head->data;
    }

    bool isEmpty() const
    {
        return list.head == nullptr;
    }

    // STL-style aliases
    void popVoid()
    {
        (void)pop();
    }

    T top() const { return peek(); }
    bool empty() const { return isEmpty(); }

    void display()
    {
        list.display();
    }
};

#endif
