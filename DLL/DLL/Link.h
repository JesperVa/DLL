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