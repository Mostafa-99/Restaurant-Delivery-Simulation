#include "Motorcycle.h"


Motorcycle::Motorcycle(int id, ORD_TYPE typ, REGION reg, int spd)
{
	SetID(id);
	SetType(typ);
	SetRegion(reg);
	SetSpeed(spd);
	SetStatus(IDLE);
	AssignOrder(nullptr);
}

void Motorcycle:: SetID(int id)
{
	ID = (id > 0 && id < 1000) ? id : 0;
}
int Motorcycle::GetID()
{
	return ID;

}

void Motorcycle::SetType(ORD_TYPE typ)
{
	type = typ;
}
ORD_TYPE Motorcycle::GetType()
{
	return type;
}

void Motorcycle::SetSpeed(int s)
{
	if (!(s <= 0))
	{
		speed = s;
	}
	else
	{
		speed = 0;
	}
}
int Motorcycle::GetSpeed()
{
	return speed;
}

void Motorcycle::SetRegion(REGION reg)
{
	region = reg;
}
REGION Motorcycle::GetRegion()
{
	return region;
}

void Motorcycle::SetStatus(STATUS stat)
{
	status = stat;
}
STATUS Motorcycle::GetStatus()
{
	return status;
}

void Motorcycle::AssignOrder(Order* O)
{
	AssignedOrder = O;

}
Order* Motorcycle::GetOrder()
{
	return AssignedOrder;

}

Motorcycle::~Motorcycle()
{
}


