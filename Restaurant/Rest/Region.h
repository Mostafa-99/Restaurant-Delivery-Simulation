#pragma once

#include <string> 
using namespace std;

#include "..\Generic_DS\Queue.h"
#include "..\Generic_DS\PriorityQueue.h"
#include "..\Generic_DS\LinkedList.h"
#include "..\Generic_DS\Stack.h"
#include "..\Generic_DS\EmergencyQueue.h"

#include "..\Events\Event.h"
#include "..\GUI\GUI.h"

#include "Order.h"
#include "Motorcycle.h"

class Restaurant ; //forward decleration 

class Region
{
	///orders lists:

	// 1-Normal Orders:
	EmergencyQueue<Order> NormalOrders;

	// 3-Frozen Oders
	Queue<Order*> FrozenOrders;

	// 3-VIP Oreders
	PriorityQueue<Order*> VIPOrders;

	///Motorcyle Lists:

	// 1-Normal Motorcyles
	Queue<Motorcycle*> NormalGarage;
	
	// 2-Frozen Motorcycles
	Queue<Motorcycle*> FrozenGarage;

	// 3-VIP Motorcycles
	Queue<Motorcycle*> VIPGarage;


	PriorityQueue<Motorcycle*> Street; //Motorcycles busy surving orders
	PriorityQueue<Motorcycle*> WayBack; //MotorCycles on their way back


	int NofMotorCycN; //Number of normal motorcycles
	int NofMotorCycV; //Number of VIP motorcycles
	int NofMotorCycF; //Number of Frozen motorcycles

	int NofNormalServed; //Number of served Normal orders so far
	int NofFrozenServed; //Number of served Frozen orders so far
	int NofVIPServed; //Number of served VIP orders so far

	int totalwait=0;
	int totalserv=0;



public:


	void AddToDraw(GUI *pGUI);

	void SelectTodelete(); // Function to select an order from each type and delete it [For phase 1]
	bool ThereIsActiveOrders(); //checks if there are any orders in any order type list
	bool ThereIsMotorcyclesOut(); //checks if there are any Motorcyles in the street or the way back 

	string PrintInfo();

	void AddOrder(Order*);
	bool CancelOrder(int);
	Order* CancelToPromoteOrder(int);
	void AutoPromote(int timestep,Restaurant*pRest);

	void AddMotorcycle(Motorcycle*);
	void SetNofMotorCyc(int,int,int);
	void SetMotorCycles(int&,ORD_TYPE,REGION,int,int,int);
	void ReSetMotorCyc();

	void AssignOrderToMotorcycle(Order*,Motorcycle*,int timestep); 
	void ReturnToGarage(int, Restaurant* pRest);
	string ServeOrders(int);
	string NumberofServed()const;

	int GetNofNormalServed() const;
	int GetNofFrozenServed() const;
	int GetNofVIPServed() const;

	int GetNofNormalMotorC()const;
	int GetNofVIPMotorC()const;
	int GetNofFrozMotorC()const;

	int GetTotalWaitingTime()const;
	int GetTotalServiceTime()const;

	
	Region();
	~Region();

};


