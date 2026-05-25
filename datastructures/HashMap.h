#ifndef HASHMAP_H
#define HASHMAP_H

#include "LinkedList.h"
#include <string>

template <typename K, typename V>
struct HashEntry {
    K key;
    V value;

    HashEntry() : key(K()), value(V()) {}
    HashEntry(K k, V v) : key(k), value(v) {}

    // Overloaded == operator compares only the keys.
    bool operator==(const HashEntry& other) const {
        return this->key == other.key;
    }
};

template <typename K, typename V>
class HashMap {
private:
    static const size_t BUCKET_COUNT = 10007; // Prime number
    LinkedList<HashEntry<K, V>> buckets[BUCKET_COUNT];
    size_t size;

    // DJB2 Hash Algorithm for std::string keys
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

    // Insert or update key-value pair. Returns true if new element added.
    bool put(const K& key, V value) {
        size_t index = hashFunction(key);
        Node<HashEntry<K, V>>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                current->data.value = value; // Update existing
                return false;
            }
            current = current->next;
        }

        // Key does not exist, insert at head
        buckets[index].insertAtHead(HashEntry<K, V>(key, value));
        size++;
        return true;
    }

    // Retrieve value by key. Returns default V (e.g. nullptr) if not found.
    V get(const K& key) const {
        size_t index = hashFunction(key);
        Node<HashEntry<K, V>>* current = buckets[index].getHead();
        
        while (current != nullptr) {
            if (current->data.key == key) {
                return current->data.value;
            }
            current = current->next;
        }
        return V(); // default (nullptr for pointer)
    }

    // Remove entry by key
    bool remove(const K& key) {
        size_t index = hashFunction(key);
        if (buckets[index].remove(HashEntry<K, V>(key, V()))) {
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
    
    // Iterate through all values and return them in a newly constructed LinkedList
    // (Caller must manage the returned list memory)
    LinkedList<V>* values() const {
        LinkedList<V>* list = new LinkedList<V>();
        for (size_t i = 0; i < BUCKET_COUNT; ++i) {
            Node<HashEntry<K, V>>* current = buckets[i].getHead();
            while (current != nullptr) {
                list->insertAtTail(current->data.value);
                current = current->next;
            }
        }
        return list;
    }

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
