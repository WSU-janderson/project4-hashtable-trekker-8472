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
