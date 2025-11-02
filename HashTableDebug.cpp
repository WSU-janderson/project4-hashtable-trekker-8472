/**
 * HashTableDebug.cpp
 * Robert Pohl
 * Write your tests in this file
 * Project 4
 */
#include <algorithm>
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

    cout << "Checking size and capacity again." << endl; //one of the previous test failed

    cout << "Previous Capacity: " << currentCapacity << " New Capacity: " << newCapacity << endl;

    cout << "Testing array like function []." << endl;

    cout << "Testing with third key: " << ht[thirdKey] <<endl;

    ht[thirdKey] = 100;

    cout << "Testing with third key: " << ht[thirdKey] <<endl;

    cout << "Testing [] for insertion." << endl;

    int sixthValue = 10;
    string sixthKey = "Waffle House browns done all the way";

    // cout << "Size prior to call: " << ht.size() << endl;
    //
    // ht[sixthKey] = sixthValue;
    //
    // cout << "Size post call: " << ht.size() << endl;
    //
    // cout << "Debug tester complete" << endl;

    cout << "Calling regular insertion" << endl;

    ht.insert(sixthKey, sixthValue);

    cout << "Current Capacity: " << ht.capacity() << ", Current Size: " << ht.size() << endl;

    cout << "Testing vector functionality." << endl;

    vector<string> expectedKeys = {firstKey, secondKey, thirdKey, fourthKey, fifthKey, sixthKey};

    vector<string> retrievedKeys = ht.keys();

    if (retrievedKeys.size() != expectedKeys.size()) {
        cout << "Wrong number of keys in vector." << endl;
    } else {
        cout << "Successfully retrieved vector." << endl;
    }

    cout << "Testing that the correct keys are returned using vector method sort." << endl;

    sort(retrievedKeys.begin(), retrievedKeys.end());
    sort(expectedKeys.begin(), expectedKeys.end());

    for (int i = 0; i < retrievedKeys.size(); ++i) {
        if (retrievedKeys[i] != expectedKeys[i]) { //remember that "W" is before "w" after run
            cout << "Wrong value for key " << retrievedKeys[i] << endl;
        } else {
            cout << "Successfully retrieved match key " << retrievedKeys[i] << endl;
        }
    }

    cout << "Current table: " << ht << endl;

    cout << "Deep copy function test: " << endl;

    int firstKeySourceValue = ht.get(firstKey).value();

    // 1. Test Copy
    cout << "\n1. Testing Copy Constructor: HashTable htCopy = ht;" << endl;
    HashTable htCopy = ht; // Uses copy constructor

    if (htCopy.size() == ht.size() && htCopy.capacity() == ht.capacity()) {
        cout << "Success" << endl;
    }
    else {
        cout << "Failure" << endl;
    }

    cout << "Modify value test." << endl;
    int firstTestKeyValue =8675309;

    ht[firstKey] = firstTestKeyValue;

    optional<int> copyCheck1 = htCopy.get(firstKey);
    if (copyCheck1.has_value() && copyCheck1.value() == firstKeySourceValue) {
        cout << "SUCCESS: \"" << firstKey << "\" is unchanged." << endl;
    } else {
        cout << "FAILURE: Correct the function code." << endl;
    }

    size_t currentCap = ht.capacity();
    cout << "Current Capacity: " << currentCap << ", Current Size: " << ht.size() << endl;

    // Define keys that should collide at a capacity of 16 (or whatever the current capacity is)
    // The actual hash values don't matter as long as they probe together.
    string keyAlpha = "Wrench"; // Collision Start
    string keyBravo = "Hammer"; // Collision Next
    string keyCharlie = "Saw";    // Insert into EAR
    string keyDelta = "Pliers";   // Simple Insert
    int valueAlpha = 100;
    int valueBravo = 200;
    int valueCharlie = 300;
    int valueDelta = 500;

    // 1. Setup the chain (Key Alpha and Key Bravo)
    cout << "1. Collides and EARs..." << endl;
    ht.insert(keyAlpha, valueAlpha);
    ht.insert(keyBravo, valueBravo); // keyBravo should be displaced/collides

    size_t keyAlphaIndex = ht.hashFunction(keyAlpha) % currentCap;
    size_t keyBravoIndex = ht.hashFunction(keyBravo) % currentCap;

    cout << "Key Alpha: " << keyAlpha << " index: " << keyAlphaIndex << endl;
    cout << "Key Bravo:" << keyBravo << " index: " << keyBravoIndex << " Displaced" << endl;

    size_t currentSizeTest = ht.size();
    cout << "Size before EARs: " << ht.size() << endl;

    ht.remove(keyBravo);

    if (!ht.contains(keyBravo) && ht.size() == currentSizeTest - 1) {
        cout << "SUCCESS: Key Bravo removed. EAR slot created." << endl;
    } else {
        cout << "FAILURE: Check Code" << endl;
    }

    cout << "Size after EARs: " << ht.size() << endl;

    cout << "Current Table: " << ht << endl;

    size_t sizeBeforeESSInsert = ht.size();
    ht.insert(keyCharlie, valueCharlie);

    if (ht.contains(keyCharlie) && ht.size() == sizeBeforeESSInsert + 1) {
        cout << "SUCCESS: inserted into ESS, size increased; now: " << ht.size() << "." << endl;
    } else {
        cout << "FAILURE: Review Code" << endl;
    }

    size_t sizeBeforeEARInsert = ht.size();

    bool insertCheck = ht.insert(keyDelta, valueDelta);

    if (insertCheck && ht.contains(keyDelta) && ht.size() == sizeBeforeEARInsert + 1) {
        cout << "SUCCESS: Key size increased to " << ht.size() << " after EAR insertion." << endl;
    } else {
        cout << "FAILURE: Review Code." << endl;
    }

    return 0;
}