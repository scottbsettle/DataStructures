#pragma once 
#include "DynArray.h"
#include <algorithm>
template<typename Type>
class BinaryHeap : protected DynArray<Type>
{

public:
	~BinaryHeap();
	void enqueue(const Type &v);
	Type dequeue();
	Type& operator[](int index);
	void clear();
	unsigned int size();

};

/////////////////////////////////////////////////////////////////////////////
// Function : enqueue
// Parameters : v - the item to add to the heap
// Notes : after the new item is added, this function ensures that the 
//	smallest value in the heap is in [0]
//I*2+1 (left child)
//I * 2 + 2 (right child)
//(I - 1) / 2 (parent)

/////////////////////////////////////////////////////////////////////////////
template<typename Type>
BinaryHeap<Type>::~BinaryHeap()
{
	clear();
}
template<typename Type>
void BinaryHeap<Type>::enqueue(const Type &v)
{
	append(v);
	if (GetSize() > 1)
	{
		int x = GetSize() - 1;
		while (Data[x] < Data[(x - 1) / 2])
		{

			swap(Data[x], Data[(x - 1) / 2]);
			x = (x - 1) / 2;

			if (x == 0) break;
		}

	}
}

/////////////////////////////////////////////////////////////////////////////
// Function : dequeue 
// Return : the smallest item in the heap, or Type() if the heap is empty
// Notes : after the smallest item is dequeued, this function ensures that 
//	the smallest item is in [0]
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type BinaryHeap<Type>::dequeue()
{

	Type m_temp, m_temp2;
	int x = 0, y = 0;
	int test1, test2;
	m_temp = Data[0];
	m_temp2 = Data[Size - 1];

	if (GetSize() > 1)
	{
		Data[0] = m_temp2;
		for (int loop = 0; loop < (int)Size; loop++)
		{
			if ((x * 2) + 1 < (int)Size)
				test1 = Data[x] - Data[(x * 2) + 1];
			else
				test1 = Data[x];
			if ((x * 2) + 1 < (int)Size)
				test2 = Data[x] - Data[(x * 2) + 2];
			else
				test2 = Data[x];

			if (test1 > test2)
			{
				if (Data[x] < Data[(x * 2) + 1])
				{
					break;
				}

				swap(Data[(x * 2) + 1], Data[x]);
				x += (x * 2) + 1;
				if (x >(int)Size)
				{
					break;
				}
			}
			else if (test1 < test2)
			{
				if (Data[x] < Data[(x * 2) + 2])
				{
					break;
				}
				swap(Data[(x * 2) + 2], Data[x]);
				x += (x * 2) + 2;
				if (x > (int)Size)
				{
					break;
				}
			}
		}
	}
	Size--;
	return m_temp;

}

///////////////////////////////////////////////////////////////////////////////
// Function : operator[]
// Parameters : index - the index to access
// Return : Type& - the item in the index
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type& BinaryHeap<Type>::operator[](int index)
{
	return  Data[index];
}

/////////////////////////////////////////////////////////////////////////////
// Function : clear	
// Notes : clears the heap out
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void BinaryHeap<Type>::clear()
{
	DynArray::clear();
}

///////////////////////////////////////////////////////////////////////////////
// Function : size
// Return : the number of valid items in the heap
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
unsigned int BinaryHeap<Type>::size()
{
	return DynArray::GetSize();
}
