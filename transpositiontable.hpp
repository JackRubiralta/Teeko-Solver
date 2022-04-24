#include "teeko.hpp"
#include <cstring>



enum Flag : uint8_t { INVALID, EXACT, LOWERBOUND, UPPERBOUND };

struct Entry {
    int8_t value;
    Flag flag;
    uint8_t depth;
    Entry() : value(0), depth(0), flag(INVALID) {}
};

bool isPrime(unsigned int number) {
    for (int i = 2; i <= number / 2; ++i) {
        if (number % i == 0) { return false; }
    }
    return true;
}

unsigned int closestPrime(unsigned int number) {
    for (unsigned int n = number; n != 2; n++) {
        if (isPrime(n)) {
            return n;
        }
    }
    return 0;
}

class TranspositionTable {
    public:
        unsigned int size;
        Entry *entries;
        uint64_t *keys;

        unsigned int index(uint64_t key) {
            return key % size;
        }

        TranspositionTable(unsigned int size) : size(closestPrime(size)) {
            entries = new Entry[size];
            keys = new uint64_t[size];
            reset();
        }

        TranspositionTable() {}

        ~TranspositionTable() {
            delete[] entries;
            delete[] keys;
        }

        void reset() {
            memset(entries, 0, sizeof(Entry) * size);
            memset(keys, 0, sizeof(uint64_t) * size);
        }

        void insert(uint64_t key, Entry entry) {
            unsigned int pos = index(key);
            keys[pos] = key;
            entries[pos] = entry;
        }

        Entry lookup(uint64_t key) {
            unsigned int pos = index(key);
            if (keys[pos] == key) {
                return entries[pos];
            } else {
                return Entry();
            }
        }

        unsigned int length() {
            unsigned int length = 0;
            for (unsigned int i = 0; i < size; i++) {
                if (keys[i] != 0) {
                    length++;
                }
            }
            return length;
        }
};