#include "Order.h"

Order::Order(int id, ORD_TYPE r_Type, REGION r_region)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;	
}

Order::Order(int id) {

	ID = (id > 0 && id < 1000) ? id : 0;	//1<ID<999
}

Order::~Order()
{
	
}

int Order::GetID()
{
	return ID;
}

ORD_TYPE Order::GetType() const
{
	return type;
}

void Order::SetType(ORD_TYPE T)
{
	type=T ;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetRegion(REGION r)
{
	Region=r ;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

double Order:: GetTM()
{
	return totalMoney ;
}

void  Order:: SetTM(double m)
{
	if(m>0)
		totalMoney=m ;
	else
		totalMoney=0 ;
}

int  Order:: GetAR()
{
	return ArrTime ;
}

void  Order:: SetAR(int a)
{
	if(a>0)
		ArrTime=a ;
	else
		ArrTime=0 ;
}

int  Order:: GetSV()
{
	return ServTime ;
}

void  Order:: SetSV(int s)
{
	if(s>0)
		ServTime=s ;
	else
		s=0 ;
}

int  Order:: GetFT()
{
	return FinishTime ;
}

void  Order:: SetFT(int f)
{
	if(f>0)
		FinishTime=f ;
	else
		FinishTime=0;
}

int  Order:: GetWT()
{
	return WaitingTime ;
}

void  Order:: SetWT(int a)
{
	if(a>0)
		WaitingTime=a ;
	else
		WaitingTime=0 ;
}




bool Order::operator==(const Order& O) {

	return (this->ID == O.ID);
}

