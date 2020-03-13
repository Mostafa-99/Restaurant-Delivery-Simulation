#pragma once

template < typename T>
class NodeP
{
	template<class T> friend class EmergencyQueue;
	T* item; // A data item
	NodeP<T>* next; // Pointer to next node

}; // end Node
