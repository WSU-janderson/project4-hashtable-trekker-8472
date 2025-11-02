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
    int firstValue = 5;
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
        cout << firstKey << " wasn't removed." << endl;
    } else {
        cout << firstKey << " was removed." << endl;
    }
    cout << "Table is: " << ht << endl;

    string secondKey = "roast beef";
    int secondValue = 15;
    string thirdKey = "pork";
    int thirdValue = 8;

    cout << "Inserting firstKey plus secondKey and thirdKey." << endl;
    ht.insert(firstKey, firstValue);
    ht.insert(secondKey, secondValue);
    ht.insert(thirdKey, thirdValue);

    // Check all three keys
    optional<int> result1 = ht.get(firstKey);
    if (result1.has_value()) {
        cout << "firstKey: \"" << firstKey << "\" value is " <<  result1.value() << endl; // Prints success message.
    } else {
        cout << "Failure for key value pair " << firstKey << endl; // Prints an error message.
    }

    optional<int> result2 = ht.get(secondKey);
    if (result2.has_value()) {
        cout << "secondKey: \"" << secondKey << "\" value is " <<  result2.value() << endl; // Prints success message.
    } else {
        cout << "Failure for key value pair " << secondKey << endl; // Prints an error message.
    }

    optional<int> result3 = ht.get(thirdKey);
    if (result3.has_value()) {
        cout << "thirdKey: \"" << thirdKey << "\" value is " <<  result3.value() << endl; // Prints success message.
    } else {
        cout << "Failure for key value pair " << thirdKey << endl; // Prints an error message.
    }


    cout << "Current Capacity: " << ht.capacity() << ", Current Size: " << ht.size() << endl;

    cout << "Need at least one more insert to call Resize and associated functions." << endl;

    string fourthKey = "sausage";
    int fourthValue = 1;

    ht.insert(fourthKey, fourthValue);

    cout << "Checking size and capacity again." << endl;

    cout << "Current Capacity: " << ht.capacity() << ", Current Size: " << ht.size() << endl;

    cout << ht.alpha() <<endl;

    int currentCapacity = ht.capacity();

    cout << "Trigger resize next time with fifth." << endl;

    string fifthKey = "browns";
    int fifthValue = 500;

    int newCapacity;

    ht.insert(fifthKey, fifthValue);

    newCapacity = ht.capacity();

    cout << "Checking size and capacity again." << endl;

    cout << "Previous Capacity: " << currentCapacity << " New Capacity: " << newCapacity << endl;

    cout << "Debug tester complete" << endl;
    return 0;
}
