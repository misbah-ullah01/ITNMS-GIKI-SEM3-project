#ifndef ORDEREDMAP_H
#define ORDEREDMAP_H

#include <iostream>
using namespace std;

// Custom OrderedMap to replace std::map (keeps insertion order and key-value pairs)
template <typename K, typename V>
class OrderedMap
{
private:
    struct MapNode
    {
        K key;
        V value;
        MapNode *next;

        MapNode(K k, V v) : key(k), value(v), next(nullptr) {}
    };

    MapNode *head;
    int size;

public:
    OrderedMap() : head(nullptr), size(0) {}

    ~OrderedMap()
    {
        clear();
    }

    // Insert or update key-value pair
    void insert(K key, V value)
    {
        // Check if key exists
        MapNode *current = head;
        while (current)
        {
            if (current->key == key)
            {
                current->value = value; // Update existing
                return;
            }
            current = current->next;
        }

        // Key not found, insert at end (maintains order)
        MapNode *newNode = new MapNode(key, value);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            MapNode *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        size++;
    }

    // Get value by key
    V &get(K key)
    {
        MapNode *current = head;
        while (current)
        {
            if (current->key == key)
                return current->value;
            current = current->next;
        }
        cerr << "Error: Key not found in map" << endl;
        static V defaultVal;
        return defaultVal;
    }

    // Operator[] for access
    V &operator[](K key)
    {
        MapNode *current = head;
        while (current)
        {
            if (current->key == key)
                return current->value;
            current = current->next;
        }

        // Create new entry if key doesn't exist
        MapNode *newNode = new MapNode(key, V());
        if (!head)
            head = newNode;
        else
        {
            MapNode *temp = head;
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        size++;
        return newNode->value;
    }

    // Check if key exists
    bool find(K key) const
    {
        MapNode *current = head;
        while (current)
        {
            if (current->key == key)
                return true;
            current = current->next;
        }
        return false;
    }

    // Remove key-value pair
    bool remove(K key)
    {
        if (!head)
            return false;

        if (head->key == key)
        {
            MapNode *temp = head;
            head = head->next;
            delete temp;
            size--;
            return true;
        }

        MapNode *prev = head;
        MapNode *current = head->next;
        while (current)
        {
            if (current->key == key)
            {
                prev->next = current->next;
                delete current;
                size--;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    // Get size
    int getSize() const { return size; }

    // Check if empty
    bool isEmpty() const { return size == 0; }

    // Clear all entries
    void clear()
    {
        while (head)
        {
            MapNode *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    // Iterate through all pairs (for-each simulation)
    void forEach(void (*callback)(K, V))
    {
        MapNode *current = head;
        while (current)
        {
            callback(current->key, current->value);
            current = current->next;
        }
    }

    // Display all pairs
    void display()
    {
        MapNode *current = head;
        cout << "{";
        while (current)
        {
            cout << current->key << ": " << current->value;
            if (current->next)
                cout << ", ";
            current = current->next;
        }
        cout << "}" << endl;
    }
};

#endif
