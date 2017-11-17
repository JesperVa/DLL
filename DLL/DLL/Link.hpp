#pragma once
#include <iostream>

template <class T>
class List;

template <class T>
class Link
{
private:
	Link* next; Link* prev;
	friend class List<T>;

public:
	Link() :next(nullptr), prev(nullptr) {}
	virtual ~Link() = default;
	T* Next();
	T* Prev();

	T* InsertAfter(T*);
	T* InsertBefore(T*);
	T* DeleteAfter();

	template<typename Arg>
	T* FindNext(const Arg&);

	virtual std::ostream& Print(std::ostream& cout) { return cout; }

};

template <class T>
T* Link<T>::Next()
{
	return static_cast<T*>(this->next);
}

template <class T>
T* Link<T>::Prev()
{
	return static_cast<T*>(this->prev);
}

//TODO: Look through InsertAfter() InsertBefore() when you're awake
template <class T>
T* Link<T>::InsertAfter(T* toInsert)
{
	Link* temp = static_cast<Link*>(toInsert);
	if (!next)
	{
		temp->prev = this;
		if (!next->next)
		{
			temp->next = next->next;
		}
		next->prev = temp;
	}
	next = temp;
	return static_cast<T*>(temp);
}

template <class T>
T* Link<T>::InsertBefore(T* toInsert)
{
	Link* temp = static_cast<Link*>(toInsert);
	if (!prev)
	{
		if (!prev->prev)
		{
			temp->prev = prev->prev;
		}
		prev->next = temp;
	}
	prev = temp;
	return static_cast<T*>(temp);
}


template <class T>
template <typename Arg>
//template <class T, typename Arg>
T* Link<T>::FindNext(const Arg& searchFor)
{
	Node* temp = static_cast<Node*>(next);

	//Might be what Olle is looking for?
	
	if (temp->Match(searchFor) && !this->next)
	{
		return static_cast<T*>(temp);
	}
	
	return nullptr;
}

template <class T>
T* Link<T>::DeleteAfter()
{
	Link* tempPointer = nullptr;
	if (next == nullptr)
	{
		return nullptr; //There was none to delete so we return nullptr
	}
	else if (next->next != nullptr)
	{
		tempPointer = next->next;
	}
	delete next;
	next = tempPointer;
	return static_cast<T*>(this);
}