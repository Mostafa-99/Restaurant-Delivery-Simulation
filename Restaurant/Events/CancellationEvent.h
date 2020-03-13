#pragma once
#include "Event.h"

class CancellationEvent : public Event
{
public:
	CancellationEvent(int eTime, int ordID);

	virtual void Execute(Restaurant *pRest);	//override execute function
	~CancellationEvent();

};

