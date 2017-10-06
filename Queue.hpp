//empty constructor
template <typename T>
Queue<T>::Queue()
{
}
//empty destructor
template <typename T>
Queue<T>::~Queue()
{
}
//copy constructor
template <typename T>
Queue<T>::Queue(const Queue& rhs)
{
	xlist = rhs.xlist;
}
//move constructor
template <typename T>
Queue<T>::Queue(Queue &&rhs)
{
	xlist = std::move(rhs.xlist);
}
//copy assignment operator
template <typename T>
typename Queue<T>::Queue & Queue<T> :: operator= (const Queue & rhs)
{
	Queue copy = rhs;
	std::swap(*this, copy);
	return *this;
}
//move assignment operator
template <typename T>
typename Queue<T>::Queue & Queue<T> :: operator= (Queue && rhs)
{
	std::swap(xlist, rhs.xlist);
	return *this;
}
//return reference to back of queue
template <typename T>
T& Queue<T>::back()
{	return xlist.back();	}
//cont version
template <typename T>
const T& Queue<T>::back() const
{	return xlist.back();	}
//check if queue is empty
template <typename T>
bool Queue<T>::empty()const
{	return xlist.empty();	}
//reference to last element of queue
template <typename T>
T& Queue<T>::front()
{	return xlist.front();	}
//const version
template <typename T>
const T& Queue<T>::front() const
{	return xlist.front();	}
//remove first element in queue
template <typename T>
void Queue<T>::pop()
{	xlist.pop_front();	}
//add element to back of queue
template <typename T>
void Queue<T>::push(const T& val)
{	xlist.push_back(val);	}
//same
template <typename T>
void Queue<T>::push(T&& val)
{	xlist.push_back(val);	}
//return queue size
template <typename T>
int Queue<T>::size()
{	return xlist.size();	}
