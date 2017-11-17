#pragma once
#include <iostream>

template <class T>
class List : public Link<T>
{
private:
	std::ostream& Print(std::ostream&);
	Link* m_root;
	Link* m_last;


public:
	List() : m_root(nullptr), m_last(nullptr) {};

	//~List();
	T* First();
	T* Last();
	T* PushFront(T*);
	T* PopFront();
	T* PushBack(T*);
	template <class Arg>
	T* FindFirst(const Arg& searchFor) { return FindNext(searchFor); }
	
	friend std::ostream& operator<<(std::ostream& cout, List& list) { return list.Print(cout); }
	void Check();


	bool Invariant(); //Used for Asserts
};

//No destructor in list?
//template <class T>
//List<T>::~List()
//{
//	//Deletes all the objects
//	//Double check with Olle
//	T* temp = m_root;
//	while (temp.next != nullptr)
//	{
//		temp = temp.next;
//		delete temp.prev;
//	}
//	delete temp;
//}


template <class T>
bool List<T>::Invariant()
{
	//return m_root == nullptr && m_last == nullptr || (*m_root) == (*m_root) && (*m_last) == (*m_last);
	return true; //TODO: Fix
}


template <class T>
T* List<T>::First()
{
	return static_cast<T*>(this->m_root);
}

template <class T>
T* List<T>::Last()
{
	return static_cast<T*>(this->m_last);
}

template <class T>
T* List<T>::PushFront(T* toPush)
{
	Link* temp = static_cast<Link*>(toPush);
	if (m_last == nullptr)
	{
		m_last = m_root = temp;
		return toPush; //We just put the same object as first in list
	}

	m_root->prev = temp;
	m_root = temp;
	return static_cast<T*>(m_root);
}

template <class T>
T* List<T>::PopFront()
{
	if (m_root == nullptr)
	{
		return nullptr;
	}

	T* temp = static_cast<T*>(m_root);
	m_root = m_root->next;
	m_root->prev = nullptr;
	return temp;
}

//TODO: Rewrite at school
template <class T>
std::ostream& List<T>::Print(std::ostream& stream)
{
	Node* temp = static_cast<Node*>(m_root);
	//while()
	return std::cout << "Test";
}

template <class T>
T* List<T>::PushBack(T* toPush)
{
	Link* temp = static_cast<Link*>(toPush);
	if (!m_root)
	{
		//If root doesn't exists, no values exists in list and thus the root and last is the same object
		m_last = m_root = temp;
		return toPush;
	}
	//Should we assume toPush is already pointing at nullptr in both directions?
	m_last->next = temp;
	m_last = temp;
	return static_cast<T*>(m_last);
}


