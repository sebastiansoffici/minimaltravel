#ifndef COP4530_QUEUE_H
#define COP4530_QUEUE_H


#include <iostream>
#include <stdexcept>
#include <list>
namespace cop4530
{

template <typename T>
class Queue
{
	public:
		typedef T* iterator;
		typedef T* const_iterator;
	
		//constructor, destructor, and copy constructor
		Queue();
		~Queue();
		Queue(const Queue &rhs);
		Queue(Queue && rhs); // move constructor
		Queue& operator=(const Queue & rhs);
		Queue& operator=(Queue &&rhs);
		T& back();
		const T& back() const;
		bool empty() const;
		T& front();
		const T& front () const;
		void pop();
		void push(const T& val);
		void push(T&& val);
		int size();
	private:
		std::list<T> xlist;
};

#include "Queue.hpp"
}
#endif
