#pragma once
/*
* Queue data structure header file
*/

#include "LinkedList.h"

template <typename T>
class Queue
{

public:
	inline Queue() : arr(new T[8]) {};

	inline Queue(T* arr, const size_t& len)
		: arr(arr), len(len) {};

	bool operator==(const Queue& other) const
	{
		bool eq_len = this->len == other.len;
		bool eq_arr = true;

		if (!eq_len) return false;

		for (int i = 0; i < this->len; ++i)
			if (this->arr[i] != other->arr[i]) return false;


		return true;
	};

	void push(const T& content)
	{
		if (isFull()) reAllocate();

		this->arr[current_len + 1] = content;
	}

	~Queue()
	{
		delete this->arr;
	};
private:
	inline bool isFull()
	{
		return current_len == len;
	}

	void reAllocate()
	{
		T* temp = new T[this->current_len * 2];
		for (size_t i = 0; i < this->current_len; ++i)
		{
			temp[i] = this->arr[i];
		}
		delete this->arr;

		this->arr = temp;
	}
private:
	T* arr;
	size_t len = 10;
	size_t current_len = 0;
};