#ifndef P_NODE_H_
#define P_NODE_H_


template < typename T>
class NodeWP
{
	template<class T> friend class PriorityQueue;
	T item; // A data item
	double priority;
	NodeWP<T>* next; // Pointer to next node
public:
	NodeWP();
	NodeWP(const T & r_Item, double P);	
	
	
}; // end Node

template < typename T>
NodeWP<T>::NodeWP() {

	next = nullptr;

}
template < typename T>
NodeWP<T>::NodeWP(const T & r_Item, double P) {
	next = nullptr;
	item = r_Item;
	priority = P;

}






#endif