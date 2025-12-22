#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <iostream>
#include <list>
#include <vector>
using namespace std;

// Template Hash Table with chaining
template <typename K, typename V>
class HashTable
{
private:
    vector<list<pair<K, V>>> table; // vector of lists for chaining
    int capacity;                   // total buckets

    // Simple hash function
    int hashFunc(K key) const
    {
        return hash<K>()(key) % capacity;
    }

public:
    // Constructor
    HashTable(int size = 10)
    {
        capacity = size;
        table.resize(capacity);
    }

    // Insert key-value pair
    void insert(K key, V value)
    {
        int index = hashFunc(key);
        // Check if key already exists
        for (auto &p : table[index])
        {
            if (p.first == key)
            {
                p.second = value; // update value
                return;
            }
        }
        table[index].push_back({key, value});
    }

    // Search by key
    bool search(K key, V &value) const
    {
        int index = hashFunc(key);
        for (const auto &p : table[index])
        {
            if (p.first == key)
            {
                value = p.second;
                return true;
            }
        }
        return false;
    }

    // Check if key exists (doesn't require default constructor)
    bool contains(K key) const
    {
        int index = hashFunc(key);
        for (const auto &p : table[index])
        {
            if (p.first == key)
            {
                return true;
            }
        }
        return false;
    }

    // Remove key
    bool remove(K key)
    {
        int index = hashFunc(key);
        for (auto it = table[index].begin(); it != table[index].end(); ++it)
        {
            if (it->first == key)
            {
                table[index].erase(it);
                return true;
            }
        }
        return false;
    }

    // Display all elements
    void display()
    {
        for (int i = 0; i < capacity; i++)
        {
            cout << "Bucket " << i << ": ";
            for (auto &p : table[i])
            {
                cout << "(" << p.first << "," << p.second << ") ";
            }
            cout << "\n";
        }
    }
};

#endif
