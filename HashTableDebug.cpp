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
    cout << "Index after modulo is" << endl;
    cout << index << endl;

    // Insert and verify
    ht.insert("corned beef", 5);
    cout << "Inserted key \"" << firstKey << "\" with value " << firstValue << endl;

    cout << "Debug tester complete" << endl;
    return 0;
}
