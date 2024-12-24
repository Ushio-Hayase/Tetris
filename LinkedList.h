#pragma once
/*
* LinkedList data structure header file
*/

#include <iterator>

template <typename T>
struct LinkedListElement
{
	T content;
	LinkedListElement* nextElement = nullptr;
	LinkedListElement* prevElement = nullptr;
};

template <typename T>
class IIterator
{
public:
	IIterator() : ptr(nullptr) {}
	IIterator(T* ptr) : ptr(ptr) {}

	// 전위형 ++it
	IIterator& operator++()
	{
		this->ptr++;
		return *this;
	}
	
	// 후위형 it++
	IIterator operator++(int)
	{
		IIterator tmp = *this;
		this->ptr++;
		return tmp;
	}

	IIterator operator+(const int count)
	{
		IIterator tmp = *this;
		tmp.ptr += count;
		return tmp;
	}

	bool operator==(const IIterator& other)
	{
		return this->ptr == other.ptr;
	}

	bool operator!=(const IIterator& other)
	{
		return this->ptr != other.ptr;
	}

	T& operator*()
	{
		return *this->ptr;
	}
public:
	T* ptr = nullptr;
};

template <typename T>
class LinkedList
{
public:
	using iterator = IIterator<LinkedListElement<T>>;

	inline const T& front()
	{
		return this->frontElement->content;
	}
	
	inline const T& back()
	{
		return this->endElement->content;
	}

	inline iterator begin()
	{
		return iterator(this->frontElement);
	}

	inline iterator end()
	{
		return iterator(this->endElement);
	}

	inline void push_back(const T& content)
	{
		this->endElement->nextElement = new LinkedListElement<T>();
		this->endElement = this->endElement->nextElement;
		this->endElement->content = content;
	}

	inline void push_front(const T& content)
	{
		this->frontElement->prevElement = new LinkedListElement<T>();
		this->frontElement = this->frontElement->prevElement;
		this->frontElement->content = content;
	}

	inline void pop_back()
	{
		LinkedList<T>* tmp = this->endElement->prevElement;
		delete this->endElement;
		this->endElement = tmp;
		this->endElement->nextElement = nullptr;
	}

	inline void pop_front()
	{
		LinkedList<T>* tmp = this->frontElement->nextElement;
		delete this->frontElement;
		this->frontElement = tmp;
		this->frontElement->prevElement = nullptr;
	}

	inline void insert(const iterator& iter, const T& content)
	{
		LinkedListElement<T>* prevTmp = iter.ptr->prevElement;

		iter.ptr->prevElement = new LinkedListElement<T>();
		iter.ptr->prevElement->content = content;
		prevTmp->nextElement = iter.ptr->prevElement;
	}

	inline iterator erase(const iterator& iter)
	{
		LinkedListElement<T>* tmp = iter.ptr->nextElement;
		iter.ptr->prevElement = tmp;
		tmp->prevElement = iter.ptr->prevElement;
		delete iter.ptr;

		return tmp;
	}

	inline size_t size()
	{
		return this->length;
	}

	void remove(const T& content)
	{
		for (auto iter : this->begin())
		{
			
		}
	}
private:
	LinkedListElement<T>* frontElement;
	LinkedListElement<T>* endElement;
	size_t length = 0;
};