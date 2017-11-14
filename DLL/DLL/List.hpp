#pragma once
template <class T>
class List : public Link<T>
{
private:
	std::ostream& Print(std::ostream&);
	T* m_root;
	T* m_last;


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


	bool Invariant(); //Used for Asserts
};

template <class T>
List::List()
{
}

template <class T>
List::~List()
{
}

template <class T>
List::T* First()
{
	return this->m_root;
}

template <class T>
List::T* Last()
{
	return this->m_last;
}

template <class T>
List::T* PushFront(T* toPush)
{
	m_root.prev = toPush;
	m_root = toPush;
	return m_root;
}

template <class T>
List::T* PushBack(T* toPush)
{
	//Should we assume toPush is already pointing at nullptr in both directions?
	m_last.next = toPush;
	m_last = toPush;
	return m_last;
}

template <class T>
List::T* PopFront()
{
	T* temp = m_root;
	m_root = m_root.next;
	m_root.prev = nullptr;
	return temp;
}

template <class T>
List::std::ostream& Print(std::ostream& stream)
{
	//Does he want us to use Nodes own print or just print out the data?
	stream << m_object.data;
}