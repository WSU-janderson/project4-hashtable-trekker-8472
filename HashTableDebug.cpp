/**
 * HashTableDebug.cpp
 * Robert Pohl
 * Write your tests in this file
 * Project 4
 */
#include <iostream>
#include "HashTable.h"

using namespace std;


int main() {
    cout << "Starting hash table debug tester" << endl;

    // Basic construction
    size_t initCapacity = 8;
    HashTable ht(initCapacity);
    cout << "Hash table constructed with capacity " << initCapacity << endl;
    cout << "Hash table constructed with a size of " << ht.size() << endl;

    // Raw hash output
    string firstKey = "corned beef";
    size_t firstValue = 5;
    size_t testHash;
    testHash = ht.hashFunction(firstKey);
    cout << "Raw hash for key \"corned beef\" is ";
    cout << testHash << "." << endl;

    // Modulo index
    size_t index = testHash % initCapacity;
    cout << "Index after modulo is " << index << endl;

    // Insert and verify
    ht.insert("corned beef", 5);
    cout << "Inserted key \"" << firstKey << "\" with value " << firstValue << endl;

    // Size recheck
    cout << "Hash table after insertion is a size of " << ht.size() << endl;

    // Value Check
    optional<int> firstResult = ht.get(firstKey); // get ValuefirstKey, returns optional<int>.
    if (firstResult.has_value()) {
        cout << "firstKey: \"" << firstKey << "\" value is " <<  firstResult.value() << endl; // Prints success message.
    } else {
        cout << "Failure for key value pair" << endl; // Prints an error message.
    }

    cout << "Table is: " << ht << endl;

    cout << "Checking presence of key: " << firstKey << "." << endl;//is what's there there
    if (ht.contains(firstKey)) {
        cout << "It is there" << endl;
    } else {
        cout << "It is not there." << endl;
    }

    string absentKey = "sun screen";
    cout << "Checking presence of key: " << absentKey << "." << endl;
    if (!ht.contains(absentKey)) {
        cout << "It is properly not there." << endl;
    } else {
        cout << "It is improperly there" << endl;
    }

    cout << "Removing lone key, firstKey." << endl;

    bool removeCheck = ht.remove(firstKey);
    cout << "remove() returned: " << (removeCheck ? "true" : "false") << endl;

    cout << "Checking presence of key: " << firstKey << "." << endl;//is what's there there
    if (ht.contains(firstKey)) {
        cout << firstKey << " is there" << endl;
    } else {
        cout << firstKey << " is not there." << endl;
    }
    cout << "Table is: " << ht << endl;

    cout << "Debug tester complete" << endl;
    return 0;
}
