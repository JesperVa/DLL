#include "Link.h"

template <class T>
Link::Link()
{
}

template <class T>
Link::~Link()
{
}

template <class T>
Link::T* Next()
{
	return next;
}

template <class T>
Link::T* Prev()
{
	return prev;
}

template <class T>
Link::T* InsertAfter(T* toInsert)
{
	//Might have to be change in case it's not a node
	if (next != nullptr)
	{
		next.prev = toInsert;
	}
	next = toInsert;
	return toInsert;
}

template <class T>
Link::T* InsertBefore(T* toInsert)
{
	if (prev != nullptr)
	{
		prev.next = toInsert;
	}
	prev = toInsert;
	return toInsert;
}

 template <class T>
 Link::T* DeleteAfter()
{
	T* tempPointer = nullptr;
	if (next == nullptr)
	{
		return nullptr;
	}
	else if (next.next != nullptr)
	{
		tempPointer = next.next;
	}
	delete next;
	next = tempPointer;
	return m_object;
}

 template <class T>
 template <class Arg>
 Link:T* FindNext(const Arg& searchFor)
 {

 }