#pragma once
#include <iostream>

template <class T>
class List : public Link<T>
{
private:
	std::ostream& Print(std::ostream&) const;

	//TODO: Make m_root and m_last prev and next
	Link* m_root;
	Link* m_last;
	int count = 0; //Used to double check with invariants

public:
	List() : m_root(nullptr), m_last(nullptr) {};

	//~List();
	T* First() const;
	T* Last() const;
	T* PushFront(T*);
	T* PopFront();
	T* PushBack(T*);
	template <class Arg>
	T* FindFirst(const Arg& searchFor) { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream& cout, List& list) { return list.Print(cout); }
	//void Check();


	bool Invariant() const; //Used for Asserts
};


template <class T>
bool List<T>::Invariant() const
{
	if (count > 1)
	{
		return m_root && m_last && (m_root) == (m_root->next->prev) && (m_last) == (m_last->prev->next);
	}
	if (count == 1)
	{
		return m_root->next == nullptr && m_last->prev == nullptr && m_root->prev == nullptr && m_last->next == nullptr;
	}
}

template <class T>
T* List<T>::First() const
{
	return static_cast<T*>(this->m_root);
}

template <class T>
T* List<T>::Last() const
{
	return static_cast<T*>(this->m_last);
}

template <class T>
T* List<T>::PushFront(T* toPush)
{
	Link* temp = static_cast<Link*>(toPush);
	if (m_last == nullptr)
	{
		next = prev = m_last = m_root = temp;
		return toPush; //We just put the same object as first in list
	}

	temp->next = m_root;
	temp->prev = nullptr;
	m_root->prev = temp;
	next = m_root = temp;
	count++;
	return static_cast<T*>(m_root);
}

template <class T>
T* List<T>::PopFront()
{
	T* temp = static_cast<T*>(m_root);
	if (m_root == nullptr)
	{
		return nullptr;
	}
	if (!m_root->next)
	{
		m_root = nullptr;
		temp->next = temp->prev = nullptr;
		return temp;
	}
	//If next exists we do this TODO:refactor
	next = m_root = m_root->next;
	m_root->prev = nullptr;
	temp->next = temp->prev = nullptr;
	count--;
	return temp;
}

template <class T>
std::ostream& List<T>::Print(std::ostream& stream) const
{
	Node* temp = static_cast<Node*>(m_root);
	while (temp)
	{
		temp->Print(stream);
		temp = static_cast<Node*>(temp->next);
	}

	return stream << std::endl; //Returns new-line to end the print
}

template <class T>
T* List<T>::PushBack(T* toPush)
{
	Link* temp = static_cast<Link*>(toPush);
	if (!m_root)
	{
		//If root doesn't exists, no values exists in list and thus the root and last is the same object
		next = prev = m_last = m_root = temp;
		return toPush;
	}
	temp->prev = m_last;
	temp->next = nullptr;
	//Should we assume toPush is already pointing at nullptr in both directions?
	m_last->next = temp;
	prev = m_last = temp;
	count++;
	return static_cast<T*>(m_last);
}