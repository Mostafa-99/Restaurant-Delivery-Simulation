

#pragma once
#include<iostream>
using namespace std;
#include "NodeP.h"

template<typename T>
class EmergencyQueue
{

private:
	NodeP<T>* backPtr;
	NodeP<T>* frontPtr;
	int count;
public:

	T* EmergencyExit(T* exit);
	EmergencyQueue();
	bool isEmpty() const;
	int getCount() const;

	void Print() const;
	bool enqueue( T* newEntry);
	bool dequeue(T* & frntEntry);
	bool peekFront(T* & frntEntry)  const;
	

	
};

template<typename T>
bool EmergencyQueue<T>::isEmpty() const {
	if (frontPtr == nullptr)
		return true;
	else
		return false;

}

template<typename T>

EmergencyQueue<T>::EmergencyQueue() {
	backPtr = NULL;
	frontPtr = NULL;
	count = 0;
}

template<typename T>

T* EmergencyQueue<T>::EmergencyExit(T* exit) {

	if (frontPtr==NULL) {
		return nullptr;
	}
	NodeP<T> *curr = frontPtr;
	NodeP<T> *prev = curr;
	while (curr) {
		
		if (  !(*curr->item == *exit)  ) 
		{
			prev = curr;
			curr = curr->next;
		}
		else
		{
			break;
		}
		
	}

	if (curr)
	{
		T* result = curr->item;

		if (frontPtr == backPtr) {
			delete frontPtr;
			frontPtr = NULL;
			backPtr = NULL;
			count--;
			return result;
		}


		if (curr == frontPtr)
		{
			frontPtr = frontPtr->next;


		}
		else if (curr == backPtr)
		{
			backPtr = prev;
			backPtr->next = NULL;

		}
		else
		{

			prev->next = curr->next;

		}

		delete curr;
		count--;
		return result;





	}
	else
	{
		return nullptr;
	}



}


template <typename T>
int  EmergencyQueue<T>::getCount() const {
	return count;
}


template <typename T>
bool EmergencyQueue<T>::enqueue(T* newEntry)
{
	NodeP<T>* newNodePtr = new NodeP<T>;
	newNodePtr->item = newEntry;
	newNodePtr->next = NULL;
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->next=newNodePtr; // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	count++;
	return true;
} // end enqueue



template <typename T>
bool EmergencyQueue<T>::dequeue(T* & frntEntry)
{
	if (isEmpty())
		return false;

	NodeP<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->item;
	frontPtr = frontPtr->next;
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;

	count--;
	return true;

}

template <typename T>
bool EmergencyQueue<T>::peekFront(T*& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->item;
	return true;

}


template <typename T>
void EmergencyQueue<T>::Print() const {

	if (frontPtr == nullptr) {
		return;
	}
	else {



		NodeP<T>* curr;
		curr = frontPtr;

		while (curr) {

			cout << *curr->item << ' ';
			curr = curr->next;
		}

		cout << endl;
	}
}



