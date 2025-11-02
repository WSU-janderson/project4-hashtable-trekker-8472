/**
* HashTable.cpp
 * Robert Pohl
 * CS 3100
 * Project 4
 */
// Including necessary headers for functionality
#include "HashTable.h"
#include <vector>
#include <string>
#include <optional>
#include <iostream>
#include <functional>
#include <utility>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * Only a single constructor that takes an initial capacity for the table is
 * necessary. If no capacity is given, it defaults to 8 initially.
 */
HashTable::HashTable(size_t initCapacity) {

     tableData = vector<HashTableBucket>(initCapacity); // constructs tableData
     currentSize = 0; // Assigns size

    srand(time(nullptr));//initialize randomness

    generateNewOffsets(initCapacity); //generates the offsets with the table generation

}

/**
 * Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
 * method should return true if the insertion was successful. If the insertion was
 * unsuccessful, such as when a duplicate is attempted to be inserted, the method
 * should return false.
 */
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

/**
 * If the key is in the table, remove will "erase" the key-value pair from the
 * table. This might just be marking a bucket as empty-after-remove.
 */
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

/**
* contains returns true if the key is in the table and false if the key is not in
* the table.
*/
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

/**
* If the key is found in the table, get will return the value associated with
* that key. If the key is not in the table, get will return std::nullopt.
* The method returns an optional<int>, which is a way to denote a method
* might not have a valid value to return.
*/
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

/**
 * The bracket operator lets us access values in the map using a familiar syntax.
 * It returns a reference to the value, which allows assignment (hashTable["key"] = 1234;).
 * If the key is not in the table, the situation results in undefined behavior
 * (no need to address attempts to access keys not in the table).
 */
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
    }//further behavior undefined
}

/**
 * keys returns a std::vector with all of the keys currently in the table. (e.g. normal)
 * The length of the vector should be the same as the size of the hash table.
 */
vector<string> HashTable::keys() const {
    vector<string> keys;
    for (const auto &bucket : tableData) {
        if (bucket.isNormal()) {
            keys.push_back(bucket.getKey());
        }
    }
    return keys;
}

/**
 * alpha returns the current load factor of the table, or size/capacity.
 * The time complexity for this method must be O(1).
 */
double HashTable::alpha() const {
    return static_cast<double>(size()) / capacity();//size fill check
}

/**
* capacity returns how many buckets in total are in the hash table.
* The time complexity for this algorithm must be O(1).
*/
size_t HashTable::capacity() const {
    return tableData.size();//return from un
}

/**
 * The size method returns how many key-value pairs are in the hash table.
 * The time complexity for this method must be O(1).
 */
size_t HashTable::size() const {
    return currentSize;
}

/**
 * Resizes the table and rehashes all existing elements when the load factor
 * (alpha) reaches or exceeds 0.5 (by doubling the size).
 */
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

/**
 * Generates a new vector of pseudo-random probe offsets based on the new capacity.
 */
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

/**
 * Custom hash function to convert a string key into a home index.
 */
size_t HashTable::hashFunction(const string &key) const {

    auto myhash = hash<string>{}; // Create a hash function
    size_t hash = myhash(key); // generates corned beef hash

    return hash; //return value
}

/**
 * Helper to find the index of an existing key or the appropriate spot for insertion.
 */
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

/**
 * operator<< allows us to print the contents of our hash table using the normal syntax:
 * cout << myHashTable << endl;
 * This is not a method of HashTable, but is declared as a friend for private access.
 */
ostream & operator<<(ostream &os, const HashTable &hashTable) {
    os << "Here is your hash table: {\n";
    size_t i = 0;
    while (i < hashTable.capacity()) {

        os << "  Bucket " << i << " is "; // show bucket number
        os << hashTable.tableData[i] << "\n";// show bucket contents

        ++i;
    }
    os << "}";
    return os;
}

/**
* The default constructor can simply set the bucket type to ESS.
*
*/
HashTableBucket::HashTableBucket() : value(0), type(BucketType::ESS) {}



/**
 * A parameterized constructor could initialize the key and value, as
 * well as set the bucket type to NORMAL.
 */
HashTableBucket::HashTableBucket(string key, int value) {
    this->key = std::move(key);
    this->value = value;
    this->type = BucketType::NORMAL;
}

/**
 * A load method could load the key-value pair into the bucket, which
 * should then also mark the bucket as NORMAL.
 */
void HashTableBucket::load(string key, int value) {
    this->key = key; //set key
    this->value = value; //set value
    this->type = BucketType::NORMAL;
}

/**
 * Mark the bucket as Empty After Remove (EAR).
 */
void HashTableBucket::makeEAR() {
    type = BucketType::EAR;
}

/**
 * This method would return whether the bucket is empty, regardless of
 * if it has had data placed in it or not (i.e., ESS or EAR).
 */
bool HashTableBucket::isEmpty() const {
    if (type == BucketType::ESS || type == BucketType::EAR) {
        return true;
    } else {
        return false;
    }
}

/**
 * Checks if the bucket is currently storing a key-value pair (NORMAL).
 */
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

/**
 * The stream insertion operator could be overloaded to print the
 * bucket's contents.
 */
ostream & operator<<(ostream &os, const HashTableBucket &bucket) {
    if (bucket.isNormal()) {
        // Print key and value if the bucket is occupied
        os << "Bucket key: " << bucket.key << " Bucket Value: " << bucket.value << endl;
    } else if (bucket.getType() == BucketType::EAR) {
        // Indicate the bucket is Empty After Remove
        os << "Bucket type is Empty After Removal." << endl;
    } else {
        // Indicate the bucket is Empty Search Sequence (ESS)
        os << "Bucket type is Empty Since Start." << endl;
    }
    return os;
}
