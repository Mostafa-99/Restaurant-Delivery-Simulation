#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"
#include "Order.h"


class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	Order* AssignedOrder;

public:
	Motorcycle(int id,ORD_TYPE typ,REGION reg,int spd);

	void SetID(int);
	int GetID();

	void SetType(ORD_TYPE);
	ORD_TYPE GetType();

	void SetSpeed(int);
	int GetSpeed();

	void SetRegion(REGION);
	REGION GetRegion();

	void SetStatus(STATUS);
	STATUS GetStatus();

	void AssignOrder(Order* O);
	Order* GetOrder();

	virtual ~Motorcycle();
};

#endif