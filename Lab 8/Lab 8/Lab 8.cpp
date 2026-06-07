#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class SinglyLinkedList {
public:
    Node* head;
    Node* tail;
    int size;

    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void addFront(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void addBack(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void insertMiddle(int val) {
        if (size < 2) {
            addBack(val);
            return;
        }
        int mid = size / 2;
        Node* temp = head;
        for (int i = 0; i < mid - 1; i++) {
            temp = temp->next;
        }
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
        size++;
    }

    void deleteFront() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete temp;
        size--;
    }

    void deleteBack() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
    }

    ~SinglyLinkedList() {
        while (head) deleteFront();
    }
};

struct DoublyNode {
    int data;
    DoublyNode* next;
    DoublyNode* prev;
    DoublyNode(int val) : data(val), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    DoublyNode* head;
    DoublyNode* tail;
    int size;

    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void addFront(int val) {
        DoublyNode* newNode = new DoublyNode(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void addBack(int val) {
        DoublyNode* newNode = new DoublyNode(val);
        if (!head) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void insertMiddle(int val) {
        if (size < 2) {
            addBack(val);
            return;
        }
        int mid = size / 2;
        DoublyNode* temp = head;
        for (int i = 0; i < mid - 1; i++) {
            temp = temp->next;
        }
        DoublyNode* newNode = new DoublyNode(val);
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next) temp->next->prev = newNode;
        temp->next = newNode;
        size++;
    }

    void deleteFront() {
        if (!head) return;
        DoublyNode* temp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete temp;
        size--;
    }

    void deleteBack() {
        if (!head) return;
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            DoublyNode* temp = tail->prev;
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        size--;
    }

    ~DoublyLinkedList() {
        while (head) deleteFront();
    }
};

void runBenchmark() {
    int elementsCount = 50000;
    int operationsCount = 10000;

    SinglyLinkedList singlyList;
    DoublyLinkedList doublyList;

    for (int i = 0; i < elementsCount; i++) {
        singlyList.addBack(i);
        doublyList.addBack(i);
    }

    cout << "Performance comparison (lists with " << elementsCount << " elements) " << endl;
    cout << left << setw(35) << "Operation (10000 times)" << setw(20) << "Singly (us)" << "Doubly (us)" << endl;
    cout << string(70, '-') << endl;

    auto start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) singlyList.insertMiddle(i);
    auto end = high_resolution_clock::now();
    auto timeSinglyMiddle = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) doublyList.insertMiddle(i);
    end = high_resolution_clock::now();
    auto timeDoublyMiddle = duration_cast<microseconds>(end - start).count();

    cout << left << setw(35) << "Insertion in the middle" << setw(20) << timeSinglyMiddle << timeDoublyMiddle << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) singlyList.deleteFront();
    end = high_resolution_clock::now();
    auto timeSinglyFront = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) doublyList.deleteFront();
    end = high_resolution_clock::now();
    auto timeDoublyFront = duration_cast<microseconds>(end - start).count();

    cout << left << setw(35) << "Deletion from the front" << setw(20) << timeSinglyFront << timeDoublyFront << endl;

    start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) singlyList.deleteBack();
    end = high_resolution_clock::now();
    auto timeSinglyBack = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    for (int i = 0; i < operationsCount; i++) doublyList.deleteBack();
    end = high_resolution_clock::now();
    auto timeDoublyBack = duration_cast<microseconds>(end - start).count();

    cout << left << setw(35) << "Deletion from the back" << setw(20) << timeSinglyBack << timeDoublyBack << endl;
}

int main() {
    cout << "Laboratory 8 linked lists" << endl << endl;
    runBenchmark();
    return 0;
}