#pragma once
template<typename Type>
class BST
{
private:
	struct Node
	{
		Type m_data;
		Node* m_right = nullptr, *m_left = nullptr;
	};
	Node* m_root;
	void pre( Node* _node);
	void post(Node* _node);
	void inorder(Node* _node) const;
public:
	BST();
	~BST();
	BST& operator=(const BST<Type>& that);
	BST<Type>(const BST& that);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	bool find(const Type& v) const;
	void clear();
	void printInOrder() const;

};
template<typename Type>
void BST<Type>::pre(Node * _node)
{
	if (_node != nullptr)
	{
		insert(_node->m_data);
		pre(_node->m_left);
		pre(_node->m_right);
	}
}
template<typename Type>
void BST<Type>::post(Node * _node)
{
	if (_node != nullptr)
	{
		post(_node->m_left);
		post(_node->m_right);
		delete _node;
	}
}
template<typename Type>
void BST<Type>::inorder(Node * _node) const
{
	if (_node != nullptr)
	{
		inorder(_node->m_left);
		cout << _node->m_data << " ";
		inorder(_node->m_right);
	}
}
/////////////////////////////////////////////////////////////////////////////
// Function : Constuctor
// Notes : constucts an empty BST
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
BST<Type>::BST()
{
	m_root = nullptr;
}
/////////////////////////////////////////////////////////////////////////////
// Function : Destructor
// Notes : destroys the BST cleaning up any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
BST<Type>::~BST()
{
	clear();
}
/////////////////////////////////////////////////////////////////////////////
// Function : assignment operator
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
BST<Type> & BST<Type>::operator=(const BST<Type> & that)
{
	//TODO: insert return statement here
	if(this != &that)
	{
		clear();
		if(that.m_root != nullptr)
		pre(that.m_root);
	}
	return *this;
}
/////////////////////////////////////////////////////////////////////////////
// Function: copy constructor
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
BST<Type>::BST(const BST<Type> & that)
{
	m_root = nullptr;
	*this = that;
}
/////////////////////////////////////////////////////////////////////////////
// Function : insert
// Parameters :  v - the item to insert 
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void BST<Type>::insert(const Type & v)
{
	Node* tmp = new Node;
	tmp->m_data = v;
	if (m_root == nullptr)
	{
		m_root = tmp;
	}
	else
	{
		Node* m_cur;
		m_cur = m_root;
		while (true)
		{
			if (v < m_cur->m_data)
			{
				if (m_cur->m_left != nullptr)
				{
					m_cur = m_cur->m_left;
				}
				else
				{
					m_cur->m_left = tmp;
					break;
				}
			}
			if (v >= m_cur->m_data)
			{
				if (m_cur->m_right != nullptr)
				{
					m_cur = m_cur->m_right;
				}
				else
				{
					m_cur->m_right = tmp;
					break;
				}
			}
		}
	}
}
/////////////////////////////////////////////////////////////////////////////
// Function : findAndRemove
// Parameters : v - the item to find (and remove if it is found)
// Return : bool - true if the item was removed, false otherwise
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool BST<Type>::findAndRemove(const Type & v)
{
	Node *m_cur = m_root, *m_parent = nullptr;
	while (m_cur != nullptr)
	{
		if (v < m_cur->m_data)
		{
			m_parent = m_cur;
			m_cur = m_cur->m_left;
		}
		else if (v > m_cur->m_data)
		{
			m_parent = m_cur;
			m_cur = m_cur->m_right;
		}
		else if (v == m_cur->m_data)
		{
			if (m_cur->m_left == nullptr && m_cur->m_right == nullptr)
			{
				if (m_cur == m_root)
				{
					delete m_cur;
					m_cur = nullptr;
					m_root = nullptr;
				}
				else if (m_parent->m_right == m_cur)
					m_parent->m_right = nullptr;
				else
					m_parent->m_left = nullptr;
				delete m_cur;
				m_cur = nullptr;
			}
			else if (m_cur->m_left == nullptr && m_cur->m_right != nullptr)
			{
				if (m_cur == m_root)
				{
					Node* tmp = nullptr;
					tmp = m_cur;
					tmp = m_cur->m_right;
					delete m_cur;
					m_root = tmp;
					m_cur = nullptr;
				}
				else if (m_parent->m_left == m_cur)
				{
					m_parent->m_left = m_cur->m_right;
					delete m_cur;
					m_cur = nullptr;
				}
				else if(m_parent->m_right == m_cur)
				{
					m_parent->m_right = m_cur->m_right;
					delete m_cur;
					m_cur = nullptr;
				}
			}
			else if (m_cur->m_left != nullptr && m_cur->m_right == nullptr)
			{
				if (m_cur == m_root)
				{
					Node* tmp = nullptr;
					tmp = m_cur;
					tmp = m_cur->m_left;
					delete m_cur;
					m_root = tmp;
					m_cur = nullptr;
				}
				else if (m_parent->m_left == m_cur)
				{
					m_parent->m_left = m_cur->m_left;
					delete m_cur;
					m_cur = m_parent->m_left;
				}
				else if (m_parent->m_right == m_cur)
				{
					m_parent->m_right = m_cur->m_left;
					delete m_cur;
					m_cur = m_parent->m_left;
				}
			}
			else if (m_cur->m_left != nullptr && m_cur->m_right != nullptr)
			{
				Node* tmp = nullptr;
				Node* parent2 = nullptr;
				Node* tmp2;
				bool LR = false;
				bool IS_root = false;
				tmp2 = m_parent;
				m_parent = m_cur;
				if (m_cur->m_data == m_root->m_data)
					IS_root = true;
				m_cur = m_cur->m_right;
				if (m_parent != m_root)
				{
					if (tmp2->m_right == m_parent)
						LR = true;
				}
				while (m_cur->m_left != nullptr)
				{
					parent2 = m_cur;
					m_cur = m_cur->m_left;
				}
				
				///////////
			       if (m_cur->m_left == nullptr && m_cur->m_right == nullptr)
				{
					tmp = m_cur;
					parent2->m_left = m_cur->m_right;
					tmp->m_right = m_parent->m_right;
					tmp->m_left = m_parent->m_left;
					m_cur = m_parent;
					m_parent = tmp;
					if (IS_root == true)
						m_root = m_parent;
					if (IS_root == false)
					{
						if (LR == true)
							tmp2->m_right = m_parent;
						else
							tmp2->m_left = m_parent;
					}
					delete m_cur;
					m_cur = nullptr;
				}
				else if (m_cur->m_left == nullptr && m_cur->m_right != nullptr)
				{
						tmp = m_cur;
						parent2->m_left = m_cur->m_right;
						tmp->m_right = m_parent->m_right;
						tmp->m_left = m_parent->m_left;
						m_cur = m_parent;
						m_parent = tmp;
						if (IS_root == true)
							m_root = m_parent;
						if (IS_root == false)
						{
							if (LR == true)
								tmp2->m_right = m_parent;
							else
								tmp2->m_left = m_parent;
						}
						delete m_cur;
						m_cur = nullptr;
				}
				//////////
			}
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////
// Function : find
// Parameters : v - the item to find
// Return : bool - true if the item was found, false otherwise
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
bool BST<Type>::find(const Type & v) const
{
	Node *m_cur = m_root;
	

	while (m_cur != nullptr)
	{
		if (v < m_cur->m_data)
		{
				m_cur = m_cur->m_left;
		}
		else if (v > m_cur->m_data)
		{
			m_cur = m_cur->m_right;
		}
		else if (v == m_cur->m_data)
		{
			return true;
		}
	}
	return false;
}
/////////////////////////////////////////////////////////////////////////////
// Function : clear
// Notes : clears the BST, cleaning up any dynamic memory
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void BST<Type>::clear()
{
	post(m_root);
	m_root = nullptr;
}
/////////////////////////////////////////////////////////////////////////////
// Function : printInOrder
// Notes : prints the contents of the BST to the screen, in ascending order
/////////////////////////////////////////////////////////////////////////////
template<typename Type>
void BST<Type>::printInOrder() const
{
	inorder(m_root);
	cout << endl;
}
