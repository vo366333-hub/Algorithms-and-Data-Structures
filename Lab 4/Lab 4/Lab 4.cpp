#include <iostream>
#include <vector>
#include <iomanip>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void printMatrix(const vector<vector<int>>& matrix) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			cout << setw(4) << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void traverseRow(const vector<vector<int>>& matrix, bool print = true) {
	for (int i = 0; i < matrix.size(); ++i) {
		for (int j = 0; j < matrix[i].size(); ++j) {
			if (print) cout << matrix[i][j] << " ";
		}
	}
	if (print) cout << endl;
}

void traverseColumn(const vector<vector<int>>& matrix, bool print = true) {
	if (matrix.empty()) return;
	for (int j = 0; j < matrix[0].size(); ++j) {
		for (int i = 0; i < matrix.size(); ++i) {
			if (print) cout << matrix[i][j] << " ";
		}
	}
	if (print) cout << endl;
}

void traverseSpiral(const vector<vector<int>>& matrix, bool print = true) {
	if (matrix.empty()) return;
	int top = 0, bottom = matrix.size() - 1;
	int left = 0, right = matrix[0].size() - 1;
	while (top <= bottom && left <= right) {
		for (int j = left; j <= right; ++j) {
			if (print) cout << matrix[top][j] << " ";
		}
		top++;
		for (int i = top; i <= bottom; ++i) {
			if (print) cout << matrix[i][right] << " ";
		}
		right--;
		if (top <= bottom) {
			for (int j = right; j >= left; --j) {
				if (print) cout << matrix[bottom][j] << " ";
			}
			bottom--;
		}
		if (left <= right) {
			for (int i = bottom; i >= top; --i) {
				if (print) cout << matrix[i][left] << " ";
			}
			left++;
		}
	}
	if (print) cout << endl;
}

vector<vector<int>> generateMatrix(int rows, int cols) {
	vector<vector<int>> matrix(rows, vector<int>(cols));
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 100);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			matrix[i][j] = dis(gen);
		}
	}
	return matrix;
}

int main() {
	cout << " MATRIX 5X5 " << endl;
	vector<vector<int>> matrix = generateMatrix(5, 5);
	printMatrix(matrix);
	cout << endl;

	cout << " Row-wise Traversal: " << endl;
	traverseRow(matrix);
	cout << endl;

	cout << " Column-wise Traversal: " << endl;
	traverseColumn(matrix);
	cout << endl;

	cout << " Spiral Traversal: " << endl;
	traverseSpiral(matrix);
	cout << endl;

	int size = 1000;
	cout << " MATRIX " << size << "X" << size << endl;
	vector<vector<int>> largeMatrix = generateMatrix(size, size);
	auto start = high_resolution_clock::now();
	traverseRow(largeMatrix, false);
	auto end = high_resolution_clock::now();
	cout << "Row-wise Traversal Time: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

	start = high_resolution_clock::now();
	traverseColumn(largeMatrix, false);
	end = high_resolution_clock::now();
	cout << "Column-wise Traversal Time: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

	start = high_resolution_clock::now();
	traverseSpiral(largeMatrix, false);
	end = high_resolution_clock::now();
	cout << "Spiral Traversal Time: " << duration_cast<microseconds>(end - start).count() << " us" << endl;

	return 0;
}