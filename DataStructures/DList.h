#pragma once
#define size_type int
template<typename Data>
class DList
{
private:
	struct Node
	{
		Data m_data;
		Node* m_prev, *m_next;
		Node* m_down, *m_up;
		Node(Data& _data, Node* _prev, Node* _next) : m_data(_data), m_prev(_prev), m_next(_next) { }
	};
	Node* first, *last;
	 vector<Node*>top, vector<Node*>bottom[]
	Data X = (int)NULL;
	int count;
public:
	DList();
	~DList();

	void push_back(Data _data);
	void push_front(Data _data);
	void push_down(Data _data);
	void push_up(Data _ data);
	void erase(int _index);
	void clear();
	int size() const { return count; }

	Data& operator[](int _index);
	Data const& operator[](int _index) const;
	//Data& GetData() const { return m_data; }
};
template<typename Data>
DList<Data>::DList()
{
	first = last = NULL;
	count = 0;
	/*first->m_next = last;
	last->m_prev = first;*/
}
template<typename Data>
DList<Data>::~DList()
{
	clear();
}
template<typename Data>
void DList<Data>::push_back(Data _data)
{
	Node* temp = new Node(_data, last, NULL);
	if (!first)
		first = temp;


	else
		last->m_next = temp;
	// temp->m_next = first;
	last = temp;

	++count;
	//if (last)
	//{
	//	if (first == last)
	//	{
	//		last->m_next = temp;
	//		last = temp;
	//		temp->m_prev = first;
	//		count++;
	//		return;
	//	}
	//	else
	//	{
	//		last->m_next = temp;
	//		temp->m_prev = last;
	//		last = temp;
	//		count++;
	//		return;
	//	}
	//}
	//else
	//{
	//	first = temp;
	//	last = temp;
	//	count++;
	//	return;
	//}
}
template<typename Data>
void push_down(Data _data)
{
	Node* temp = new Node(_data, bottom, NULL);
	if (!top)
		top = temp;


	else
		bottom->m_down = temp;
	// temp->m_next = first;
	bottom = temp;

	++count;
}
template<typename Data>
void push_up(Data _ data)
{
	Node* temp = new Node(_data, bottom, NULL);
	if (!top)
		top = temp;


	else
		bottom->m_down = temp;
	// temp->m_next = first;
	bottom = temp;

	++count;
}
template<typename Data>
void DList<Data>::push_front(Data _data)
{
	Node* temp = new Node(_data, NULL, first);
	//if (first)
	//{
	//	if (first == last)
	//	{
	//		first->m_prev = temp;
	//		first = temp;
	//		temp->m_next = last;
	//		count++;
	//		return;
	//	}
	//	else
	//	{
	//		first->m_prev = temp;
	//		temp->m_next = first;
	//		first = temp;
	//		count++;
	//		return;
	//	}
	//}
	//else
	//{
	//	/*first = temp;
	//	last = temp;*/
	//	count++;
	//	return;
	//}
	if (!last)
		last = temp;


	else
		first->m_prev = temp;
	// temp->m_next = first;
	first = temp;

	++count;
	//}

}
template<typename Data>
void DList<Data>::erase(int _index)
{
	Node* temp = first;
	if (_index <= count && _index >= 0)
	{
		if (count >= 0)
		{
			{
				for (int loop = 0; loop < _index; loop++)
				{
					temp = temp->m_next;
				}

				 if (temp == first)
				{
					//temp->m_prev->m_next = temp->m_next;
					 if (count > 1)
					 {
						 temp->m_next->m_prev = temp->m_prev;
						 first = temp->m_next;
					 }
					 else if (count == 1)
					 {
						 temp = first;
					 }
				}
				else if (temp == last)
				{
					if (count > 1)
					{
						temp->m_prev->m_next = temp->m_next;
						last = temp->m_prev;
					}
					else if (count == 1)
					{
						temp = last;
					}
					//temp->m_next->m_prev = temp->m_prev;
				}
				else if (temp != first)
				{
					temp->m_prev->m_next = temp->m_next;
					temp->m_next->m_prev = temp->m_prev;
				}
				else if (temp != last)
				{
					temp->m_prev->m_next = temp->m_next;
					temp->m_next->m_prev = temp->m_prev;
				}
				delete temp;
				count--;
			}
		}
	}
}
template<typename Data>
void DList<Data>::clear()
{
	Node* temp = first;

	while (count > 0)
	{
		first = first->m_next;
		delete temp; //Old first
		temp = first;
		count--;
	}
}
template<typename Data>
Data& DList<Data>::operator[](int _index)
{
	Node* temp = first;
	int i = 0;
	for (; i < _index; ++i)
	{
		temp = temp->m_next;
	}

	return temp->m_data;
}
template<typename Data>
Data const& DList<Data>::operator[](int _index) const
{
	Node* temp = first;
	int i = 0;
	for (; i < _index; ++i)
	{
		temp = temp->next;
	}

	return temp->data;
}