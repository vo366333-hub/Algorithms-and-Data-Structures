#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }
        return node;
    }

    bool searchHelper(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (node->data == value) {
            return true;
        }
        if (value < node->data) {
            return searchHelper(node->left, value);
        }
        else {
            return searchHelper(node->right, value);
        }
    }

    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node* deleteHelper(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = deleteHelper(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteHelper(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteHelper(node->right, temp->data);
        }
        return node;
    }

    void preorderHelper(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderHelper(node->left);
        preorderHelper(node->right);
    }

    void inorderHelper(Node* node) {
        if (node == nullptr) return;
        inorderHelper(node->left);
        cout << node->data << " ";
        inorderHelper(node->right);
    }

    void postorderHelper(Node* node) {
        if (node == nullptr) return;
        postorderHelper(node->left);
        postorderHelper(node->right);
        cout << node->data << " ";
    }

public:
    BinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertHelper(root, value);
    }

    bool search(int value) {
        return searchHelper(root, value);
    }

    void deleteValue(int value) {
        root = deleteHelper(root, value);
    }

    void preorder() {
        preorderHelper(root);
        cout << endl;
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    void postorder() {
        postorderHelper(root);
        cout << endl;
    }
};

int main() {
    BinarySearchTree bst;

    cout << " 1. Checking basic operations " << endl;
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder traversal : ";
    bst.inorder();

    cout << "Preorder traversal: ";
    bst.preorder();

    cout << "Postorder traversal: ";
    bst.postorder();

    cout << "\nSearching for number 40: " << (bst.search(40) ? "Found" : "Not found") << endl;
    cout << "Searching for number 99: " << (bst.search(99) ? "Found" : "Not found") << endl;

    cout << "\nDeleting number 20 " << endl;
    bst.deleteValue(20);
    bst.inorder();

    cout << "Deleting number 30 " << endl;
    bst.deleteValue(30);
    bst.inorder();

    cout << "Deleting number 50 " << endl;
    bst.deleteValue(50);
    bst.inorder();

    cout << "\n 2. Benchmark " << endl;
    BinarySearchTree bigTree;
    int elementsCount = 10000;

    auto startInsert = high_resolution_clock::now();
    for (int i = 0; i < elementsCount; i++) {
        bigTree.insert(rand() % 100000);
    }
    auto endInsert = high_resolution_clock::now();
    cout << "Insertion time of " << elementsCount << " elements: "
        << duration_cast<microseconds>(endInsert - startInsert).count() << " us" << endl;

    auto startSearch = high_resolution_clock::now();
    bigTree.search(50000);
    auto endSearch = high_resolution_clock::now();
    cout << "Search time for one element in an array of " << elementsCount << " elements: "
        << duration_cast<microseconds>(endSearch - startSearch).count() << " us" << endl;

    return 0;
}