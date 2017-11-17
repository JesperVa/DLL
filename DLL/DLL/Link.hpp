#pragma once
#include <iostream>
#include <cassert>

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
	T* Next() const;
	T* Prev() const;

	T* InsertAfter(T*);
	//T* InsertAfter(const T*);
	T* InsertBefore(T*);
	T* DeleteAfter();

	template<typename Arg>
	T* FindNext(const Arg&) const;

	virtual std::ostream& Print(std::ostream& cout) const { return cout; }

	bool Invariant() const;

};

template <class T>
bool Link<T>::Invariant() const
{
	if (next && prev) { return next->prev == this && prev->next == this; }
	else if (!next && !prev) { return true; }
	else if (!next && prev) { return prev->next == this; }
	else if (next && !prev) { return next->prev == this; }
}

template <class T>
T* Link<T>::Next() const { return static_cast<T*>(this->next); }

template <class T>
T* Link<T>::Prev() const { return static_cast<T*>(this->prev); }

//TODO: Look through InsertAfter() InsertBefore() when you're awake
template <class T>
T* Link<T>::InsertAfter(T* toInsert)
{
	Link* temp = static_cast<Link*>(toInsert);
	temp->prev = this;
	if (next) //If next isn't nullptr, set next-prev to temp
	{
		next->prev = temp;
	}
	temp->next = next;
	temp->prev = this;
	next = temp;

	assert(this->Invariant());
	return static_cast<T*>(temp);
}

template <class T>
T* Link<T>::InsertBefore(T* toInsert)
{
	Link* temp = static_cast<Link*>(toInsert);
	if (prev) //If prev isn't nullptr, set prev-next to temp
	{
		prev->next = temp;
	}
	prev = temp;
	assert(this->Invariant());
	return static_cast<T*>(temp);
}


template <class T>
template <typename Arg>
//template <class T, typename Arg>
T* Link<T>::FindNext(const Arg& searchFor) const
{
	Node* temp = static_cast<Node*>(next);

	if (temp->Match(searchFor))
	{
		return static_cast<T*>(temp); //A match
	}
	else if (temp->next)
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
		next->prev = this;
	}
	tempPointer->next = tempPointer->prev = nullptr;
	assert(this->Invariant());
	return static_cast<T*>(tempPointer);
}