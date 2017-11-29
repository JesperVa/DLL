#pragma once
#include <iostream>

template <class T>
class List : public Link<T>
{
private:
	std::ostream& Print(std::ostream&) const;

	//Link* m_root;
	//Link* m_last;
	int count = 0; //Used for Invariant()
	
public:
	List() = default;
	~List()
	{
		while (next != this)
		{
			Link* temp = next;
			next = next->next;
			delete temp;
		}
	}

	T* First();
	const T* First() const;
	T* Last();
	const T* Last() const;

	T* PushFront(T*);
	T* PopFront();
	T* PushBack(T*);
	template <class Arg>
	T* FindFirst(const Arg& searchFor) const { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream& cout, List& list) { return list.Print(cout); }

	bool Invariant() const; //Used for Asserts
};

template <class T>
bool List<T>::Invariant() const
{
	if (count > 1)
	{
		return next && prev && (next) == (next->next->prev) && (prev) == (prev->prev->next);
	}
	//if (count == 1)
	//{
	//	return m_root->next == nullptr && m_last->prev == nullptr && m_root->prev == nullptr && m_last->next == nullptr;
	//}
}

template <class T>
const T* List<T>::First() const { return dynamic_cast<const T*>(this->next); }

template <class T>
T* List<T>::First() { return dynamic_cast<T*>(this->next); }

template <class T>
const T* List<T>::Last() const { return dynamic_cast<const T*>(this->prev); }

template <class T>
T* List<T>::Last() { return dynamic_cast<T*>(this->prev); }

template <class T>
T* List<T>::PushFront(T* toPush)
{
	Link* temp = dynamic_cast<Link*>(toPush);
	//if (m_last == nullptr)
	//{
	//	next = prev = m_last = m_root = temp;
	//	count++;
	//	return toPush; //We just put the same object as first in list
	//}

	//If next isn't set, neither is prev
	if (next == nullptr)
	{
		prev = next = temp;
		temp->next = temp->prev = this;
		return toPush;
	}

	temp->next = next;
	temp->prev = this;
	next->prev = temp;
	next = temp;

	count++;
	return dynamic_cast<T*>(next);
}

template <class T>
T* List<T>::PopFront()
{
	Link* temp = dynamic_cast<T*>(next);
	if (next == this) //We are pointing at ourself
	{
		return nullptr;
	}
	//if (!m_root->next)
	//{
	//	m_root = nullptr;
	//	temp->next = temp->prev = nullptr;
	//	count--;
	//	return temp;
	//}

	next = next->next;
	next->prev = this;
	temp->next = temp->prev = nullptr;
	count--;

	return dynamic_cast<T*>(temp);
}

template <class T>
std::ostream& List<T>::Print(std::ostream& stream) const
{
	Node* temp = dynamic_cast<Node*>(next);
	while (temp)
	{
		temp->Print(stream);
		temp = dynamic_cast<Node*>(temp->next);
	}

	return stream << std::endl; //Returns new-line to end the print
}

template <class T>
T* List<T>::PushBack(T* toPush)
{
	Link* temp = dynamic_cast<Link*>(toPush);
	//if (!m_root)
	//{
	//	//If root doesn't exists, no values exists in list and thus the root and last is the same object
	//	next = prev = m_last = m_root = temp;
	//	count++;
	//	return toPush;
	//}

	//If next isn't set, neither is prev
	if (next == nullptr)
	{
		prev = next = temp;
		temp->next = temp->prev = this;
		return toPush;
	}

	temp->prev = prev;
	temp->next = this;
	prev->next = temp;
	prev = temp;
	count++;

	return dynamic_cast<T*>(prev);
}