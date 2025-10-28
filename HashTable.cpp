/**
* HashTable.cpp
 * Robert Pohl
 * CS 3100
 * Project 4
 */
// https://learn.zybooks.com/zybook/WRIGHTCS3100_5100AndersonFall2025/chapter/9/section/3 poss useful
#include "HashTable.h"
#include <vector>
#include <string>
#include <optional>
#include <cmath>
#include <iostream>

using namespace std;


HashTable::HashTable(size_t initCapacity) {

     tableData = vector<HashTableBucket>(initCapacity); // Default-constructs tableData
     currentSize = 0; // Assigns size

    generateNewOffsets(initCapacity); //generates the offsets with the table generation

}

bool HashTable::insert(string key, int value) {


    size_t index = hashFunction(key) % capacity();
    size_t firstEAR = capacity(); // hold for EAR entry

    for (size_t i = 0; i < capacity(); ++i) {
        size_t probe = (index + i) % capacity();
        HashTableBucket& bucket = tableData[probe];

        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {
            // Key already exists — reject insert
            return false;
        }

        if (bucket.getType() == BucketType::EAR && firstEAR == capacity()) {
            // Remember first EAR slot
            firstEAR = probe;
        }

        if (bucket.getType() == BucketType::ESS) {
            // ESS found — insert into EAR if remembered, else here
            size_t target = (firstEAR != capacity()) ? firstEAR : probe;
            HashTableBucket& insertBucket = tableData[target];
            insertBucket.setKey(key);
            insertBucket.setValue(value);
            insertBucket.setType(BucketType::NORMAL);
            ++currentSize;
            return true;
        }
    }

    // Chain exhausted — insert into EAR if remembered
    if (firstEAR != capacity()) {
        HashTableBucket& insertBucket = tableData[firstEAR];
        insertBucket.setKey(key);
        insertBucket.setValue(value);
        insertBucket.setType(BucketType::NORMAL);
        ++currentSize;
        return true;
    }

    return false; // table full, no usable slot
}


bool HashTable::remove(string key) {
}

bool HashTable::contains(const string &key) const {
}

optional<int> HashTable::get(const string &key) const {
}

int & HashTable::operator[](const string &key) {
}

vector<string> HashTable::keys() const {
}

double HashTable::alpha() const {
}

size_t HashTable::capacity() const {
}

size_t HashTable::size() const {
    return currentSize;
}

void HashTable::resizeAndRehash() {

    size_t newCapacity = capacity() * 2; //resize by double

    size_t count = 0;
    for (const auto& bucket : tableData) {
        if (bucket.getType() == BucketType::NORMAL) {
            ++count; // count active entries
        }
    }

    vector<HashTableBucket> oldTable(count); // preallocate exact size
    size_t index = 0;
    for (const auto& bucket : tableData) {
        if (bucket.getType() == BucketType::NORMAL) {
            oldTable[index++] = bucket; // copy active entries
        }
    }

    tableData = vector<HashTableBucket>(newCapacity); // allocate new table
    currentSize = 0;

    generateNewOffsets(newCapacity); // update probing logic

    for (const auto& bucket : oldTable) {
        insert(bucket.getKey(), bucket.getValue()); // reinsert with new capacity
    }
}

void HashTable::generateNewOffsets(size_t newCapacity) {
}

size_t HashTable::hashFunction(const string &key) const {

    auto myhash = hash<string>{}; // Create a hash function
    size_t hash = myhash(key); // generates corned beef hash

    return hash; //return value
}

size_t HashTable::findIndex(const string &key) const {
}

// Default constructor
HashTableBucket::HashTableBucket() : value(0), type(BucketType::ESS) {}

HashTableBucket::HashTableBucket(string key, int value) {
}

void HashTableBucket::load(string key, int value) {
}

void HashTableBucket::makeEAR() {
}

bool HashTableBucket::isEmpty() const {
}

bool HashTableBucket::isNormal() const {
}

BucketType HashTableBucket::getType() const {
}

const string & HashTableBucket::getKey() const {
}

int & HashTableBucket::getValue() {
}

const int & HashTableBucket::getValue() const {
}

ostream & operator<<(ostream &os, const HashTable &hashTable) {
}

ostream & operator<<(ostream &os, const HashTableBucket &bucket) {
}
