#ifndef SEARCHING_H
#define SEARCHING_H

// Linear Search
// Works on any data type
// Checks each element one by one
template <typename T>
int linearSearch(T arr[], int size, T key)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == key) // if key found
            return i;      // return index
    }
    return -1; // not found
}

// Binary Search
// Array must be SORTED
// Faster than linear search
template <typename T>
int binarySearch(T arr[], int size, T key)
{
    int low = 0;
    int high = size - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid; // key found

        else if (arr[mid] < key)
            low = mid + 1; // search right side

        else
            high = mid - 1; // search left side
    }

    return -1; // not found
}

#endif
