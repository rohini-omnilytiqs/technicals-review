// compile with g++ hashTable.cpp -std=c++11
#include <string>
#include <list>
#include <tuple>
#include <vector>
#include <functional>
#include <stdexcept>
#include <iostream>

using namespace std;
typedef vector<tuple<string, int>> bucket;

// This is open hashing; in closed, all KV pairs will be in the table itself
// Simple hash table class: array with chaining  
class SimpleHashTable {
private: 
    vector<bucket> table;
    int numBuckets;
    int getIndexOfKeyValueInBucket(string key);
    size_t getHash(string key);
    int getHashTableIndex(string key);

public:
    SimpleHashTable(int bucketCount = 10){
        numBuckets = bucketCount;
        table.resize(numBuckets);
    };
    void insert(string key, int value); // O(1)
    int retrieve(string key); // O(n)
    void remove(string key); // O(n)
    bool keyExists(string key); // O(n)
};

/**
 * Hashes a string key with built-in functionality.
 *
 * @param key Key to be hashed.
 * @return Hashed key.
 */
size_t SimpleHashTable::getHash(string key) {
    size_t hashedKey = hash<string>{}(key);
    return hashedKey;
}

/**
 * Gets index of a key in the hash table by performing modulo on hashed key.
 *
 * @param key Key to be stored with its value.
 * @return Index of the key in the hash table.
 */
int SimpleHashTable::getHashTableIndex(string key){
    size_t hashedKey = getHash(key);
    return int(hashedKey % numBuckets);
}

/**
 * Gets index of the key and value in the bucket.
 *
 * @param key Key to be stored with its value
 * @return Index of the key and value in the bucket.
 */
int SimpleHashTable::getIndexOfKeyValueInBucket(string key) {
    int hashTableIndex = getHashTableIndex(key);
    for (int i=0; i<table[hashTableIndex].size(); i++) {
        //cout << get<0>(table[hashTableIndex][i]) << " " << get<1>(table[hashTableIndex][i]) << endl;
        if (get<0>(table[hashTableIndex][i]) == key) {
            return i;
        }
    }
    return -1;
}

/**
 * Determines if the key is in the hash table.
 *
 * @param key Key to check.
 * @return True if key is already in the table, else false.
 */
bool SimpleHashTable::keyExists(string key) { 
    int indexOfKeyValueInBucket = getIndexOfKeyValueInBucket(key);
    if (indexOfKeyValueInBucket == -1) return false;
    else return true;
}

/**
 * Removes a key-value pair corresponding to the key given.
 *
 * @param key Key to be removed with its value.
 */
void SimpleHashTable::remove(string key) { 
    if (!keyExists(key)) {
        throw invalid_argument("Expected key that exists");
    }

    int hashTableIndex = getHashTableIndex(key);
    int indexOfKeyValueInBucket = getIndexOfKeyValueInBucket(key);
    table[hashTableIndex].erase(table[hashTableIndex].begin() + indexOfKeyValueInBucket);

}

/**
 * Inserts a key and value into the hash table.
 *
 * @param key Key to be stored with its value.
 * @param value Value corresponding to the key to be stored.
 */
void SimpleHashTable::insert(string key, int value) {
    if (keyExists(key)){
        remove(key);
    }
    int hashTableIndex = getHashTableIndex(key);
    table[hashTableIndex].push_back(tuple<string, int>{key, value});

}

/**
 * Retrieves a value from the hash table corresponding to the key given.
 *
 * @param key Key corresponding to the value to retrieve.
 * @return Value from hash table corresponding to the key.
 */
int SimpleHashTable::retrieve(string key){
    if (!keyExists(key)) {
        throw invalid_argument("Expected key that exists");
    }
    int hashTableIndex = getHashTableIndex(key);
    int indexOfKeyValueInBucket = getIndexOfKeyValueInBucket(key);
    return get<1>(table[hashTableIndex][indexOfKeyValueInBucket]);   
}

// Driver
int main() {
    SimpleHashTable myHashTable = SimpleHashTable(12);

    myHashTable.insert("key1", 1);
    myHashTable.insert("key2", 2);
    myHashTable.insert("key3", 3);

    if (myHashTable.keyExists("key4")) { 
        cout << "Key exists!" << endl;
    }
    else {
        cout << "Key doesn't exist!" << endl;
    }
 
    cout << "Key 2 corresponds to " << myHashTable.retrieve("key2") << endl;

    myHashTable.remove("key2");

    if (myHashTable.keyExists("key2")) { 
        cout << "Key exists!" << endl;
    }
    else {
        cout << "Key doesn't exist!" << endl;
    } 
    return 0;
}