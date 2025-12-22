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

    T pop()
    {
        if (!list.head)
            throw runtime_error("Stack Empty");
        T val = list.head->data;
        ListNode<T> *temp = list.head;
        list.head = list.head->next;
        delete temp;
        list.size--;
        return val;
    }

    T peek()
    {
        if (!list.head)
            throw runtime_error("Stack Empty");
        return list.head->data;
    }

    bool isEmpty()
    {
        return list.head == nullptr;
    }

    void display()
    {
        list.display();
    }
};

#endif
