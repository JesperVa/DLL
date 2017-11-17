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

	bool Invariant();

};

template <class T>
bool Link<T>::Invariant()
{
	if (next && prev) { return next->prev == this && prev->next == this; }
	else if(!next && !prev) { return true; }
	else if (!next && prev) { return prev->next == this; }
	else if (next && !prev) { return next->pref == this; }
}

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

//1 2 2 3

//TODO: Look through InsertAfter() InsertBefore() when you're awake
template <class T>
T* Link<T>::InsertAfter(T* toInsert)
{
	Link* temp = static_cast<Link*>(toInsert);
	temp->prev = this;
	if (!next)
	{
		if (!next->next)
		{
			temp->next = next->next;
		}
		next->prev = temp;
	}
	temp->next = next;
	temp->prev = this;
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
	
	if (temp->Match(searchFor))
	{
		return static_cast<T*>(temp); //A match
	}
	else if(temp->next)
	{
		return next->FindNext(searchFor); //Next isn't null, keep looking
	}
	
	return nullptr; //We didn't find anything
}


template <class T>
T* Link<T>::DeleteAfter()
{
	Link* tempPointer = next;
	if (next == nullptr)
	{
		return nullptr; //There was none to delete so we return nullptr
	}
	else if (next->next != nullptr)
	{
		next = next->next;
	}
	tempPointer->next = tempPointer->prev = nullptr;
	return static_cast<T*>(tempPointer);
}