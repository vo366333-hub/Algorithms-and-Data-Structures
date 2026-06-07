#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = arr[0];
    for (int num : arr) {
        if (num > max_val) {
            max_val = num;
        }
    }

    vector<int> count(max_val + 1, 0);

    for (int num : arr) {
        count[num]++;
    }

    int index = 0;
    for (int i = 0; i <= max_val; i++) {
        while (count[i] > 0) {
            arr[index] = i;
            index++;
            count[i]--;
        }
    }
}

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void bucketSort(vector<int>& arr) {
    if (arr.empty()) return;

    int max_val = arr[0];
    for (int num : arr) {
        if (num > max_val) {
            max_val = num;
        }
    }

    int num_buckets = arr.size();
    vector<vector<int>> buckets(num_buckets);

    for (int i = 0; i < arr.size(); i++) {
        int bucket_index = (arr[i] * 1.0 / (max_val + 1)) * num_buckets;
        buckets[bucket_index].push_back(arr[i]);
    }

    for (int i = 0; i < num_buckets; i++) {
        insertionSort(buckets[i]);
    }

    int index = 0;
    for (int i = 0; i < num_buckets; i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            arr[index] = buckets[i][j];
            index++;
        }
    }
}

void runTest(string testName, vector<int> data) {
    cout << " " << testName << " (Size: " << data.size() << ")" << endl;

    vector<int> arrForCounting = data;
    vector<int> arrForBucket = data;

    auto startCounting = high_resolution_clock::now();
    countingSort(arrForCounting);
    auto endCounting = high_resolution_clock::now();
    long long timeCounting = duration_cast<microseconds>(endCounting - startCounting).count();

    auto startBucket = high_resolution_clock::now();
    bucketSort(arrForBucket);
    auto endBucket = high_resolution_clock::now();
    long long timeBucket = duration_cast<microseconds>(endBucket - startBucket).count();

    cout << left << setw(25) << "Counting Sort:" << timeCounting << " us" << endl;
    cout << left << setw(25) << "Bucket Sort:" << timeBucket << " us" << endl << endl;
}

int main() {
    int SIZE = 10000;

    random_device rd;
    mt19937 gen(rd());

    cout << "Lab 7 linear sorting algorithms" << endl << endl;

    vector<int> identicalData(SIZE, 42);
    runTest("Array with identical elements", identicalData);

    uniform_int_distribution<> largeRangeDist(1, 5000000);
    vector<int> largeRangeData(SIZE);
    for (int i = 0; i < SIZE; i++) {
        largeRangeData[i] = largeRangeDist(gen);
    }
    runTest("Array with large range", largeRangeData);

    uniform_int_distribution<> uniformDist(1, SIZE);
    vector<int> uniformData(SIZE);
    for (int i = 0; i < SIZE; i++) {
        uniformData[i] = uniformDist(gen);
    }
    runTest("Uniformly distributed elements", uniformData);

    return 0;
}