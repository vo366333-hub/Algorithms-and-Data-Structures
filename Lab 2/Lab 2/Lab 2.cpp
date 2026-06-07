#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

unsigned long long factorialStandard(int n) {
	if (n == 0||n==1) {
		return 1;
	}
	return n * factorialStandard(n - 1);
}

unsigned long long factorialTail(int n, unsigned long long acc = 1) {
	if (n == 0 || n == 1) {
		return acc;
	}
	return factorialTail(n - 1, n * acc);
}

unsigned long long fibonacciStandard(int n) {
	if (n <= 1) {
		return n;
	}
	return fibonacciStandard(n - 1) + fibonacciStandard(n - 2);
}

unsigned long long fibonacciTail(int n, unsigned long long a = 0, unsigned long long b = 1) {
if (n == 0) return a;
if (n == 1) return b;
return fibonacciTail(n - 1, b, a + b);
}

unsigned long long powerTail(int base, int exp, unsigned long long acc = 1) {
	if (exp == 0) {
		return acc;
	}
	return powerTail(base, exp - 1, base * acc);
}

int main() {
	int factN = 20; 
	cout << "factorial(" << factN << ") " << endl;

	auto start = high_resolution_clock::now();
	cout << "Standard Factorial: " << factorialStandard(factN);
	auto end = high_resolution_clock::now();
	cout << " Time taken: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

	start = high_resolution_clock::now();
	cout << "Tail Recursive Factorial: " << factorialTail(factN);
	end = high_resolution_clock::now();
	cout << " Time taken: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;
	cout << endl;

	int fibN = 30;
	cout << "fibonacci(" << fibN << ") " << endl;

	start = high_resolution_clock::now();
	cout << "Standard Fibonacci: " << fibonacciStandard(fibN);
	end = high_resolution_clock::now();
	cout << " Time taken: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;

	start = high_resolution_clock::now();
	cout << "Tail Recursive Fibonacci: " << fibonacciTail(fibN);
	end = high_resolution_clock::now();
	cout << " Time taken: " << duration_cast<microseconds>(end - start).count() << " microseconds" << endl;
	cout << endl;

	int base = 2, exp = 10;
	cout << "power(" << base << ", " << exp << ") " << endl;
	cout << base << "^" << exp << " = " << powerTail(base, exp) << endl;
	return 0;
}