#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent(int eTime, int oID, ORD_TYPE oType,REGION reg):Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
}
ArrivalEvent::ArrivalEvent(int eTime, ORD_TYPE oType, int oID, int dist, double money, REGION reg) : Event(eTime, oID)
{
	OrdType = oType;
	OrdRegion = reg;
	OrdMoney = money;
	OrdDistance = dist;
}
void ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	Order* neworder = new Order(this->OrderID, this->OrdType, this->OrdRegion);

	neworder->SetDistance(this->OrdDistance);
	neworder->SetAR(this->EventTime);
	neworder->SetTM(this->OrdMoney);

	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1

	pRest->AddOrder(neworder);

	
}
