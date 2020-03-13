#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 

	double totalMoney;	//Total order money

	int ArrTime, ServTime, WaitingTime, FinishTime;	//arrival, service start, and finish times
	
	
	

public:
	Order(int ID, ORD_TYPE r_Type, REGION r_region);
	Order(int ID);

	virtual ~Order();


	// setters and getters
	int GetID();
	void SetType(ORD_TYPE t);
	void SetRegion(REGION r);
	double GetTM();  //Total Money 
	void SetTM(double m);
	int GetAR(); //Arrival Time
	void SetAR(int a);
	int GetSV();   //serv Time
	void SetSV(int s);
	int GetFT();  //Finish Time
	void SetFT(int f);
	int GetWT();  //Waiting Time
	void SetWT(int w);
	ORD_TYPE GetType() const;
	REGION GetRegion() const;
	void SetDistance(int d);
	int GetDistance() const;
	
	


	// overloading operators:
	//1- ==

	bool operator==(const Order&);
	


};

#endif