#pragma once
/*
* LinkedList data structure header file
*/
#include <functional>

#include "IIterator.h"

template <typename T>
struct LinkedListElement
{
	T content;
	LinkedListElement* nextElement = nulli;
	LinkedListElement* prevElement = nulli;
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
		LinkedListElement<T>* prevTmp = iter.i->prevElement;

		iter.i->prevElement = new LinkedListElement<T>();
		iter.i->prevElement->content = content;
		prevTmp->nextElement = iter.i->prevElement;
	}

	inline iterator erase(const iterator& iter)
	{
		LinkedListElement<T>* tmp = iter.i->nextElement;
		iter.i->prevElement = tmp;
		tmp->prevElement = iter.i->prevElement;

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
			if (iter.i.content == content) this->erase(iter);
		}
	}

	void reverse()
	{
		for (auto iter : this->begin())
		{
			LinkedListElement<T>* tmp = iter.i.prevElement;
			iter.i.prevElement = iter.i.nextElement;
			iter.i.nextElement = tmp;
		}

		LinkedListElement<T>* tmp = this->frontElement;
		this->frontElement = this->endElement;
		this->endElement = tmp;
	}

	void sort(std::function func)
	{

	}
private:
	LinkedListElement<T>* frontElement;
	LinkedListElement<T>* endElement;
	size_t length = 0;
};