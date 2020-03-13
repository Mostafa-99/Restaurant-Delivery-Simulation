#pragma once
#include "Event.h"

class PromotionEvent : public Event
{

private:
	double ExtraMoney;

public:
	PromotionEvent(int eTime, int ordID, double exmny=0);

	virtual void Execute(Restaurant *pRest);	//override execute function

	~PromotionEvent();


};

