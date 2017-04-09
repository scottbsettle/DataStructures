#pragma once
#include "SLList.h"

template<typename Type>
class HTable
{
private:
	SLList<Type>* m_HTlist;
	unsigned int (*funcptr)(const Type& v);
	int m_size;

public:
	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor 
	// Parameters : numOfBuckets - the number of buckets
	//              hFunction - pointer to the hash function for this table
	// Notes : constructs an empty hash table
	/////////////////////////////////////////////////////////////////////////////
	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v));

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys a hash table
		/////////////////////////////////////////////////////////////////////////////
		~HTable();

		/////////////////////////////////////////////////////////////////////////////
		// Function : Assignment Operator
		/////////////////////////////////////////////////////////////////////////////
		HTable<Type>& operator=(const HTable<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : Copy Constructor
		/////////////////////////////////////////////////////////////////////////////
		HTable(const HTable<Type>& that);

		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters : v - the item to insert into the hash table
		/////////////////////////////////////////////////////////////////////////////
		void insert(const Type& v);

		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to remove(if it is found)
		/////////////////////////////////////////////////////////////////////////////
		bool findAndRemove(const Type& v);



		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the hash table
		/////////////////////////////////////////////////////////////////////////////
		void clear();

		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to look for
		// Return : the bucket we found the item in or -1 if we didn’t find the item.
		/////////////////////////////////////////////////////////////////////////////
		int find(const Type& v) const;



};

template<typename Type>
inline HTable<Type>::HTable(unsigned int numOfBuckets, unsigned int(*hFunction)(const Type &v))
{
	m_HTlist = new SLList<Type>[numOfBuckets];
	funcptr = hFunction;
	m_size = numOfBuckets;
}

template<typename Type>
inline HTable<Type>::~HTable()
{
	clear();
	delete[] m_HTlist;
}

template<typename Type>
inline HTable<Type>& HTable<Type>::operator=(const HTable<Type>& that)
{
	// TODO: insert return statement here
	if (this != &that)
	{
		delete[] m_HTlist;
		m_HTlist = new SLList<Type>[that.m_size];
		funcptr = that.funcptr;
		m_size = that.m_size;
		for (int loop = 0; loop < that.m_size; loop++)
		{
			m_HTlist[loop] = that.m_HTlist[loop];
		}

	}
	return *this;
}

template<typename Type>
inline HTable<Type>::HTable(const HTable<Type>& that)
{
	delete[] m_HTlist;
	m_HTlist = new SLList<Type>[that.m_size];
	funcptr = that.funcptr;
	m_size = that.m_size;
	for (int loop = 0; loop <  that.size(); loop++)
	{
		m_HTlist[loop] = that.m_HTlist[loop];
	}
}

template<typename Type>
inline void HTable<Type>::insert(const Type & v)
{
	unsigned int tmp;
	tmp = funcptr(v);
	m_HTlist[tmp].addHead(v);
}

template<typename Type>
inline bool HTable<Type>::findAndRemove(const Type & v)
{
	unsigned int tmp;
	tmp = funcptr(v);
	SLLIter<Type> itter(m_HTlist[tmp]);
	itter.begin(); 
	while (!itter.end())
	{
		if (itter.current() == v)
		{
			m_HTlist[tmp].remove(itter);
			return true;
		}
		++itter;
	}
	return false;
}

template<typename Type>
inline void HTable<Type>::clear()
{
	for (int loop = 0; loop < m_size; loop++)
	{
		m_HTlist[loop].clear();
	}
}

template<typename Type>
inline int HTable<Type>::find(const Type & v) const
{
	unsigned int tmp;
	tmp = funcptr(v);
	SLLIter<Type> itter(m_HTlist[tmp]);
	itter.begin();
	while (!itter.end())
	{
		if (itter.current() == v)
		{	
			return tmp;
		}
		++itter;
	}
	return -1;
}
