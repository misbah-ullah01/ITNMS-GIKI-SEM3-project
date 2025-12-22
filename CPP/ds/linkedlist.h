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
    int count;

    LinkedList() : head(nullptr), count(0) {}

    // Copy constructor (deep copy)
    LinkedList(const LinkedList<T> &other) : head(nullptr), count(0)
    {
        ListNode<T> *temp = other.head;
        while (temp)
        {
            insertEnd(temp->data);
            temp = temp->next;
        }
    }

    // Copy assignment operator (deep copy)
    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this != &other)
        {
            clear();
            ListNode<T> *temp = other.head;
            while (temp)
            {
                insertEnd(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

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
        count++;
    }

    // Insert at the front
    void insertFront(T val)
    {
        ListNode<T> *newNode = new ListNode<T>(val);
        newNode->next = head;
        head = newNode;
        count++;
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
            count--;
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
            count--;
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
        count = 0;
    }

    // New helpers for compatibility
    int size() const { return count; }

    void push_back(const T &val) { insertEnd(val); }

    // Get element at index (0-based)
    T &get(int index)
    {
        if (index < 0)
        {
            cerr << "Error: Index out of bounds" << endl;
            static T defaultVal;
            return defaultVal;
        }
        ListNode<T> *temp = head;
        int i = 0;
        while (temp && i < index)
        {
            temp = temp->next;
            i++;
        }
        if (!temp)
        {
            cerr << "Error: Index out of bounds" << endl;
            static T defaultVal;
            return defaultVal;
        }
        return temp->data;
    }

    const T &get(int index) const
    {
        if (index < 0)
        {
            cerr << "Error: Index out of bounds" << endl;
            static T defaultVal;
            return defaultVal;
        }
        ListNode<T> *temp = head;
        int i = 0;
        while (temp && i < index)
        {
            temp = temp->next;
            i++;
        }
        if (!temp)
        {
            cerr << "Error: Index out of bounds" << endl;
            static T defaultVal;
            return defaultVal;
        }
        return temp->data;
    }

    // Remove element at index
    bool removeAt(int index)
    {
        if (index < 0 || !head)
            return false;
        if (index == 0)
        {
            ListNode<T> *toDelete = head;
            head = head->next;
            delete toDelete;
            count--;
            return true;
        }
        int i = 0;
        ListNode<T> *prev = head;
        while (prev->next && i < index - 1)
        {
            prev = prev->next;
            i++;
        }
        if (!prev->next)
            return false;
        ListNode<T> *toDelete = prev->next;
        prev->next = prev->next->next;
        delete toDelete;
        count--;
        return true;
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
