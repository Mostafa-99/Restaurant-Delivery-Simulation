#include "PromotionEvent.h"
#include "..\Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int ordID, double exmny) : Event(eTime, ordID)
{

	ExtraMoney = (exmny>0) ? exmny : 0;

}

void PromotionEvent::Execute(Restaurant *pRest) {

	pRest->PromoteOrder( this->OrderID, this->ExtraMoney);

}

PromotionEvent::~PromotionEvent()
{
}