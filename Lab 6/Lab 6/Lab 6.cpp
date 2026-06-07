#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int i = left;
    int j = right;

    int pivot = arr[left + (right - left) / 2];

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    if (left < j) {
        quickSort(arr, left, j);
    }
    if (i < right) {
        quickSort(arr, i, right);
    }
}

void runQuickSort(vector<int>& arr) {
    if (!arr.empty()) {
        quickSort(arr, 0, arr.size() - 1);
    }
}

void shellSort(vector<int>& arr) {
    int n = arr.size();

    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;

            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, 10000);

    for (int i = 0; i < size; i++) {
        arr[i] = distrib(gen);
    }
    return arr;
}

void testSortingAlgorithms(int size) {
    cout << "Test for array of size " << size << " elements" << endl;

    vector<int> originalArray = generateRandomArray(size);

    vector<int> arrQuick = originalArray;
    vector<int> arrShell = originalArray;

    auto startQuick = high_resolution_clock::now();
    runQuickSort(arrQuick);
    auto endQuick = high_resolution_clock::now();
    long long timeQuick = duration_cast<microseconds>(endQuick - startQuick).count();

    auto startShell = high_resolution_clock::now();
    shellSort(arrShell);
    auto endShell = high_resolution_clock::now();
    long long timeShell = duration_cast<microseconds>(endShell - startShell).count();

    cout << left << setw(20) << "Quick Sort:" << timeQuick << " us" << endl;
    cout << left << setw(20) << "Shell Sort:" << timeShell << " us" << endl;
    cout << endl;
}

int main() {
    cout << "Laboratory 6 quick sort and shell sort" << endl << endl;

    testSortingAlgorithms(100);
    testSortingAlgorithms(1000);
    testSortingAlgorithms(10000);

    return 0;
}