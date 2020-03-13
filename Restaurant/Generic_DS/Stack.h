#pragma once
template <class T>
class Stack
{
	T arr[3];
	int size;
public:
	Stack();
	bool Push(T);
	bool Pop();
	bool IsEmpty();
	void PrintAll();
	~Stack();
};
template <class T>
Stack<T>::Stack()
{
	size = 0;

}

template <class T>
bool Stack<T>::Push(T item)
{
	if (size < 3)
	{
		arr[size] = item;
		size++;
		return true;
	}
	else
	{
		return false;
	}
}

template <class T>
bool Stack<T>::Pop()
{
	if (size != 0)
	{
		size--;
		return true;
	}
	return false;
}

template <class T>
bool Stack<T>::IsEmpty()
{
	if (size == 0)
		return true;
	return false;
}

template <class T>
Stack<T>::~Stack()
{

}
template <class T>
void Stack<T>::PrintAll()
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}
