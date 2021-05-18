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
	for (int i = 0; i < numOfItems; i++)
	{
		data.emplace_back(*(items + i));
	}

	const unsigned firstParentIndex = static_cast<unsigned>((data.size() / 2) - 1);	// I don't know why but It didn't worked as 
	typename std::vector<T>::iterator iter = data.begin() + firstParentIndex;		// I run in for loop, while(iter-- != data.begin()), etc....
	while (true)																	//
	{																				//
		Update(iter);																//
		if (iter == data.begin())													//
		{																			//
			break;																	//
		}																			//
		--iter;																		//
	}																				//

}

template <class T>
void Heap<T>::Push(T newItem)
{
	data.emplace_back(newItem);
	std::cout << "Push:\t" << *this << std::endl;

	if (data.size() < 2)
	{
		return;
	}
	
	const unsigned firstParentIndex = static_cast<unsigned>((data.size() / 2) - 1);	// I don't know why but It didn't worked as 
	typename std::vector<T>::iterator iter = data.begin() + firstParentIndex;		// I run in for loop, while(iter-- != data.begin()), etc....
	while (true)																	//
	{																				//
		Update(iter);																//
		if (iter == data.begin())													//
		{																			//
			break;																	//
		}																			//
		--iter;																		//
	}																				//
}

template <class T>
T Heap<T>::Pop()
{
	if(data.size() <= 0)
	{
		throw HeapException("No data inside");
	}
	
	T returnValue = data.front();
	std::swap(data.front(), data.back());
	data.pop_back();
	std::cout << "Pop:\t" << *this << std::endl;

	if (data.size() < 2)
	{
		return returnValue;
	}
	
	const unsigned firstParentIndex = static_cast<unsigned>((data.size() / 2) - 1);	// I don't know why but It didn't worked as 
	typename std::vector<T>::iterator iter = data.begin() + firstParentIndex;		// I run in for loop, while(iter-- != data.begin()), etc....
	while (true)																	//
	{																				//
		Update(iter);																//
		if (iter == data.begin())													//
		{																			//
			break;																	//
		}																			//
		--iter;																		//
	}																				//

	return returnValue;
}

template <class T>
bool Heap<T>::IsEmpty()
{
	return data.empty();
}

template <class T>
void Heap<T>::Sort()
{
	if(data.size() < 2)
	{
		return;
	}

	sortHelperFunction(1); // starting from index 1.
}

template <class T>
void Heap<T>::Update(typename std::vector<T>::iterator iter)
{
	const unsigned currentLocation = static_cast<int>(iter - data.begin());
	if((currentLocation << 1) + 1 >= data.size()) // Check if it has a child data
	{
		upperHeapify(iter);
	}
	else
	{
		downwardHeapify(iter);
	}
}

template <class T>
void Heap<T>::downwardHeapify(typename std::vector<T>::iterator iter, unsigned Index) // downwardHeapify Parent->Child
{
	unsigned currentLocation = static_cast<unsigned>(iter - data.begin() - Index);	// 
																					// 
	unsigned LeftChildIndex = ((currentLocation + 1) << 1) - 1;						// 
	unsigned RightChildIndex = LeftChildIndex + 1;									// 
																					// 
	const unsigned Size = data.size() - Index;										// I should make downwardHeapify like this to make sure
																					// that I need to go through typical nodes not going through the
	if (Size <= LeftChildIndex)														// all of the nodes......
	{																				//
		return;																		//
	}																				//
																					//
	bool isSortLogicTrue = false;													//
																					//
	if (Size <= RightChildIndex)													//
	{																				//
		isSortLogicTrue = true;														//
	}																				//
	else																			//
	{																				//
		currentLocation += Index;													//
		LeftChildIndex += Index;													//
		RightChildIndex += Index;													//
		isSortLogicTrue = compareFunc(data[LeftChildIndex], data[RightChildIndex]);	//
	} // I did this if and only if that RightChildIndex == data.size();				
																					
	if (isSortLogicTrue == true)													
	{																				
		if (compareFunc(data[LeftChildIndex], data[currentLocation]) == true)		
		{
			std::swap(data[LeftChildIndex], data[currentLocation]);
			std::cout << "Swap:\t" << *this << std::endl;
			downwardHeapify(data.begin() + LeftChildIndex, Index);
		}
	}
	else
	{
		if (compareFunc(data[RightChildIndex], data[currentLocation]) == true)
		{
			std::swap(data[RightChildIndex], data[currentLocation]);
			std::cout << "Swap:\t" << *this << std::endl;
			downwardHeapify(data.begin() + RightChildIndex, Index);
		}
	}
}

template <class T>
void Heap<T>::upperHeapify(typename std::vector<T>::iterator iter) // This is for the UpperHeapify..... Child->Parent
{
	const unsigned currentLocation = static_cast<unsigned>(iter - data.begin());

	const unsigned parentIndex = ((currentLocation - 1) >> 1);

	if (currentLocation <= 0)
	{
		return;
	}
	
	if (compareFunc(data[currentLocation], data[parentIndex]) == true)	
	{
		std::swap(data[parentIndex], data[currentLocation]);
		std::cout << "Swap:\t" << *this << std::endl;
		upperHeapify(data.begin() + parentIndex);
	}
}

template <class T>
void Heap<T>::sortHelperFunction(int index)
{
	// I need to go through the Heapify recursively so I should do like this.
	// I can't find out more better way about how can I go through...
	// Just following the sort algorithm that prof. kevin showed.
	if ((index + 1) >= static_cast<int>(data.size()))
	{
		return;
	}

	const unsigned firstParentIndex = static_cast<unsigned>(((data.size() - index)) / 2 - 1) ;
	typename std::vector<T>::iterator iter = (data.begin() + index) + firstParentIndex;	// I don't know why but It didn't worked as 
	while (true)																		// I run in for loop, while(iter-- != data.begin()), etc....
	{																					//
		downwardHeapify(iter, index);													//
		if (iter == (data.begin() + index))												//
		{																				//
			break;																		//
		}																				//
		--iter;																			//
	}																					//
																						//
	sortHelperFunction(index + 1); 
}

template<class T>
std::ostream& operator<<(std::ostream& out, Heap<T>& heap)
{
	if (heap.data.empty() == false)
	{
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