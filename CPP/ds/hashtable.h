#ifndef HASHTABLES_H
#define HASHTABLES_H

#include <iostream>
#include "linkedlist.h"
#include "array.h"
#include "pair.h"
using namespace std;

// Template Hash Table with chaining using custom DS
template <typename K, typename V>
class HashTable
{
private:
    DynamicArray<LinkedList<Pair<K, V>>> table; // array of linked lists for chaining
    int capacity;                               // total buckets

    // Simple hash function for int keys
    int hashFunc(int key) const
    {
        return key % capacity;
    }

    // Hash for other types (string, etc.) - simple sum-based
    int hashFunc(const string &key) const
    {
        int sum = 0;
        for (int i = 0; i < (int)key.size(); i++)
            sum += (int)key[i];
        return sum % capacity;
    }

public:
    // Constructor
    HashTable(int size = 10) : table(size), capacity(size)
    {
        // Initialize each bucket with an empty LinkedList
        for (int i = 0; i < capacity; i++)
        {
            table.push_back(LinkedList<Pair<K, V>>());
        }
    }

    // Insert key-value pair
    void insert(K key, V value)
    {
        int index = hashFunc(key);
        LinkedList<Pair<K, V>> &bucket = table[index];
        // Check if key already exists
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket.get(i).first == key)
            {
                bucket.get(i).second = value; // update value
                return;
            }
        }
        bucket.push_back(Pair<K, V>(key, value));
    }

    // Search by key
    bool search(K key, V &value) const
    {
        int index = hashFunc(key);
        const LinkedList<Pair<K, V>> &bucket = table[index];
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket.get(i).first == key)
            {
                value = bucket.get(i).second;
                return true;
            }
        }
        return false;
    }

    // Check if key exists (doesn't require default constructor)
    bool contains(K key) const
    {
        int index = hashFunc(key);
        const LinkedList<Pair<K, V>> &bucket = table[index];
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket.get(i).first == key)
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
        LinkedList<Pair<K, V>> &bucket = table[index];
        for (int i = 0; i < bucket.size(); i++)
        {
            if (bucket.get(i).first == key)
            {
                bucket.removeAt(i);
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
            LinkedList<Pair<K, V>> &bucket = table[i];
            for (int j = 0; j < bucket.size(); j++)
            {
                cout << "(" << bucket.get(j).first << "," << bucket.get(j).second << ") ";
            }
            cout << "\n";
        }
    }
};

#endif
