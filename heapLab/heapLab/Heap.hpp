/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Heap.hpp
Project: Lab 8 - Heaps
Author: Sunghwan Cho
Creation date: 05/18/2021
******************************************************************/

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include "Heap.h"

template <class T>
Heap<T>::Heap(bool(*compareFunc)(const T& a, const T& b))
	:compareFunc(compareFunc)
{
}

template <class T>
Heap<T>::Heap(T* items, int numOfItems, bool(*compareFunc)(const T& a, const T& b))
	: compareFunc(compareFunc)
{
	data.reserve(numOfItems);//pre make 

	for (int i = 0; i < numOfItems; ++i)
	{
		data.push_back(items[i]);
	}

	BuildHeap();
}

template <class T>
void Heap<T>::Push(T newItem)
{
	data.push_back(newItem);
	std::cout << "Push:\t" << *this << std::endl;
	const int LastIndex = data.size() - 1;
	HeapifyUp(LastIndex, data.begin(), data.end());
}

template <class T>
T Heap<T>::Pop()
{
	T firstElement = data.front();
	*data.begin() = *(data.end() - 1);

	data.pop_back();

	std::cout << "Pop:\t" << *this << std::endl;

	HeapifyDown(0, data.begin(), data.end());

	return firstElement;
}

template <class T>
bool Heap<T>::IsEmpty()
{
	return data.empty();
}

template <class T>
void Heap<T>::Sort()
{
	const int DataSize = data.size();
	for (int i = 1; i < DataSize; ++i)
	{
		for (int parent = GetParentIndex(DataSize - i - 1); parent >= 0; --parent)
		{
			HeapifyDown(parent, data.begin() + i, data.end());
		}
	}
}

template <class T>
void Heap<T>::Update(typename std::vector<T>::iterator iter)
{
	const int index = iter - data.begin();

	int parent = GetParentIndex(index);
	if (compareFunc(*iter, data[parent]) == true)//has higher priority than parent so it should go up
	{
		HeapifyUp(index, data.begin(), data.end());
	}
	else
	{
		HeapifyDown(index, data.begin(), data.end());
	}
}

template <class T>
int Heap<T>::GetParentIndex(int index) const
{
	return (index - 1) / 2;
}

template <class T>
int Heap<T>::GetLeftChildIndex(int index) const
{
	return index * 2 + 1;
}

template <class T>
int Heap<T>::GetRightChildIndex(int index) const
{
	return index * 2 + 2;
}

template <class T>
void Heap<T>::HeapifyUp(int index, Iter start, Iter end)
{
	if (index == 0)
	{
		return;
	}

	const int ParentIndex = GetParentIndex(index);

	if (compareFunc(*(start + index), *(start + ParentIndex)) == true)
	{
		Swap(*(start + index), *(start + ParentIndex));
		HeapifyUp(ParentIndex, start, end);
	}
}

template <class T>
void Heap<T>::HeapifyDown(int index, Iter start, Iter end)
{
	int TempIndex = index;
	const int LeftIndex = GetLeftChildIndex(index);
	const int RightIndex = GetRightChildIndex(index);
	const int DataQuantity = end - start;
	if (LeftIndex > DataQuantity - 1)
	{
		return;
	}
	
	if (LeftIndex == DataQuantity - 1)
	{
		if (compareFunc(*(start + LeftIndex), *(start + index)) == true)
		{
			TempIndex = LeftIndex;
		}
	}
	else 
	{
		if (compareFunc(*(start + LeftIndex), *(start + RightIndex)) == true)
		{
			if (compareFunc(*(start + LeftIndex), *(start + index)) == true)
			{
				TempIndex = LeftIndex;
			}
		}
		else
		{
			if (compareFunc(*(start + RightIndex), *(start + index)) == true)
			{
				TempIndex = RightIndex;
			}
		}
	}

	if (TempIndex != index)
	{
		Swap(*(start + TempIndex), *(start + index));
		HeapifyDown(TempIndex, start, end);
	}
}

template <class T>
void Heap<T>::BuildHeap()
{
	for (int index = GetParentIndex(data.size() - 1); index >= 0; --index)
	{
		HeapifyDown(index, data.begin(), data.end());
	}
}

template <class T>
void Heap<T>::Swap(T& a, T& b)
{
	std::swap(a, b);
	std::cout << "Swap:\t" << *this << std::endl;
}


template<class T>
std::ostream& operator<<(std::ostream& out, Heap<T>& heap)
{
	if (heap.data.empty() == false) {
		for (int i = 0; i < static_cast<int>(heap.data.size()) - 1; i++) 
		{
			out << std::setw(3) << heap.data[i] << ",  ";
		}
		out << std::setw(3) << heap.data.back();
	}
	return out;
}

template<>
std::ostream& operator<<(std::ostream& out, Heap<std::string>& heap)
{
	for (unsigned int i = 0; i < heap.data.size() - 1; i++) 
	{
		out << heap.data[i] << ",  ";
	}
	out << heap.data.back();
	return out;
}