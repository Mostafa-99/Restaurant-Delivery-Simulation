#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "Region.h"
// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file


	int PromLimit;
	int NofEvents;

	

	Region A, B, C, D;

	Region region[4] = { A,B,C,D };

	Queue<Order*>AllDelvOrders; //Queue of all delivered orders sorted by finish time only
	Queue<Order*>AllDelvOrdersSorted; //sorted by both finish time and service time

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	bool PromoteOrder(int, double);
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void AutoPromote(int timestep);

	void ReturnToGarage(int);
	void AddOrder(Order*);
	bool CancelOrder(int );
	bool ThereIsActiveOrders();
	bool ThereIsMotorcyclesOut();
	void AddMotorcycle(Motorcycle*);
	void AddtoAllDelvOrders(Order* O);
	void SortAllDelvOrders();
	int GetPromLimit()const;
	
	void Load(ifstream &InFile);
	void Save();

	void RunSimulation();
	void Interactive();
	void StepByStep();
	void Silent();


};

#endif