#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
struct ListNode
{
    T data;
    ListNode *next;
    ListNode(T val) : data(val), next(nullptr) {}
};

template <typename T>
class LinkedList
{
public:
    ListNode<T> *head;
    int size;

    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList()
    {
        clear();
    }

    // Insert at the end
    void insertEnd(T val)
    {
        ListNode<T> *newNode = new ListNode<T>(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            ListNode<T> *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        size++;
    }

    // Insert at the front
    void insertFront(T val)
    {
        ListNode<T> *newNode = new ListNode<T>(val);
        newNode->next = head;
        head = newNode;
        size++;
    }

    // Remove a node by value
    bool remove(T val)
    {
        if (!head)
            return false;

        // If the head needs to be removed
        if (head->data == val)
        {
            ListNode<T> *toDelete = head;
            head = head->next;
            delete toDelete;
            size--;
            return true;
        }

        ListNode<T> *temp = head;
        while (temp->next && !(temp->next->data == val))
        {
            temp = temp->next;
        }

        if (temp->next)
        {
            ListNode<T> *toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
            size--;
            return true;
        }

        return false;
    }

    // Check if list is empty
    bool isEmpty() const
    {
        return head == nullptr;
    }

    // Clear the list
    void clear()
    {
        while (head)
        {
            ListNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    // Display list
    void display() const
    {
        ListNode<T> *temp = head;
        while (temp)
        {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

#endif
