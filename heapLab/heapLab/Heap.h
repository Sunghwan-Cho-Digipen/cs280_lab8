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

class HeapException : public std::runtime_error
{
public:
	HeapException(const std::string& Message) : std::runtime_error(Message.c_str()) {};
};

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
	friend std::ostream& operator<<(std::ostream & out, Heap<U>& heap);
private:
    // Add your own private functions 
	void downwardHeapify(typename std::vector<T>::iterator iter, unsigned Index = 0);
	void upperHeapify(typename std::vector<T>::iterator iter);
	void sortHelperFunction(int index);
	bool(*compareFunc)(const T& a, const T& b);
	std::vector<T> data;
};

#include "Heap.hpp"
