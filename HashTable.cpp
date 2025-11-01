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
#include <iostream>

using namespace std;


HashTable::HashTable(size_t initCapacity) {

     tableData = vector<HashTableBucket>(initCapacity); // constructs tableData
     currentSize = 0; // Assigns size

    srand(time(nullptr));//initialize randomness

    generateNewOffsets(initCapacity); //generates the offsets with the table generation

}

bool HashTable::insert(string key, int value) {

    if (alpha() > 0.5) { //resize if at least half full
        resizeAndRehash();
    }

    size_t index = hashFunction(key) % capacity();
    size_t firstEAR = capacity(); // hold for EAR entry

    for (size_t i = 0; i < capacity(); ++i) {//PROBE THROUGH THE TABLE
        size_t probe = (index + offsets[i]) % capacity();// via offsets
        HashTableBucket& bucket = tableData[probe];

        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {//REJECT EXISTING
            // Key already exists — reject insert
            return false;
        }

        if (bucket.getType() == BucketType::EAR && firstEAR == capacity()) {
            // Remember first EAR slot
            firstEAR = probe;
        }

        if (bucket.getType() == BucketType::ESS) {
            size_t target;
            if (firstEAR != capacity()) {
                // PUT IN EAR
                target = firstEAR;
            } else {
                // No EAR found
                target = probe;
            }
            HashTableBucket& insertBucket = tableData[target];
            insertBucket.load(key,value); //load values from function
            ++currentSize;
            return true;
        }
    }

    // Chain exhausted — insert into EAR if remembered
    if (firstEAR != capacity()) {
        HashTableBucket& insertBucket = tableData[firstEAR];
        insertBucket.load(key,value); //load values from function
        ++currentSize;
        return true;
    }

    return false; // table full, no usable slot
}


bool HashTable::remove(string key) {
    size_t index = hashFunction(key) % capacity();

    for (size_t i = 0; i < capacity(); ++i) {
        size_t probe = (index + offsets[i]) % capacity();
        HashTableBucket& bucket = tableData[probe];
        if (bucket.getType() == BucketType::ESS) {///breaks from function since no point in continuing
            return false;
        }
        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {//found
            bucket.makeEAR();
            --currentSize;
            return true;
        }
    }
    return false;
}

bool HashTable::contains(const string &key) const {
    size_t index = this->hashFunction(key) % this->capacity();
    size_t i = 0;

    // Probe table
    while (i < this->capacity()) {
        size_t probe = (index + offsets[i]) % this->capacity();
        const HashTableBucket& bucket = this->tableData[probe];

        // Stop if ESS (End Search Sequence)
        if (bucket.getType() == BucketType::ESS) {
            return false;
        }

        //  found
        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {
            return true;
        }
        i++;
    }

    // Key not found after exhausting search
    return false;
}

optional<int> HashTable::get(const string &key) const {
    // Calculate hash
    size_t index = this->hashFunction(key) % this->capacity();
    size_t i = 0;

    //  probe table
    while ( i < this->capacity()) {
        // Calculate index
        size_t probe = (index + offsets[i]) % this->capacity();
        const HashTableBucket& bucket = this->tableData[probe];

        // Stop if ESS
        if (bucket.getType() == BucketType::ESS) {
            return nullopt;
        }

        //  found
        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {
            // Return value
            return make_optional(bucket.getValue());
        }
        i++;
    }

    // Key not found
    return nullopt;
}

int & HashTable::operator[](const string &key) {

    size_t index = this->hashFunction(key) % this->capacity();

    for (size_t i = 0; i < this->capacity(); ++i) {
        // Probe using the randomized offset
        size_t probe = (index + offsets[i]) % this->capacity();
        HashTableBucket& bucket = this->tableData[probe];

        // 2. If found, return a reference to the existing value
        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {
            return bucket.getValue();
        }

        // Stop if ESS (End Search Sequence)
        if (bucket.getType() == BucketType::ESS) {
            break; // Key is definitely not in the table
        }
    }

}

vector<string> HashTable::keys() const {
    vector<string> keys;
    for (const auto &bucket : tableData) {
        if (bucket.isNormal()) {
            keys.push_back(bucket.getKey());
        }
    }
    return keys;
}

double HashTable::alpha() const {
    return static_cast<double>(size()) / capacity();//size fill check
}

size_t HashTable::capacity() const {
    return tableData.size();
}

size_t HashTable::size() const {
    return currentSize;
}

void HashTable::resizeAndRehash() {

    size_t newCapacity = capacity() * 2; //resize by double

    size_t count = 0;
    for (const auto& bucket : tableData) {
        if (bucket.isNormal()) {
            ++count; // count active entries
        }
    }

    vector<HashTableBucket> priorTable(count); // preallocate exact size
    size_t index = 0;
    for (const auto& bucket : tableData) {
        if (bucket.isNormal()) {
            priorTable[index++] = bucket; // copy active entries
        }
    }

    tableData = vector<HashTableBucket>(newCapacity); // allocate new table
    currentSize = 0;

    generateNewOffsets(newCapacity); // update probing logic

    for (const auto& bucket : priorTable) {
        insert(bucket.getKey(), bucket.getValue()); // reinsert with new capacity
    }
}

void HashTable::generateNewOffsets(size_t newCapacity) {
    // Implement pseudo-random offset generation using the previously seeded rand().

    // offsets vector cleared
    offsets.clear();

    // initialized offsets
    for (size_t i = 0; i < newCapacity; ++i) {
        offsets.push_back(i);
    }

    //  pseudo-random generation
    for (size_t i = newCapacity - 1; i > 0; --i) {
        // Generate random index j such that 0 <= j <= i
        size_t j = rand() % (i + 1);
        // Swap offsets[i] and offsets[j]
        swap(offsets[i], offsets[j]);
    }
}

size_t HashTable::hashFunction(const string &key) const {

    auto myhash = hash<string>{}; // Create a hash function
    size_t hash = myhash(key); // generates corned beef hash

    return hash; //return value
}

size_t HashTable::findIndex(const string &key) const {
    size_t index = this->hashFunction(key) % this->capacity();
    size_t i = 0;

    // Probe table
    while (i < this->capacity()) {
        //  probe index
        size_t probe = (index + offsets[i]) % this->capacity();
        const HashTableBucket& bucket = this->tableData[probe];

        // Stop if ESS
        if (bucket.getType() == BucketType::ESS) {
            // Key not found
            return this->capacity();
        }

        // Found the key
        if (bucket.getType() == BucketType::NORMAL && bucket.getKey() == key) {
            // Return index
            return probe;
        }
        i++;
    }

    // Key not found at all
    return this->capacity(); // same return for ess
}

// Default constructor
HashTableBucket::HashTableBucket() : value(0), type(BucketType::ESS) {}

HashTableBucket::HashTableBucket(string key, int value) {
}

void HashTableBucket::load(string key, int value) {
    this->key = key; //set key
    this->value = value; //set value
    this->type = BucketType::NORMAL;
}

void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}

bool HashTableBucket::isEmpty() const {
    if (type == BucketType::ESS || type == BucketType::EAR) {
        return true;
    } else {
        return false;
    }
}

bool HashTableBucket::isNormal() const {
    if (type == BucketType::NORMAL) {
        return true;
    } else {
        return false;
    }
}

BucketType HashTableBucket::getType() const {
    return type;
}

const string & HashTableBucket::getKey() const {
    return key;
}

int & HashTableBucket::getValue() {
    return value;
}

const int & HashTableBucket::getValue() const {
    return value;
}

ostream & operator<<(ostream &os, const HashTable &hashTable) {
}

ostream & operator<<(ostream &os, const HashTableBucket &bucket) {
}
