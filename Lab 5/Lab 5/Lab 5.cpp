#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

struct SortStats {
	long long comparisons = 0;
	long long swaps = 0;
	long long time = 0;
};

SortStats bubbleSort(vector<int>& arr) {
	SortStats stats;
	auto start = high_resolution_clock::now();
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			stats.comparisons++;
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
				stats.swaps++;
			}
		}
	}
	auto end = high_resolution_clock::now();
	stats.time = duration_cast<microseconds>(end - start).count();
	return stats;
}

SortStats insertionSort(vector<int>& arr) {
	SortStats stats;
	auto start = high_resolution_clock::now();
	int n = arr.size();
	for (int i = 1; i < n; i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			stats.comparisons++;
			arr[j + 1] = arr[j];
			j--;
			stats.swaps++;
		}
		if (j >= 0) stats.comparisons++;
		arr[j + 1] = key;
		stats.swaps++;
	}
	auto end = high_resolution_clock::now();
	stats.time = duration_cast<microseconds>(end - start).count();
	return stats;
}

vector<int> generateRandomArray(int size) {
	vector<int> arr(size);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 10000);
	for (int& x : arr) {
		x = dis(gen);
	}
	return arr;
}

void runTest(int size) {
	cout << "Array Size: " << size << endl;
	vector<int> original = generateRandomArray(size);
	vector<int> arr1 = original;
	vector<int> arr2 = original;
	SortStats bubbleStats = bubbleSort(arr1);
	SortStats insertionStats = insertionSort(arr2);

	cout << left << setw(15) << "Algorithm" << setw(15) << "Comparisons" << setw(15) << "Swaps" << setw(15) << "Time (us)" << endl;
	cout << string(60, '-') << endl;

	cout << left << setw(15) << "Bubble Sort"
		<< setw(15) << bubbleStats.comparisons
		<< setw(15) << bubbleStats.swaps
		<< bubbleStats.time << endl;

	cout << left << setw(15) << "Insertion Sort"
		<< setw(15) << insertionStats.comparisons
		<< setw(15) << insertionStats.swaps
		<< insertionStats.time << endl;

	cout << endl;
}

int main() {
	cout << "Sorting Algorithm Performance Comparison" << endl;
	vector<int> sizes = { 100, 500, 1000, 5000, 10000 };
	for (int size : sizes) {
		runTest(size);
	}

	return 0;

}