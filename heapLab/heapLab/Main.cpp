/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 8 - Heaps
Author: Kevin Wright
Creation date: 1/29/21
******************************************************************/
#include <iomanip>
#include <iostream>
#include "Heap.h"

template<class T>
static bool Less(const T& a, const T& b) { return a < b; }

template<class T>
static bool Greater(const T& a, const T& b) { return a > b; }

void Test1() {
	std::cout << "==================== Max Heap ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	int size = sizeof(array) / sizeof(*array);
	std::cout << "Before:\t";
	for (int i = 0; i < size-1; i++) {
		std::cout << std::setw(3) << array[i] << ",  ";
	}
	std::cout << std::setw(3) << array[size-1] << std::endl;
	Heap<int> heap(array, size, Greater);
	std::cout << "Heap:\t" << heap << std::endl;
}

void Test2() {
	std::cout << "==================== Min Heap ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	int size = sizeof(array) / sizeof(*array);
	std::cout << "Before:\t";
	for (int i = 0; i < size - 1; i++) {
		std::cout << std::setw(3) << array[i] << ",  ";
	}
	std::cout << std::setw(3) << array[size - 1] << std::endl;
	Heap<int> heap(array, size, Less);
	std::cout << "Heap:\t" << heap << std::endl;
}

void Test3() {
	std::cout << "==================== Duplicate Items ====================" << std::endl;
	int array[] = { 2, 2, 2, 2, 2, 2, 2 };
	int size = sizeof(array) / sizeof(*array);
	Heap<int> maxHeap(array, size, Greater);
	std::cout << "MaxHeap:\t" << maxHeap << std::endl;
	Heap<int> minHeap(array, size, Less);
	std::cout << "MinHeap:\t" << minHeap << std::endl;
}

void Test4() {
	std::cout << "==================== Max Heap Reverse Sort ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	int size = sizeof(array) / sizeof(*array);
	Heap<int> heap(array, size, Greater);

	std::cout << "Sort" << std::endl;
	heap.Sort();
	std::cout << "Reverse Sorted: " << heap << std::endl;
}

void Test5() {
	std::cout << "==================== Min Heap Sort ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	int size = sizeof(array) / sizeof(*array);
	Heap<int> heap(array, size, Less);

	std::cout << "Sort" << std::endl;
	heap.Sort();
	std::cout << "Sorted: " << heap << std::endl;
}

void Test6() {
	std::cout << "==================== Max Push/Pop ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	Heap<int> heap(Greater);
	for (int i : array) {
		heap.Push(i);
	}

	while (heap.IsEmpty() == false) {
		int poppedResult = heap.Pop();
		std::cout << "returned: " << poppedResult << std::endl;
	}
}


void Test7() {
	std::cout << "==================== Min Push/Pop ====================" << std::endl;
	int array[] = { 2, -10, 5, 2, 19, -1, 6, 8, -1, 6 };
	Heap<int> heap(Less);
	for (int i : array) {
		heap.Push(i);
	}

	while (heap.IsEmpty() == false) {
		int poppedResult = heap.Pop();
		std::cout << "returned: " << poppedResult << std::endl;
	}
}

void Test8() {
	std::cout << "==================== Strings ====================" << std::endl;
	std::string array[9] = { "the", "fast", "brown", "fox", "jumped", "over", "the", "lazy", "dog" };
	int size = sizeof(array) / sizeof(*array);
	Heap<std::string> minHeap(array, size, Less);
}

void Test9() {
	std::cout << "==================== Strings ====================" << std::endl;
	std::string array[9] = { "the", "fast", "brown", "fox", "jumped", "over", "the", "lazy", "dog" };
	int size = sizeof(array) / sizeof(*array);
	Heap<std::string> maxHeap(array, size, Greater);
}

void Test10() {
	std::cout << "==================== Strings ====================" << std::endl;
	std::string array[9] = { "the", "fast", "brown", "fox", "jumped", "over", "the", "lazy", "dog" };
	int size = sizeof(array) / sizeof(*array);
	Heap<std::string> minHeap(array, size, Less);

	std::vector<std::string>::iterator itThe = minHeap.Find(std::string("the"));
	*itThe = "The";
	std::cout << std::endl << "Change to \"The\":\t" << minHeap << std::endl;
	minHeap.Update(itThe);
	std::cout << "Change Done:\t" << minHeap << std::endl;

	itThe = minHeap.Find(std::string("The"));
    *itThe = "the";
	std::cout << std::endl << "Change to \"the\":\t" << minHeap << std::endl;
	minHeap.Update(itThe);
	std::cout << "Change back:\t" << minHeap << std::endl;
}


int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	void(*tests[])() = { Test1, Test2, Test3, Test4, Test5,
						Test6, Test7, Test8, Test9, Test10 };
	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests));

	if (test_num >= 0 && test_num <= numTests) {
		tests[test_num - 1]();
	} else {
		for (int i = 0; i < numTests; i++) {
			tests[i]();
			std::cout << std::endl << std::endl;
		}
	}
#ifdef _MSC_VER
	system("pause");
#endif
}