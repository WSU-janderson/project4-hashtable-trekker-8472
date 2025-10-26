/**
 * HashTable.h
 * Robert Pohl
 * CS 3100
 * Project 4
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <string>
#include <optional>
#include <cmath>
#include <iostream>

using namespace std;

/**
 * Forward declaration for the HashTable class, needed for the friend declaration
 * of the operator<< overload.
 */
class HashTableBucket;

enum class BucketType {NORMAL, ESS, EAR};

class HashTable {

    public:
    /**
     * Only a single constructor that takes an initial capacity for the table is
     * necessary. If no capacity is given, it defaults to 8 initially.
     */
    HashTable(size_t initCapacity = 8);
    ~HashTable() = default;
    HashTable(const HashTable& other) = default;
    HashTable& operator=(const HashTable& other) = default;

    /**
     * Insert a new key-value pair into the table. Duplicate keys are NOT allowed. The
     * method should return true if the insertion was successful. If the insertion was
     * unsuccessful, such as when a duplicate is attempted to be inserted, the method
     * should return false.
     */
    bool insert(string key, int value);

    /**
     * If the key is in the table, remove will "erase" the key-value pair from the
     * table. This might just be marking a bucket as empty-after-remove.
     */
    bool remove(string key);

    /**
    * contains returns true if the key is in the table and false if the key is not in
    * the table.
    */
    bool contains(const string& key) const;

    /**
    * If the key is found in the table, get will return the value associated with
    * that key. If the key is not in the table, get will return std::nullopt.
    * The method returns an optional<int>, which is a way to denote a method
    * might not have a valid value to return.
     */
    optional<int> get(const string& key) const;


    /**
     * The bracket operator lets us access values in the map using a familiar syntax.
     * It returns a reference to the value, which allows assignment (hashTable["key"] = 1234;).
     * If the key is not in the table, the situation results in undefined behavior
     * (no need to address attempts to access keys not in the table).
     */
    int& operator[](const string& key);

    /**
     * keys returns a std::vector with all of the keys currently in the table.
     * The length of the vector should be the same as the size of the hash table.
     */
    vector<string> keys() const;

    /**
     * alpha returns the current load factor of the table, or size/capacity.
     * The time complexity for this method must be O(1).
     */
    double alpha() const;

    /**
    * capacity returns how many buckets in total are in the hash table.
    * The time complexity for this algorithm must be O(1).
    */
    size_t capacity() const;

    /**
     * The size method returns how many key-value pairs are in the hash table.
     * The time complexity for this method must be O(1).
     */
    size_t size() const;

    /**
     * operator<< allows us to print the contents of our hash table using the normal syntax:
     * cout << myHashTable << endl;
     * This is not a method of HashTable, but is declared as a friend for private access.
     */
    friend ostream& operator<<(ostream& os, const HashTable& hashTable);

    private:
    // tableData will use a vector of HashTableBucket objects.
    vector<HashTableBucket> tableData;

    // Stores the pseudo-random probe offsets.
    vector<size_t> offsets;

    // Tracks the number of NORMAL (occupied) buckets (N) for O(1) size() and alpha()
    size_t currentSize;

    /**
     * Resizes the table and rehashes all existing elements when the load factor
     * (alpha) reaches or exceeds 0.5 (by doubling the size).
     */
    void resizeAndRehash();

    /**
     * Generates a new vector of pseudo-random probe offsets based on the new capacity.
     */
    void generateNewOffsets(size_t newCapacity);

    /**
     * Custom hash function to convert a string key into a home index.
     */
    size_t hashFunction(const string& key) const;

    /**
     * Helper to find the index of an existing key or the appropriate spot for insertion.
     */
    size_t findIndex(const string& key) const;

};

class HashTableBucket {
    public:

    /**
    * The default constructor can simply set the bucket type to ESS.
    *
    */
    HashTableBucket();
    ~HashTableBucket();//destructor
    HashTableBucket(const HashTableBucket& other) = default; //recommended by clion
    HashTableBucket& operator=(const HashTableBucket& other) = default; //recommended by clion

    /**
     * A parameterized constructor could initialize the key and value, as
     * well as set the bucket type to NORMAL.
     */
    HashTableBucket(string key, int value);

    /**
     * A load method could load the key-value pair into the bucket, which
     * should then also mark the bucket as NORMAL.
     */
    void load(string key, int value);

    /**
     * Mark the bucket as Empty After Remove (EAR).
     */
    void makeEAR();

    /**
     * This method would return whether the bucket is empty, regardless of
     * if it has had data placed in it or not (i.e., ESS or EAR).
     */
    bool isEmpty() const;

    /**
     * Checks if the bucket is currently storing a key-value pair (NORMAL).
     */
    bool isNormal() const;

    BucketType getType() const;

    const string& getKey() const;
    int& getValue();
    const int& getValue() const;

    /**
     * The stream insertion operator could be overloaded to print the
     * bucket's contents.
     */
    friend ostream& operator<<(ostream& os, const HashTableBucket& bucket);



    private:

    string key;
    int value;
    size_t capacity;


};

#endif
