#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
using namespace std;

class Passenger
{
private:
    string name;
    int id;  // unique passenger ID
    int age; // passenger age

public:
    Passenger() : name(""), id(0), age(0) {}
    // Constructor
    Passenger(int _id, string _name, int _age)
        : id(_id), name(_name), age(_age) {}

    // Getters
    string getName() const { return name; }
    int getID() const { return id; }
    int getAge() const { return age; }

    // Setters
    void setName(string _name) { name = _name; }
    void setAge(int _age) { age = _age; }

    // Display passenger info
    void display() const
    {
        cout << "Passenger ID: " << id
             << ", Name: " << name
             << ", Age: " << age << endl;
    }

    // Operator overloading for comparisons
    bool operator==(const Passenger &other) const
    {
        return id == other.id;
    }
};

#endif
