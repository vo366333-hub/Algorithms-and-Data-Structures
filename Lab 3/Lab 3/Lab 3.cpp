#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>

using namespace std;
int linearSearch(const vector<int>& arr, int target) {
	for (size_t i = 0; i < arr.size(); ++i) {
		if (arr[i] == target) {
			return i;
		}
	}
	return -1; 
}

void bubbleSort(vector<int>& arr) {
	size_t n = arr.size();
	for (size_t i = 0; i < n - 1; ++i) {
		for (size_t j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void insertElement(vector<int>& arr, int index, int value) {
	if (index >= 0 && index <= arr.size()) {
		arr.insert(arr.begin() + index, value);
	}
	else {
		cout << "Error: Index out of bounds." << endl;
	}
}

void deleteElement(vector<int>& arr, int index) {
	if (index >= 0 && index < arr.size()) {
		arr.erase(arr.begin() + index);
	} else {
		cout << "Error: Index out of bounds." << endl;
	}
}

void displayArray(const vector<int>& arr) {
	for (int num : arr) {
		cout << num << " ";
	}
	cout << endl;
}
void printStatistics(const vector<int>& arr) {
	if (arr.empty()) return;

	int minVal = arr[0];
	int maxVal = arr[0];
	double sum = 0;

	for (int num : arr) {
		if (num < minVal) minVal = num;
		if (num > maxVal) maxVal = num;
		sum += num;
	}
	double average = sum / arr.size();
	cout << "Minimum: " << minVal << endl;
	cout << "Maximum: " << maxVal << endl;
	cout << "Average: " << average << endl;
}

void countFrequencies(const vector<int>& arr) {
	map<int, int> Frequencies;
	for (int num : arr) {
		Frequencies[num]++;
	}
	cout << "Element Frequencies:" << endl;
	for (const auto& pair : Frequencies) {
		cout << "Number " << pair.first << " appears " << pair.second << endl;
	}
}

int main() {
	// 1. Робота з масивами
	cout << "1. WORKING WITH ARRAYS" << endl;
	vector<int> numbers = { 5, 3, 8, 1, 2 };
	cout << "Original array: ";
	displayArray(numbers);

	int searchTarget = 3;
	int index = linearSearch(numbers, searchTarget);
	if (index != -1) {
		cout << "Element " << searchTarget << " found at index: " << index << endl;
	} else {
		cout << "Element " << searchTarget << " not found in the array." << endl;
	}

	cout << "Inserting element 10 at index 2." << endl;
	insertElement(numbers, 2, 10);
	displayArray(numbers);
	cout << "Deleting element at index 4." << endl;
	deleteElement(numbers, 4);
	displayArray(numbers);
	cout << "Array after sorting: " << endl;
	bubbleSort(numbers);
	displayArray(numbers);
	cout << endl;
	// 2. Робота зі словниками
	cout << "2. WORKING WITH DICTIONARIES" << endl;
	map<string, int> studentGrades;
	studentGrades["Alice"] = 95;
	studentGrades["Bob"] = 90;
	studentGrades["Charlie"] = 78;
	cout << "Student Grades:" << endl;
	for (const auto& pair : studentGrades) {
		cout << pair.first << ": " << pair.second << endl;
	}	

	studentGrades["Alice"] = 85;
	cout << "Alice's grade: " << studentGrades["Alice"] << endl;

	studentGrades.erase("Bob");
		cout << "Student bob removed from the dictionary." << endl;

	string searchKey = "Charlie";
	if (studentGrades.find(searchKey) != studentGrades.end()) {
		cout << "Found: " << searchKey << " has grade " << studentGrades[searchKey] << endl;
	}
	else {
		cout << "Key " << searchKey << " not found in the dictionary." << endl;
	}
	cout << endl;
	// 3. Статистика та групування
	cout << "3. STATISTICS AND GROUPING" << endl;
	vector<int> data = { 10, 10, 20, 20, 20, 30};
	cout << "Data: ";
	displayArray(data);

	printStatistics(data);
	cout << endl;
	countFrequencies(data);
	cout << endl;
	// 4. Аналіз часу виконання
	cout << "4. Execution time analysis" << endl;

	int dataSize = 10000000;
	vector<int> largeVector;
	map<int, int> largeMap;

	cout << "Generating data... Please wait." << endl;

	for (int i = 0; i < dataSize; ++i) {
		largeVector.push_back(i);
		largeMap[i] = i * 2;
	}

	int targetToFind = 9999999;

	auto start = chrono::high_resolution_clock::now();
	volatile int res1 = linearSearch(largeVector, targetToFind);
	auto end = chrono::high_resolution_clock::now();
	auto vectorDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

	start = chrono::high_resolution_clock::now();
	volatile int res2 = largeMap.find(targetToFind)->second;
	end = chrono::high_resolution_clock::now();
	auto mapDuration = chrono::duration_cast<chrono::microseconds>(end - start).count();

	cout << "Dataset size: " << dataSize << " elements." << endl;
	cout << "Linear search in vector took: " << vectorDuration << " microseconds." << endl;
	cout << "Key search in dictionary took: " << mapDuration << " microseconds." << endl;
	return 0;
}