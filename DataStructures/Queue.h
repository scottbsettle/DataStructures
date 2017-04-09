#pragma once

#include "stdafx.h"

/*
	Queues use FIFO (First In, First Out) ordering
			   LILO (Last In, Last Out)

		Ex:	car wash, midnight release of a game, a line at an amusement park, etc.

*/


// Keeps the class generic
//typedef int Item;


template<typename Item>
class Queue
{
private:

	struct Node
	{
		Item m_data;		// The value to store
		Node* m_next;		// The next one in the list

		// Ctor
		Node(const Item& _info);
	};

	Node* m_head;		// The oldest node in the list
	Node* m_tail;		// The newest node in the list

	int m_currSize;		// Current number of nodes allocated
	const int m_maxSize;// Max number to store at any given time

public:

	// Def ctor
	// In:	_maxSize		The max size for *THIS* particular queue
	Queue(int _maxSize = 0);	// 0 will represent unlimited

	// Dtor
	~Queue();

private:

	// Disabled copy ctor
	Queue(const Queue& _q) : m_maxSize(0) { }

	// Disabled assignment operator
	Queue& operator=(const Queue& q) { return *this; }

public:



	int GetCurrSize() const { return m_currSize;  }

	// Add an Item to the end of the queue
	// In:	_info		The Item to add
	// 
	// Return: True, if something was added
	bool Enqueue(const Item& _info);

	// Remove the Item from the front of the queue
	// In: _info		A "blank" Item
	//
	// Out: _info		The Item at the front
	// Return: True, if something was removed
	bool Dequeue(Item& _info);
};

// Ctor
template<typename Item>
Queue<Item>::Node::Node(const Item& _info)
{
	m_data = _info;
	m_next = NULL;
}

// Def ctor
//
// Const data members have to use the member initializer
template<typename Item>
Queue<Item>::Queue(int _maxSize) : m_maxSize(_maxSize)
{
	m_head = m_tail = NULL;
	m_currSize = 0;
}

// Dtor
template<typename Item>
Queue<Item>::~Queue()
{
	for (Node* temp = m_head; temp; temp = m_head)
	{
		m_head = m_head->m_next;
		delete temp;
	}
}


// Add an Item to the end of the queue
// In:	_info		The Item to add
// 
// Return: True, if something was added
template<typename Item>
bool Queue<Item>::Enqueue(const Item& _info)
{
	// Is the list full?
	if (m_maxSize != 0 && m_maxSize == m_currSize)
		return false;

	// Allocate space to store the information
	Node* newest = new Node(_info);

	// Did we run out of memory?
	if (NULL == newest)
		return false;

	// If the list is currently empty, set the head and tail pointer
	if (!m_head)
	{
		m_head = newest;
		m_tail = newest;
	}
	// Otherwise, go to the end of the list
	else
	{
		m_tail->m_next = newest;
		m_tail = newest;
	}

	++m_currSize;
	return true;

}

// Remove the Item from the front of the queue
// In: _info		A "blank" Item
//
// Out: _info		The Item at the front
// Return: True, if something was removed
template<typename Item>
bool Queue<Item>::Dequeue(Item& _info)
{
	// If the list is empty, GTFO
	if (!m_head)
		return false;

	// Copy over our value
	_info = m_head->m_data;

	// Update the list
	Node* temp = m_head;
	m_head = m_head->m_next;
	delete temp;

	m_currSize--;
	return true;
}
