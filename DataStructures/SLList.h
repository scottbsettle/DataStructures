#pragma once
template<typename Type> class SLLIter;

template<typename Type>
class SLList
{
private:

	struct Node
	{
		Type Data;
		Node* m_next = nullptr;
		Node(){ Data = nullptr; }
		Node(Type _data){ Data = _data; }
	};
	Node* m_head;
	int m_size;
public:
	friend class SLLIter<Type>;
	SLList();
	~SLList();
	SLList<Type>& operator=(const SLList<Type>& that);
	SLList(const SLList<Type>& that);
	void addHead(const Type& v);
	void clear();
	void insert(SLLIter<Type>& index, const Type& v);
	void remove(SLLIter<Type>& index);
	unsigned int size() const{ return m_size; }
	

};
template<typename Type>
SLList<Type>::SLList()
{
	m_head = nullptr;
	m_size = 0;

}
template<typename Type>
SLList<Type>::~SLList()
{
	clear();
}
template<typename Type>
SLList<Type>& SLList<Type>::operator=(const SLList<Type>& that)
{
	if (this != &that )
	{
		clear();
		if (that.m_size > 0)
		{
			
			m_head = new Node(that.m_head->Data);
			Node* temp2;
			Node* temp3;
			temp2 = that.m_head->m_next;
			temp3 = m_head;
			for (int loop = 0; loop < that.m_size - 1; loop++)
			{
				Node* temp = new Node(temp2->Data);
				temp2 = temp2->m_next;
				temp3->m_next = temp;
				temp3 = temp3->m_next;


			}
			m_size = that.m_size;
		}
	}
	return *this;
}
template<typename Type>
SLList<Type>::SLList(const SLList<Type>& that)
{
	if (m_size > 0)
	clear();
	if (that.m_size > 0)
	{

		m_head = new Node(that.m_head->Data);
		Node* temp2;
		Node* temp3;
		temp2 = that.m_head->m_next;
		temp3 = m_head;
		for (int loop = 0; loop < that.m_size - 1; loop++)
		{
			Node* temp = new Node(temp2->Data);
			temp2 = temp2->m_next;
			temp3->m_next = temp;
			temp3 = temp3->m_next;


		}
		m_size = that.m_size;
	}
	
}
template<typename Type>
void SLList<Type>::addHead(const Type& v)
{
		Node* temp = new Node(v);
		temp->m_next = m_head;
		m_head = temp;
		m_size++;
}
template<typename Type>
void SLList<Type>::clear()
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
			m_size--;
		}
	}
}

template<typename Type>
void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{
	if (m_size > 0)
	{
		Node* temp = new Node(v);
		if (index.m_cur == nullptr)
		{
			if (index.m_prev != nullptr)
			{
				index.m_prev->m_next = temp;
			}
			else
				delete temp;
		}
		else if (index.m_cur == m_head)
		{

			temp->m_next = index.m_cur;
			m_head = temp;
			index.m_cur = m_head;
			
		}
		else
		{
			index.m_prev->m_next = temp;
			temp->m_next = index.m_cur;
			index.m_cur = index.m_prev->m_next;
		}
		m_size++;
	}
}

template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	if (index.m_cur != nullptr || index.m_prev != nullptr)
	{
		if (m_size > 0)
		{
			if (index.m_cur == m_head)
			{
				index.m_cur = index.m_cur->m_next;
				delete m_head;
				m_head = index.m_cur;
			}

			else if (index.m_cur == nullptr)
			{
				delete index.m_prev->m_next;
					index.m_prev = nullptr;
			}
			else
			{
				index.m_prev->m_next = index.m_cur->m_next;
				delete index.m_cur;
				index.m_cur = index.m_prev->m_next;
			}
			m_size--;
		}
	}
}

template<typename Type>
class SLLIter
{
private:
	typename SLList<Type>::Node * m_prev, *m_cur;
	typename SLList<Type>& m_temp;
	friend class SLList<Type>;
	int count = 0;
public:

    SLLIter(SLList<Type>& listToIterate);
	void begin();
	bool end() const;
	SLLIter<Type>& operator++();
	Type& current() const;
};

template<typename Type>
SLLIter<Type>::SLLIter(SLList<Type>& listToIterate) : m_temp(listToIterate)
{
	m_cur = m_temp.m_head;
	m_prev = nullptr;
}
template<typename Type>
void SLLIter<Type>::begin()
{
	m_prev = nullptr;
	m_cur = m_temp.m_head;
}
template<typename Type>
bool SLLIter<Type>::end() const
{
	
	if (m_cur == nullptr)
		return true;
	else
		return false;
}
template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	if (m_cur != nullptr)
	{
		m_cur = m_cur->m_next; 

		if (m_prev == nullptr)
			m_prev = m_temp.m_head;
		else
			m_prev = m_prev->m_next;
	}
		
	return *this;
}
template<typename Type>
Type& SLLIter<Type>::current() const
{
	return m_cur->Data;
}