#ifndef PAIR_H
#define PAIR_H

// Custom Pair struct to replace std::pair
template <typename K, typename V>
struct Pair
{
    K first;
    V second;

    Pair() : first(K()), second(V()) {}
    Pair(K k, V v) : first(k), second(v) {}

    bool operator==(const Pair &other) const
    {
        return first == other.first && second == other.second;
    }

    bool operator<(const Pair &other) const
    {
        return first < other.first;
    }

    bool operator>(const Pair &other) const
    {
        return first > other.first;
    }
};

#endif
