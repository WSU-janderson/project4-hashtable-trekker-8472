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

    // Test 1: Basic construction
    size_t initCapacity = 8;
    HashTable ht(initCapacity);
    cout << "Hash table constructed with capacity " << initCapacity << endl;

    // Test 2: Raw hash output
    string key = "corned beef";
    size_t testHash;
    testHash = ht.hashFunction(key);
    cout << "Raw hash for key \"corned beef\" is " << endl;
    cout << testHash << endl;

    // Test 3: Modulo index
    size_t index = testHash % initCapacity;
    cout << "Index after modulo is" << endl;
    cout << index << endl;

    // Test 4: Insert and verify
    ht.insert("corned beef", 5);
    cout << "Inserted key \"corned beef\" with value five" << endl;

    cout << "Debug tester complete" << endl;
    return 0;
}
