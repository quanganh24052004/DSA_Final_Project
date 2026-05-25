#ifndef HASHMAP_H
#define HASHMAP_H

#include "LinkedList.h"
#include <string>

// Forward declaration of Student to avoid circular dependency
class Student;

struct HashEntry {
    std::string key;
    Student* value;

    HashEntry() : key(""), value(nullptr) {}
    HashEntry(std::string k, Student* v) : key(k), value(v) {}

    // Overloaded == operator compares only the keys.
    // This allows LinkedList<HashEntry>::remove and search to work perfectly.
    bool operator==(const HashEntry& other) const {
        return this->key == other.key;
    }
};

class HashMap {
private:
    static const size_t BUCKET_COUNT = 10007; // Prime number for 10k records to minimize collisions
    LinkedList<HashEntry> buckets[BUCKET_COUNT];
    size_t size;

    // DJB2 Hash Algorithm: Highly efficient with low collision rates for strings
    size_t hashFunction(const std::string& key) const {
        size_t hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        }
        return hash % BUCKET_COUNT;
    }

public:
    HashMap() : size(0) {}

    ~HashMap() {
        clear();
    }

    // Disable copy constructor and assignment operator
    HashMap(const HashMap&) = delete;
    HashMap& operator=(const HashMap&) = delete;

    void clear() {
        for (size_t i = 0; i < BUCKET_COUNT; ++i) {
            buckets[i].clear();
        }
        size = 0;
    }

    // Insert or update key-value pair. Returns true if new element added, false if updated.
    bool put(const std::string& key, Student* value) {
        size_t index = hashFunction(key);
        Node<HashEntry>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value; // Update existing
                return false;
            }
            current = current->next;
        }

        // Key does not exist, insert at head
        buckets[index].insertAtHead(HashEntry(key, value));
        size++;
        return true;
    }

    // Retrieve value by key. Returns nullptr if not found.
    Student* get(const std::string& key) const {
        size_t index = hashFunction(key);
        Node<HashEntry>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                return current->data.value;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Remove entry by key. Returns true if found and removed, false otherwise.
    bool remove(const std::string& key) {
        size_t index = hashFunction(key);
        // Uses the overloaded == operator in HashEntry (which compares key)
        if (buckets[index].remove(HashEntry(key, nullptr))) {
            size--;
            return true;
        }
        return false;
    }

    size_t getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }
    
    // For debug/QC: count total collisions
    size_t getCollisionCount() const {
        size_t collisions = 0;
        for (size_t i = 0; i < BUCKET_COUNT; ++i) {
            size_t bucketSize = buckets[i].getSize();
            if (bucketSize > 1) {
                collisions += (bucketSize - 1);
            }
        }
        return collisions;
    }
};

#endif // HASHMAP_H
