#include <iostream>
using namespace std;

#define tab "\t"

void FillRand(int arr[], const int size);
void Print(int arr[], const int size);

void main() {
	setlocale(LC_ALL, "");

	int n;
	cout << "Enter array size: "; cin >> n;
	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);

	int value;
	cout << "Enter added value: "; cin >> value;
	int* buffer = new int[n + 1] {};
	for (int i = 0; i < n; i++)
	{
		buffer[i] = arr[i];
	}
	delete[] arr;
	arr = buffer;
	arr[n++] = value;
	Print(arr, n);
	delete[] arr;
}

void FillRand(int arr[], const int size) {
	for (int i = 0; i < size; i++)
	{
		arr[i] = rand() % 100;
	}
}
void Print(int arr[], const int size) {
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << tab;
	}
	cout << endl;
}

