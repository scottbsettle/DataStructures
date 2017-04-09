#pragma once
#include "Card.h"



typedef Card Item;

// A singly linked list with FILO ordering
template<typename Item>
class Stack
{
private:

	struct Node
	{
		Item m_data;	
		Node* m_next;	
	};

	Node* m_top;		
	int m_currSize;		

public:

	// Default ctor
	Stack();

	// Dtor
	~Stack();

	
	int GetCurrSize() const { return m_currSize; }

	
	bool Push(const Item& _info);

	
	bool Pop(Item& _info);

	
	void Clear();

	
	const Item* Peek() const;
};

// Default ctor
template<typename Item>
Stack<Item>::Stack()
{
	m_currSize = 0;
	m_top = NULL;
}

// Dtor
template<typename Item>
Stack<Item>::~Stack()
{
	Clear();
}

template<typename Item>
bool Stack<Item>::Push(const Item& _info)
{
	// Make space for this new data
	Node* newTop = new Node;

	// Did new fail?
	if (!newTop)
		return false;

	// Fill in the node
	newTop->m_data = _info;
	newTop->m_next = m_top;

	// Update the top pointer
	m_top = newTop;

	m_currSize++;
	return true;
}

template<typename Item>
bool Stack<Item>::Pop(Item& _info)
{
	// Is the list empty?
	if (NULL == m_top)
		return false;

	// Copy over the value
	_info = m_top->m_data;

	// Update the stack
	Node* temp = m_top;
	m_top = m_top->m_next;
	delete temp;

	m_currSize--;
	return true;
}

// Empty out the stack for re-use
template<typename Item>
void Stack<Item>::Clear()
{
	Node* temp = m_top;

	// Loop until all nodes have been de
	while (m_top)
	{
		m_top = m_top->m_next;
		delete temp;
		temp = m_top;
	}

	m_currSize = 0;
}

// Look at the top thing without removing it
template<typename Item>
const Item* Stack<Item>::Peek() const
{
	return (m_top ? &m_top->m_data : NULL);
}