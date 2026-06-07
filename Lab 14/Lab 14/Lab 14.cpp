#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

int linearSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid;
        }

        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

void runBenchmark(int size) {
    cout << " Array size: " << size << " elements" << endl;

    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }

    int target = -1;

    auto startLinear = high_resolution_clock::now();
    linearSearch(arr, target);
    auto endLinear = high_resolution_clock::now();
    long long timeLinear = duration_cast<microseconds>(endLinear - startLinear).count();

    auto startBinary = high_resolution_clock::now();
    binarySearch(arr, target);
    auto endBinary = high_resolution_clock::now();
    long long timeBinary = duration_cast<microseconds>(endBinary - startBinary).count();

    cout << left << setw(20) << "Linear search:" << timeLinear << " microseconds" << endl;
    cout << left << setw(20) << "Binary search:" << timeBinary << " microseconds" << endl << endl;
}

int main() {
    cout << "Laboratory 14 search algorithms" << endl << endl;

    runBenchmark(1000);
    runBenchmark(100000);
    runBenchmark(10000000);

    return 0;
}