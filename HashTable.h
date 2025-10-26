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
};


#endif
