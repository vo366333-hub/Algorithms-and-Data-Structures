#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class ArrayStack {
private:
    int* arr;
    int capacity;
    int topIndex;

public:
    ArrayStack(int size = 10) {
        capacity = size;
        arr = new int[capacity];
        topIndex = -1;
    }

    ~ArrayStack() {
        delete[] arr;
    }

    void push(int val) {
        if (topIndex == capacity - 1) {
            int newCapacity = capacity * 2;
            int* newArr = new int[newCapacity];

            for (int i = 0; i <= topIndex; i++) {
                newArr[i] = arr[i];
            }

            delete[] arr;
            arr = newArr;
            capacity = newCapacity;
        }
        topIndex++;
        arr[topIndex] = val;
    }

    void pop() {
        if (!isEmpty()) {
            topIndex--;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return arr[topIndex];
        }
        return -1;
    }

    bool isEmpty() {
        return topIndex == -1;
    }
};

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedListStack {
private:
    Node* topNode;

public:
    LinkedListStack() {
        topNode = nullptr;
    }

    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (!isEmpty()) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    int peek() {
        if (!isEmpty()) {
            return topNode->data;
        }
        return -1;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }
};

void runBenchmark() {
    int operationsCount = 5000000;

    ArrayStack arrayStack;
    LinkedListStack linkedListStack;

    cout << "Execution time comparison (" << operationsCount << " operations) " << endl;
    cout << left << setw(20) << "Structure" << setw(20) << "Push Time (us)" << "Pop Time (us)" << endl;
    cout << string(60, '-') << endl;

    auto startArrayPush = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) arrayStack.push(i);
    auto endArrayPush = high_resolution_clock::now();
    auto timeArrayPush = duration_cast<microseconds>(endArrayPush - startArrayPush).count();

    auto startArrayPop = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) arrayStack.pop();
    auto endArrayPop = high_resolution_clock::now();
    auto timeArrayPop = duration_cast<microseconds>(endArrayPop - startArrayPop).count();

    auto startListPush = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) linkedListStack.push(i);
    auto endListPush = high_resolution_clock::now();
    auto timeListPush = duration_cast<microseconds>(endListPush - startListPush).count();

    auto startListPop = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) linkedListStack.pop();
    auto endListPop = high_resolution_clock::now();
    auto timeListPop = duration_cast<microseconds>(endListPop - startListPop).count();

    cout << left << setw(20) << "Array Stack" << setw(20) << timeArrayPush << timeArrayPop << endl;
    cout << left << setw(20) << "Linked List Stack" << setw(20) << timeListPush << timeListPop << endl;
}

int main() {
    cout << "Laboratory 9" << endl << endl;

    ArrayStack testStack;
    testStack.push(10);
    testStack.push(20);
    cout << "Top element: " << testStack.peek() << endl;
    testStack.pop();
    cout << "Top element after pop: " << testStack.peek() << endl << endl;

    runBenchmark();

    return 0;
}