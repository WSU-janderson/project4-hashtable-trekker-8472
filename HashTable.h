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

enum class BucketType {
    NORMAL, // The bucket is non-empty and currently storing a key-value pair
    ESS,            // Empty Since Start - the bucket has never had a key-value pair
    EAR             // Empty After Remove - the bucket previously stored a key-value pair, but it was later removed
};
class HashTable {
    public:
    /**
     * Only a single constructor that takes an initial capacity for the table is
     * necessary. If no capacity is given, it defaults to 8 initially.
     */
    HashTable(size_t initCapacity = 8);
    ~HashTable();

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

};


#endif
