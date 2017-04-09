#pragma once
#include <iostream>
using namespace std;

template<typename Type>
class DynArray
{
protected:
	unsigned int Size, compacity;
	Type* Data, *temp;


public:

	DynArray();

	~DynArray();

	DynArray(const DynArray<Type>& that);


	DynArray<Type>& operator=(const DynArray<Type>& that);

	Type& operator[](const unsigned int index);

	const Type& operator[](const unsigned int index) const;

	unsigned int size() const;

	unsigned int capacity() const;

	void clear();

	void append(const Type& item);

	void reserve(const unsigned int & newCap = 0);
	void SetSize(int _x) { Size = _x; }
	void SetCapacity(int _x){ compacity = _x; }

	unsigned int GetSize() { return Size; }
	unsigned int GetCapacity(){ return compacity; }

};
template<typename Type>
DynArray<Type>::DynArray()
{
	Size = compacity = 0;
	Data = NULL;
}

template<typename Type>
DynArray<Type>::~DynArray()
{
	/*for (int loop = 0; loop < Size; loop++)
	{
	delete Data[loop];
	}*/
	delete[] Data;
	clear();
}

template<typename Type>
DynArray<Type>::DynArray(const DynArray<Type>& that)
{
	Size = that.Size;
	compacity = that.compacity;
	Data = new Type[compacity];
	for (int loop = 0; loop < (int)that.Size; loop++)
	{
		Data[loop] = that.Data[loop];
	}
}

template<typename Type>
DynArray<Type>& DynArray<Type>::operator=(const DynArray<Type>& that)
{
	if (this != &that)
	{
		Size = that.Size;
		compacity = that.compacity;
		delete[] Data;
		Data = new Type[compacity];
		for (int loop = 0; loop < (int)Size; loop++)
		{
			Data[loop] = that.Data[loop];
		}
	}
	return *this;
}

template<typename Type>
Type& DynArray<Type>::operator[](const unsigned int index)
{
	return Data[index];
}

template<typename Type>
const Type& DynArray<Type>::operator[](const unsigned int index) const
{
	return  Data[index];
}

template<typename Type>
unsigned int DynArray<Type>::size() const
{
	return Size;
}

template<typename Type>
unsigned int DynArray<Type>::capacity() const
{
	return compacity;
}

template<typename Type>
void DynArray<Type>::clear()
{
	Size = 0;
	compacity = 0;
}

template<typename Type>
void DynArray<Type>::append(const Type& item)
{
	if (Size == 0 && compacity == 0)
	{
		//Size = 1;
		if (compacity == 0)
			compacity = 1;
		//delete Data;
		Data = new Type[1];

	}
	else if (Size == compacity)
	{
		compacity *= 2;
		temp = new Type[compacity];
		for (int loop = 0; loop < (int)Size; loop++)
		{
			temp[loop] = Data[loop];
		}
		delete[] Data;
		//Data = new Type[compacity];
		Data = temp;

	}

	Size++;
	Data[Size - 1] = item;

}
/////////////////////////////////////////////////////////////////////////////
// Function : reserve
// Parameters : newCap - the new capacity
// Notes : 	- default parameter - reserve more space in the array, based on //		the expansion rate (100%, 1 minimum).
//		- non-default parameter, expand to the specified capacity
//		- if newCap is LESS than the current capacity, do nothing. 
//		This function should NOT make the array smaller.
/////////////////////////////////////////////////////////////////////////////

template<typename Type>
void DynArray<Type>::reserve(const unsigned int & newCap = 0)
{
	if (newCap == 0)
	{
		if (compacity == 0)
		{
			compacity = 1;
			//delete[] Data;
			Data = new Type[1];

		}
		else
		{
			compacity *= 2;
			temp = new Type[compacity];
			for (int loop = 0; loop < (int)Size; loop++)
			{
				temp[loop] = Data[loop];
			}
			delete[] Data;
			//Data = new Type[compacity];
			Data = temp;
			/*delete temp;*/
		}
	}
	else if (newCap > compacity)
	{
		compacity = newCap;
		temp = new Type[newCap];
		for (int loop = 0; loop < (int)Size; loop++)
		{
			temp[loop] = Data[loop];
		}
		delete[] Data;
		//Data = new Type[newCap];
		Data = temp;

	}
}