#pragma once 

template<typename Type> class DLLIter;

template<typename Type>
class DLList
{
private:
	struct Node
	{
		Type Data;
		Node* m_next = nullptr, *m_prev = nullptr;
		Node(Type _x) { Data = _x; }
	};
	Node* m_head,* m_tail;
public:
	friend class DLLIter<Type>;
	 DLList();
	~DLList();
	DLList<Type>& operator=(const DLList<Type>& that);
	DLList(const DLList<Type>& that);
	void addHead(const Type& v);
	void addTail(const Type& v);
	void clear();
	void insert(DLLIter<Type>& index, const Type& v);
	void remove(DLLIter<Type>& index);

};

/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Notes : constructs an empty list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLList<Type>::DLList()
{
	m_head = nullptr;
	m_tail = nullptr;
}
/////////////////////////////////////////////////////////////////////////////
// Function : Destructor
// Notes : Destroys a list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLList<Type>::~DLList()
{
	clear();
}
/////////////////////////////////////////////////////////////////////////////
// Function : Assignment Operator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLList<Type>& DLList<Type>::operator=(const DLList<Type>& that)
{
	if (this != &that)
	{
		if (m_head != nullptr)
			clear();
		if (that.m_head != nullptr)
		{
			Node* tail = that.m_tail;
			while (tail)
			{
					addHead(tail->Data);
				tail = tail->m_prev;
			}

		}
	}

	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// Function : Copy Constructor
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLList<Type>::DLList(const DLList<Type>& that)
{
	m_head = nullptr;
	m_tail = nullptr;
	if (that.m_head != nullptr)
	{
		Node* tail = that.m_tail;
		while (tail)
		{
			addHead(tail->Data);
			tail = tail->m_prev;
		}

	}
}
/////////////////////////////////////////////////////////////////////////////
// Function : addHead
// Parameters : v - the item to add to the head of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void DLList<Type>::addHead(const Type& v)
{
	Node* temp = new Node(v);
	if (!m_tail)
		m_tail = temp;
	else
	{
		m_head->m_prev = temp;
		temp->m_next = m_head;
	}
	     m_head = temp;
		m_head->m_prev = nullptr;
	   

	
}
/////////////////////////////////////////////////////////////////////////////
// Function : addTail
// Parameters : v - the item to add to the tail of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void DLList<Type>::addTail(const Type& v)
{
	Node* temp = new Node(v);
	if (!m_head)
		m_head = temp;
	else
	{
		m_tail->m_next = temp;
		temp->m_prev = m_tail;
	}
	    m_tail = temp;
	m_tail->m_next = nullptr;
	
}
template<typename Type>
inline void DLList<Type>::clear()
{
	if (m_head != nullptr)
	{
		Node* temp;
		temp = m_head;
		while (m_head)
		{
			m_head = m_head->m_next;
			delete temp;
			temp = m_head;
		}
		m_head = nullptr;
		m_tail = nullptr;
	}

}

/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters :	index - an iterator to the location to insert at
//				v - the item to insert
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void DLList<Type>::insert(DLLIter<Type>& index, const Type& v)
{
	if (index.m_cur != nullptr)
	{
		if (index.m_cur == m_head)
		{
			addHead(v);
		}
		else if (index.m_cur == m_head)
		{
			addTail(v);
		}
		else
		{
			Node* temp = new Node(v);
			index.m_cur->m_prev->m_next = temp;
			temp->m_prev = index.m_cur->m_prev;
			temp->m_next = index.m_cur;
			index.m_cur->m_prev = temp;
			index.m_cur = temp;
		}
	}
}



/////////////////////////////////////////////////////////////////////////////
// Function : remove
// Parameters :	index - an iterator to the location to remove from
// Notes : do nothing on a bad iterator
/////////////////////////////////////////////////////////////////////////////



                               //    Iterator
template<typename Type>
void DLList<Type>::remove(DLLIter<Type>& index)
{
		if (index.m_cur != nullptr)
		{
			Node* temp;
			if (m_head != m_tail)
			{
				if (index.m_cur == m_head)
				{
					temp = m_head;
					m_head = m_head->m_next;
					index.m_cur = m_head;
					m_head->m_prev = nullptr;
				}
				else if (index.m_cur == m_tail)
				{
					temp = m_tail;
					m_tail = m_tail->m_prev;
					index.m_cur = m_tail;
					m_tail->m_next = nullptr;
				}
				else
				{
					temp = index.m_cur;
					index.m_cur->m_prev->m_next = index.m_cur->m_next;
					index.m_cur->m_next->m_prev = index.m_cur->m_prev;
					index.m_cur = index.m_cur->m_next;
				}
			}
			else
			{
				temp = m_head;
				m_head = nullptr;
				m_tail = nullptr;
				index.m_cur = m_head;
			}

			delete temp;
		}
	
}


template<typename Type>
class DLLIter
{
private:

	typename DLList<Type>::Node* m_cur;
	typename DLList<Type>& m_temp;
	friend class DLList<Type>;
public:
	
	DLLIter(DLList<Type>& listToIterate);
	void beginHead();
	void beginTail();
	bool end() const;
	DLLIter<Type>& operator++();
	DLLIter<Type>& operator--();
	Type& current() const;

};
/////////////////////////////////////////////////////////////////////////////
// Function : Constructor
// Parameters :	listToIterate - the list to iterate
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLLIter<Type>::DLLIter(DLList<Type>& listToIterate) : m_temp(listToIterate)
{
	m_cur = nullptr;
}

/////////////////////////////////////////////////////////////////////////////
// Function : beginHead
// Notes : moves the iterator to the head of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void DLLIter<Type>::beginHead()
{
	m_cur = m_temp.m_head;
}

/////////////////////////////////////////////////////////////////////////////
// Function : beginTail
// Notes : moves the iterator to the tail of the list
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void DLLIter<Type>::beginTail()
{
	m_cur = m_temp.m_tail;
}

/////////////////////////////////////////////////////////////////////////////
// Function : end
// Notes : returns true if we are at the end of the list, false otherwise
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool DLLIter<Type>::end() const
{
	if (m_cur == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////
// Function : operator++
// Notes : move the iterator forward one node
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator++()
{
	if (m_cur != nullptr)
	{
		m_cur = m_cur->m_next;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : operator--
// Notes : move the iterator backward one node
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
DLLIter<Type>& DLLIter<Type>::operator--()
{
	if (m_cur != nullptr)
	{
		m_cur = m_cur->m_prev;
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
// Function : current
// Notes : returns the item at the current iterator location
////////////////////////////////////////////////////////////////////////////
template<typename Type>
Type& DLLIter<Type>::current() const
{
	return m_cur->Data;
}