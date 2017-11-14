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

	T* m_object;
	int const m_Capacity = 1; //Only one object per link at a time
	
public:
	Link();
	virtual ~Link() = default;
	T* Next();
	T* Prev();

	T* InsertAfter(T*);
	T* InsertBefore(T*);
	T* DeleteAfter();

	template<class Arg>
	T* FindNext(const Arg&);

	virtual std::ostream& Print(std::ostream& cout) { return cout; }

};

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
Link::T* FindNext(const Arg& searchFor)
{
	//Might be what Olle is looking for?
	if (m_object.next == nullptr)
	{
		return nullptr;
	}
	else if (!m_object.next.Match(searchFor))
	{
		return searchFor.findNext(searchFor);
	}
}