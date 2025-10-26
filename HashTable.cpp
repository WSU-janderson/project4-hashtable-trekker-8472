/**
* HashTable.cpp
 * Robert Pohl
 * CS 3100
 * Project 4
 */

#include "HashTable.h"

HashTable::HashTable(size_t initCapacity) {
}

bool HashTable::insert(string key, int value) {
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
}

void HashTable::resizeAndRehash() {
}

void HashTable::generateNewOffsets(size_t newCapacity) {
}

size_t HashTable::hashFunction(const string &key) const {
}

size_t HashTable::findIndex(const string &key) const {
}

ostream & operator<<(ostream &os, const HashTable &hashTable) {
}
