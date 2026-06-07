#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& arr) {
	int n = arr.size();
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int partition(vector<int>& arr, int low, int high) {
	int pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j] < pivot) {
			i++;
			swap(arr[i], arr[j]);
		}
	}
	swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

vector<int> generateRandomArray(int size) {
	vector<int> arr(size);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 10000);
	for (int i = 0; i < size; i++) {
		arr[i] = dis(gen);
	}
	return arr;
}

int main() {
	vector<int> sizes = {10000, 25000, 50000, 100000};
	cout << setw(15) << "Size" << setw(20) << "Bubble Sort (ms)" << setw(20) << "Quick Sort (ms)" << endl;
	for (int size : sizes) {
		vector<int> arr1 = generateRandomArray(size);
		vector<int> arr2 = arr1; // Copy for fair comparison
		auto start = chrono::high_resolution_clock::now();
		bubbleSort(arr1);
		auto end = chrono::high_resolution_clock::now();
		auto bubbleDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		start = chrono::high_resolution_clock::now();
		quickSort(arr2, 0, arr2.size() - 1);
		end = chrono::high_resolution_clock::now();
		auto quickDuration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
		cout << setw(15) << size << setw(20) << bubbleDuration << setw(20) << quickDuration << endl;
	}
	return 0;
}