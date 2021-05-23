/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Heap.h
Project: Lab 8 - Heaps
Author: Kevin wright
Creation date: 05/18/2021
******************************************************************/

#pragma once

#include <vector>
#include <algorithm>

template<class T>
class Heap {
public:
	Heap(bool(*compareFunc)(const T& a, const T& b));
	Heap(T* items, int numOfItems, bool(*compareFunc)(const T& a, const T& b));

	void Push(T newItem);
	T Pop();

	bool IsEmpty();
	void Sort();
	typename std::vector<T>::iterator Find(const T& val) { return std::find(data.begin(), data.end(), val); }
	void Update(typename std::vector<T>::iterator iter);

	template<class U>
	friend std::ostream& operator<<(std::ostream& out, Heap<U>& heap);
private:
	// Add your own private functions
	using Iter = typename std::vector<T>::iterator;
	int GetParentIndex(int index) const;
	int GetLeftChildIndex(int index) const;
	int GetRightChildIndex(int index) const;

	void HeapifyUp(int index, Iter start, Iter end);

	void HeapifyDown(int index, Iter start, Iter end);

	void BuildHeap();
	void Swap(T& a, T& b);
	bool(*compareFunc)(const T& a, const T& b);
	std::vector<T> data;
};

#include "Heap.hpp"
