#pragma once
template <class T>
class List : public Link<T>
{
private:
	std::ostream& Print(std::ostream&);
public:
	List();
	~List();
	T* First();
	T* Last();
	T* PushFront(T*);
	T* PopFront();
	T* PushBack(T*);
	template <class Arg>
	T* FindFirst(const Arg& searchFor) { return FindNext(searchFor); }

	friend std::ostream& operator<<(std::ostream& cout, List& list) { return list.Print(cout); }
	void Check();
};