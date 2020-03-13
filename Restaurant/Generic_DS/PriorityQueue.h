#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include "NodeWP.h"
#include <new>

#include <iostream>
using namespace std;


template <typename T>
class PriorityQueue
{

	NodeWP<T>* backPtr;
	NodeWP<T>* frontPtr;
	int count;

public:

	PriorityQueue();

	bool isEmpty() const;

	bool PriorEnqueue(const T& newEntry, double priority);

	bool dequeue(T& frntEntry);

	bool peekFront(T& frntEntry)  const;

	//bool enqueue(const T& newEntry);

	void Print() const;

	int Getcount();

	T * toArray(int&) const;

	~PriorityQueue();

};

template <typename T>

PriorityQueue<T>::PriorityQueue() {

	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;

}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	return (frontPtr == nullptr);
}


template <typename T>
bool PriorityQueue<T>::PriorEnqueue(const T& newEntry, double priority) {


	NodeWP<T>* newNodePtr = new(std::nothrow) NodeWP<T>(newEntry, priority);

	if (newNodePtr) {
		// Insert the new node
		if (isEmpty()) 
		{
			frontPtr = newNodePtr; // The queue is empty
			backPtr = newNodePtr; // New node is at back
		}	
		else // at least one node exists
		{
			if (newNodePtr->priority > frontPtr->priority) //insert at front
			{
				newNodePtr->next = frontPtr;
				frontPtr = newNodePtr;

			}
			else //middle or back
			{

				NodeWP<T>* curr = frontPtr;
				while (curr->next && (curr->next)->priority >= newNodePtr->priority) 
				{
					curr = curr->next;
				}

				//breaks the while loop under two cases

				if (curr==backPtr) //reached the end
				{
					backPtr->next = newNodePtr;
					backPtr = newNodePtr;


				}
				else //in the middle
				{

					newNodePtr->next = curr->next;

					curr->next = newNodePtr;

				}


			}

		}
			
		count++;
		return true;


	}
	else //allocation fails
	{
		return false;
	}

	


}



template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry)  const {

	if (isEmpty())
		return false;

	frntEntry = frontPtr->item;
	return true;

}

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry) {


	if (isEmpty())
		return false;

	NodeWP<T>* nodeToDeletePtr = frontPtr;
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
void PriorityQueue<T>::Print() const {

	if (frontPtr == nullptr) {
		return;
	}
	else {



		NodeWP<T>* curr;
		curr = frontPtr;

		while (curr) {

			cout << curr->item << ' ';
			curr = curr->next;
		}

		cout << endl;
	}
}

template <typename T>
PriorityQueue<T>::~PriorityQueue() {

}

template <typename T>
int PriorityQueue<T>::Getcount() {
	return count;
}

template < typename T>
T * PriorityQueue<T>::toArray(int& count) const
{
	count = this->count;

	T * bagContents = new T[this->count];
	NodeWP<T>* curPtr = frontPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < this->count))
	{
		bagContents[counter] = curPtr->item;
		curPtr = curPtr->next;
		counter++;
	} // end while
	return bagContents;
} // end toArray

#endif