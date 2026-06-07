#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class Queue {
private:
    int* arr;
    int capacity;
    int frontIndex;
    int rearIndex;
    int currentSize;

public:
    Queue(int size = 10) {
        capacity = size;
        arr = new int[capacity];
        frontIndex = 0;
        rearIndex = -1;
        currentSize = 0;
    }

    ~Queue() {
        delete[] arr;
    }

    void enqueue(int val) {
        if (currentSize == capacity) {
            int newCapacity = capacity * 2;
            int* newArr = new int[newCapacity];

            for (int i = 0; i < currentSize; i++) {
                newArr[i] = arr[(frontIndex + i) % capacity];
            }

            delete[] arr;
            arr = newArr;
            frontIndex = 0;
            rearIndex = currentSize - 1;
            capacity = newCapacity;
        }

        rearIndex = (rearIndex + 1) % capacity;
        arr[rearIndex] = val;
        currentSize++;
    }

    void dequeue() {
        if (!isEmpty()) {
            frontIndex = (frontIndex + 1) % capacity;
            currentSize--;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return arr[frontIndex];
        }
        return -1;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    int size() {
        return currentSize;
    }
};

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListQueue {
private:
    Node* head;
    Node* tail;
    int currentSize;

public:
    LinkedListQueue() {
        head = nullptr;
        tail = nullptr;
        currentSize = 0;
    }

    ~LinkedListQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    void enqueue(int val) {
        Node* newNode = new Node(val);
        if (isEmpty()) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        currentSize++;
    }

    void dequeue() {
        if (!isEmpty()) {
            Node* temp = head;
            head = head->next;
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            currentSize--;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return head->data;
        }
        return -1;
    }

    bool isEmpty() {
        return currentSize == 0;
    }

    int size() {
        return currentSize;
    }
};

void runBenchmark() {
    int operationsCount = 5000000;

    Queue arrayQueue;
    LinkedListQueue listQueue;

    cout << " Execution time comparison (" << operationsCount << " operations) " << endl;
    cout << left << setw(20) << "Structure" << setw(20) << "Enqueue Time (us)" << "Dequeue Time (us)" << endl;
    cout << string(60, '-') << endl;

    auto startArrayEnq = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) arrayQueue.enqueue(i);
    auto endArrayEnq = high_resolution_clock::now();
    auto timeArrayEnq = duration_cast<microseconds>(endArrayEnq - startArrayEnq).count();

    auto startArrayDeq = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) arrayQueue.dequeue();
    auto endArrayDeq = high_resolution_clock::now();
    auto timeArrayDeq = duration_cast<microseconds>(endArrayDeq - startArrayDeq).count();

    auto startListEnq = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) listQueue.enqueue(i);
    auto endListEnq = high_resolution_clock::now();
    auto timeListEnq = duration_cast<microseconds>(endListEnq - startListEnq).count();

    auto startListDeq = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) listQueue.dequeue();
    auto endListDeq = high_resolution_clock::now();
    auto timeListDeq = duration_cast<microseconds>(endListDeq - startListDeq).count();

    cout << left << setw(20) << "Array Queue" << setw(20) << timeArrayEnq << timeArrayDeq << endl;
    cout << left << setw(20) << "List Queue" << setw(20) << timeListEnq << timeListDeq << endl;
}

int main() {
    cout << "Laboratory 10 " << endl << endl;

    Queue testQueue;
    testQueue.enqueue(10);
    testQueue.enqueue(20);
    cout << "First element: " << testQueue.peek() << endl;
    testQueue.dequeue();
    cout << "First element after dequeue: " << testQueue.peek() << endl << endl;

    runBenchmark();

    return 0;
}