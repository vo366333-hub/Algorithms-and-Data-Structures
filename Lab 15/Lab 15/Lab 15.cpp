#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class HashTable {
private:
    int capacity;
    vector<list<int>> table;

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    HashTable(int size) {
        capacity = size;
        table.resize(capacity);
    }

    void insertItem(int key) {
        int index = hashFunction(key);
        table[index].push_back(key);
    }

    bool searchItem(int key) {
        int index = hashFunction(key);
        for (int item : table[index]) {
            if (item == key) {
                return true;
            }
        }
        return false;
    }

    void deleteItem(int key) {
        int index = hashFunction(key);
        table[index].remove(key);
    }
};

void runBenchmark() {
    int dataSize = 100000;

    HashTable goodTable(dataSize);
    HashTable badTable(10);

    cout << " Time measurement (Insertion of " << dataSize << " elements)" << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < dataSize; i++) goodTable.insertItem(i);
    auto end = high_resolution_clock::now();
    cout << left << setw(35) << "Good table:"
        << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < dataSize; i++) badTable.insertItem(i);
    end = high_resolution_clock::now();
    cout << left << setw(35) << "Bad table:"
        << duration_cast<microseconds>(end - start).count() << " us" << endl;

    cout << "\n Time measurement" << endl;

    start = high_resolution_clock::now();
    goodTable.searchItem(99999);
    end = high_resolution_clock::now();
    cout << left << setw(35) << "Good table:"
        << duration_cast<microseconds>(end - start).count() << " us" << endl;

    start = high_resolution_clock::now();
    badTable.searchItem(99999);
    end = high_resolution_clock::now();
    cout << left << setw(35) << "Bad table (searching in a long list):"
        << duration_cast<microseconds>(end - start).count() << " us" << endl;
}

int main() {
    cout << "Laboratory 15 hashing" << endl << endl;
    runBenchmark();
    return 0;
}