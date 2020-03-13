#pragma once
#include "Node.h"
template <typename T>
class LinkedList :public Node<T>
{
private:
	Node<T>* head;
	int size;
public:
	LinkedList();
	bool IsEmpty(); //checks the list is empty or not
	Node<T>* GetPointerTo(T search); //return a pointer of a certain value
	bool Add(T n); //add node at first(Bag)
	bool AddSorted(T n); //add node in sorted descendingly linkedlist(List)
	bool Remove(T r); //remove node(Bag)
	bool RemoveSorted(T n); //Remove node from sorted descendingly linkedlist(List)
	void Clear(); //Delete all the list
	int GetSize(); //return the size of the list
	bool Contain(T c);
	int GetFreqOf(T f);
	void print();
	//T Searchandremove(int);
	~LinkedList();
};

template <typename T>
LinkedList<T>::LinkedList()
{
	head = NULL;
	size = 0;
}
/*
template <typename T>
T LinkedList<T>::Searchandremove(int n) {

	if (*head->getItem() == n) {

	}

	Node<T>* curr = head;
	Node<T>* prev = curr;

	while (curr) 
	{
		if (*curr->getItem() == n) {

			T Found = curr->getItem();



			return Found;
		}



		prev = curr;
		curr = curr->getNext();
	}

	return NULL;
}

*/

template <typename T>
bool LinkedList<T>::IsEmpty()
{
	if (head == NULL)
		return true;
	return false;
}

template <typename T>
Node<T>* LinkedList<T>::GetPointerTo(T s)
{
	Node<T>* currptr = head;
	while (currptr != NULL)
	{
		if (currptr->getItem() == s)
			return currptr;
		currptr = currptr->getNext();
	}
	return NULL;
}

template <typename T>
bool LinkedList<T>::Add(T a)
{
	Node<T>* nptr = new Node<T>;
	nptr->setItem(a);
	nptr->setNext(head);
	head = nptr;
	size++;
	return true;
}

template <typename T>
bool LinkedList<T>::AddSorted(T a)
{
	Node<T>* nptr = new Node<T>;
	Node<T>* ptr = head;
	if (ptr == NULL || (ptr->getitem() <= a))
	{
		nptr->setItem(a);
		nptr->setNext(head);
		head = nptr;
		size++;
		return true;
	}
	while (ptr->getnext() != NULL)
	{
		if ((ptr->getitem() > a) && ((ptr->getnext())->getitem() <= a))
			break;
		ptr = ptr->getnext();
	}
	if (ptr->getnext() == NULL)
	{
		nptr->setitem(a);
		nptr->setnext(NULL);
		ptr->setnext(nptr);
		size++;
		return true;
	}
	else
	{
		nptr->setitem(a);
		nptr->setnext(ptr->getnext());
		ptr->setnext(nptr);
		size++;
		return true;
	}
}

template <typename T>
bool LinkedList<T>::Contain(T c)
{
	if (GetPointerTo(c) == NULL)
		return false;
	return true;
}

template <typename T>
int LinkedList<T>::GetFreqOf(T f)
{
	int freq = 0;
	Node<T>* currptr = head;
	while (currptr != NULL)
	{
		if (currptr->getitem() == f)
			freq++;
		currptr = currptr->getnext();
	}
	return freq;
}

template <typename T>
bool LinkedList<T>::Remove(T r)
{
	Node<T>* ptr = GetPointerTo(r);
	if (ptr != NULL)
	{
		ptr->setItem(head->getItem());
		Node<T>* delptr = head;
		head = head->getNext();
		delptr->setNext(NULL);
		delete delptr;
		size--;
		return true;
	}
	return false;
}

template <typename T>
bool LinkedList<T>::RemoveSorted(T c)
{
	Node<T>* dptr = GetPointerTo(c);
	Node<T>* prev = head;
	Node<T>* ptr = head->getnext();
	if (head == NULL || dptr == NULL)
	{
		return false;
	}
	if (dptr == head)
	{
		head = head->getnext();
		delete prev;
		size--;
		return true;
	}
	while (dptr != ptr)
	{
		prev = prev->getnext();
		ptr = ptr->getnext();
	}
	prev->setnext(ptr->getnext());
	delete ptr;
	size--;
	return true;
}


template <typename T>
void LinkedList<T>::Clear()
{
	Node<T>* ptr = head;
	while (ptr != NULL)
	{
		Remove(ptr->getItem());
		ptr = ptr->getNext();
	}
	size = 0;
}

template <typename T>
int LinkedList<T>::GetSize()
{
	return size;
}

template <typename T>
LinkedList<T>::~LinkedList()
{
	Clear();
}

template <typename T>
void LinkedList<T>::print()
{
	Node<T>*ptr = head;
	for (int i = 0; i < size; i++)
	{
		cout << ptr->getitem() << " ";
		ptr = ptr->getnext();
	}
	cout << endl;
}