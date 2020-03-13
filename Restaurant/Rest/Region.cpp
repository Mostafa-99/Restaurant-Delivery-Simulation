#include "Region.h"
#include "Restaurant.h"



Region::Region()
{
	NofNormalServed = 0;
	NofFrozenServed = 0;
	NofVIPServed = 0;

}

void Region::AddOrder(Order* O) {

	ORD_TYPE type = O->GetType();
	switch (type)
	{
	case TYPE_NRM: 
		NormalOrders.enqueue(O);
		break;
	case TYPE_FROZ:
		FrozenOrders.enqueue(O);
		break;
	case TYPE_VIP:
		double priority = (O->GetTM() * 2) / (O->GetAR() * O->GetDistance()); //total money*2/(arrival time*Distance)
		VIPOrders.PriorEnqueue(O, priority);
		break;
	
	}
	

}

void Region::AddToDraw(GUI *pGUI) {

	Order *temp=nullptr;
	
	//For VIP
	int c;
	Order ** arr = VIPOrders.toArray(c);

	for (int i = 0; i < c; i++) {
		pGUI->AddOrderForDrawing(arr[i]);
		pGUI->UpdateInterface();

	}
	
	// For Frozen
	for (int i = 0; i < FrozenOrders.getCount(); i++) {

		FrozenOrders.dequeue(temp);
		pGUI->AddOrderForDrawing(temp);
		pGUI->UpdateInterface();
		FrozenOrders.enqueue(temp);

	}

	//For Normal
	for (int i = 0; i < NormalOrders.getCount(); i++) {

		NormalOrders.dequeue(temp);
		pGUI->AddOrderForDrawing(temp);
		pGUI->UpdateInterface();
		NormalOrders.enqueue(temp);

	}



}

string Region::PrintInfo() {

	//Orders INFO

	string OrdersINFO = "Waiting Orders: N: " + to_string(NormalOrders.getCount()) + ", "

		+ "F: " + to_string(FrozenOrders.getCount()) + ", "

		+ "V: " + to_string(VIPOrders.Getcount()) + " --- ";


	//Motorcycles INFO

	string MotorcycleINFO = "Motorcycles: N: " + to_string(NormalGarage.getCount()) + ", "

		+ "F: " + to_string(FrozenGarage.getCount()) + ", "

		+ "V: " + to_string(VIPGarage.getCount()) + " ";


	string Return = OrdersINFO + MotorcycleINFO;

	return Return;
	



}

bool Region::CancelOrder(int id) {

	Order*tempOrder = new Order(id); //create a temporary order with the same id as the one that should be cancelled from the list.

	Order* RemovedOrder = NormalOrders.EmergencyExit(tempOrder);
	delete tempOrder; 
	
	if (RemovedOrder) 
	{
		delete RemovedOrder;
	}
	else
	{
		return false;
	}

		return true;
}

Order* Region::CancelToPromoteOrder(int id) {

	Order*tempOrder = new Order(id); //create a temporary order with the same id as the one that should be cancelled from the list.

	Order* RemovedOrder = NormalOrders.EmergencyExit(tempOrder);
	delete tempOrder;

	return RemovedOrder;

}


void Region::SelectTodelete() {

	Order* ToDeleteVIP=NULL;
	Order* ToDeleteFrozen = NULL;
	Order* ToDeleteNormal = NULL;
	if (VIPOrders.dequeue(ToDeleteVIP)) 
	{
		delete ToDeleteVIP;
	}

	if (FrozenOrders.dequeue(ToDeleteFrozen)) 
	{
		delete ToDeleteFrozen;
	}

	if(NormalOrders.dequeue(ToDeleteNormal)) 
	{
		delete ToDeleteNormal;
	}



}

bool Region::ThereIsActiveOrders() {


	if (!NormalOrders.isEmpty()) return true;

	if (!FrozenOrders.isEmpty()) return true;

	if (!VIPOrders.isEmpty()) return true;

	return false;


}



void Region::AddMotorcycle(Motorcycle* O) {
	ORD_TYPE type = O->GetType();
	switch (type)
	{
	case TYPE_NRM:
		NormalGarage.enqueue(O);
		break;
	case TYPE_FROZ:
		FrozenGarage.enqueue(O);
		break;
	case TYPE_VIP:
		VIPGarage.enqueue(O);
		break;

	}

}

void Region::SetNofMotorCyc(int n,int f,int v)
{
	NofMotorCycN = n;
	NofMotorCycF = f;
	NofMotorCycV = v;

}



void Region::SetMotorCycles(int &ID,ORD_TYPE O,REGION r,int MSpeedN,int MSpeedF,int MSpeedV)
{
	for (int i = 0; i < NofMotorCycN; i++)
	{	
		Motorcycle *m=new Motorcycle(ID,TYPE_NRM,r,MSpeedN);
		AddMotorcycle(m);
		ID++;
	}
	for (int i = 0; i < NofMotorCycF; i++)
	{
		Motorcycle *m=new Motorcycle(ID, TYPE_FROZ, r, MSpeedF);
		AddMotorcycle(m);
		ID++;
	}for (int i = 0; i < NofMotorCycV; i++)
	{
		Motorcycle *m=new Motorcycle(ID, TYPE_VIP, r, MSpeedV);
		AddMotorcycle(m);
		ID++;
	}
}

void Region:: ReSetMotorCyc()
{
	Motorcycle* todelete = NULL;
	int normcount=NormalGarage.getCount();
	int VIPcount = VIPGarage.getCount();
	int Frozcount = FrozenGarage.getCount();

	for (int i = 0; i <normcount ; i++)
	{
		NormalGarage.dequeue(todelete);
		delete todelete;
	}
	for (int i = 0; i < VIPcount; i++)
	{
		VIPGarage.dequeue(todelete);
		delete todelete;
	}
	for (int i = 0; i < Frozcount; i++)
	{
		FrozenGarage.dequeue(todelete);
		delete todelete;
	}
}

Region::~Region()
{
}

void Region::AssignOrderToMotorcycle(Order* O, Motorcycle* M,int timestep) 
{

	M->AssignOrder(O);
	M->SetStatus(SERV); //change the status to be in service


	int servicetime = (O->GetDistance() / M->GetSpeed()); // calculate the service time using order's distance and the motorcyle's speed

	int waitingtime = timestep - O->GetAR(); // calculate the waiting time by subtracting the arrival time from the current time step 

	int finishtime = O->GetAR() + waitingtime + servicetime;  // calculate the order's finish time

	O->SetSV(servicetime); //set service time
	O->SetWT(waitingtime); //set waiting time
	O->SetFT(finishtime); //set finish time

	
	double priorityofreturn = 1 / double(O->GetFT()); //the priority is inversely propotional with the finish time.

	

	Street.PriorEnqueue(M, priorityofreturn);
	totalwait += waitingtime;
	totalserv += servicetime;
}

void Region::ReturnToGarage(int timestep,Restaurant*pRest)
{

	Motorcycle* Putonthewayback;

	while (Street.peekFront(Putonthewayback))
	{

		if ((Putonthewayback->GetOrder())->GetFT()  <= timestep)
		{

			Motorcycle* Motortoreturn;
			Street.dequeue(Motortoreturn);

			Order*Addtodelivered = Motortoreturn->GetOrder();
			
			pRest->AddtoAllDelvOrders(Addtodelivered);
		
			ORD_TYPE type = (Motortoreturn->GetOrder())->GetType();

			switch (type)
			{
			case TYPE_NRM:
				NofNormalServed++;
				break;
			case TYPE_FROZ:
				NofFrozenServed++;
				break;
			case TYPE_VIP:
				NofVIPServed++;
				break;

			}

			double priotiywayback = (1 / (Motortoreturn->GetOrder())->GetSV());
			
			WayBack.PriorEnqueue(Motortoreturn, priotiywayback);

		}
		else
		{
			break;
		}



	}

	Motorcycle* check;
	while ( WayBack.peekFront(check))
	{

		if (((check->GetOrder())->GetFT() + (check->GetOrder())->GetSV()) <= timestep)
		{

			Motorcycle* Motortoreturn;
			WayBack.dequeue(Motortoreturn);

			Motortoreturn->AssignOrder(NULL);

			Motortoreturn->SetStatus(IDLE);

			AddMotorcycle(Motortoreturn);

		}
		else
		{
			break;
		}



	}


}

string Region::ServeOrders(int timestep) {


	Order* Ordertobeserved;
	Motorcycle* Motortoserve;

	string Assigned = " ";
	

	////////////////////////////To serve the VIP Orders/////////////////////////////

	while (!VIPOrders.isEmpty() && !VIPGarage.isEmpty())
	{

		

		VIPOrders.dequeue(Ordertobeserved);
		VIPGarage.dequeue(Motortoserve);

		string S = "V" + to_string(Motortoserve->GetID()) + "(V" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);

	}


	while (!VIPOrders.isEmpty() && !NormalGarage.isEmpty())
	{

		VIPOrders.dequeue(Ordertobeserved);
		NormalGarage.dequeue(Motortoserve);

		string S = "N" + to_string(Motortoserve->GetID()) + "(V" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);
	}

	while (!VIPOrders.isEmpty() && !FrozenGarage.isEmpty())
	{

		VIPOrders.dequeue(Ordertobeserved);
		FrozenGarage.dequeue(Motortoserve);

		string S = "F" + to_string(Motortoserve->GetID()) + "(V" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);
	}


	/////////////////////// To serve the Frozen Orders//////////////////////////

	while (!FrozenOrders.isEmpty() && !FrozenGarage.isEmpty()) 
	
	{
		FrozenOrders.dequeue( Ordertobeserved);
		FrozenGarage.dequeue(Motortoserve);

		string S = "F" + to_string(Motortoserve->GetID()) + "(F" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);

	}


	/////////////////////// To serve the Normal Orders//////////////////////////

	while (!NormalOrders.isEmpty() && !NormalGarage.isEmpty())
	{
		NormalOrders.dequeue(Ordertobeserved);

		NormalGarage.dequeue(Motortoserve);

		string S = "N" + to_string(Motortoserve->GetID()) + "(N" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);

	}

	while (!NormalOrders.isEmpty() && !VIPGarage.isEmpty()) 
	{
		NormalOrders.dequeue(Ordertobeserved);
		
		VIPGarage.dequeue(Motortoserve);

		string S = "V" + to_string(Motortoserve->GetID()) + "(N" + to_string(Ordertobeserved->GetID()) + "),  ";
		Assigned += S;

		AssignOrderToMotorcycle(Ordertobeserved, Motortoserve, timestep);


	}


	////////////////////End of Assignment///////////////////////////////////


	return Assigned; // return string containing the assigned orders to motorcycles



}

int Region::GetNofNormalServed() const{

	return NofNormalServed;
}
int Region::GetNofFrozenServed()const {

	return NofFrozenServed;
}
int Region::GetNofVIPServed()const {

	return NofVIPServed;

}
int Region::GetNofNormalMotorC()const
{
	return NofMotorCycN;
}
int Region::GetNofVIPMotorC()const
{
	return NofMotorCycV;
}
int Region::GetNofFrozMotorC()const
{
	return NofMotorCycF;
}
int Region::GetTotalWaitingTime()const
{
	return totalwait;
}
int Region::GetTotalServiceTime()const
{
	return totalserv;
}


string Region::NumberofServed()const {

	string N, F, V,served;

	N = "N: " + to_string(NofNormalServed);
	F = "F: " + to_string(NofFrozenServed);
	V = "V: " + to_string(NofVIPServed);

	served = "Served Orders: " + N + ", " + F + ", " + V;
	
	return served;

}

bool Region::ThereIsMotorcyclesOut() {

	if (!Street.isEmpty()) return true;

	if (!WayBack.isEmpty()) return true;

	return false;


}

void Region::AutoPromote(int timestep, Restaurant*pRest) {

	if (NormalOrders.isEmpty()) return;

	Order*Promoteme;
	int waitingtime;

	while (NormalOrders.peekFront(Promoteme)) {

		waitingtime = (timestep - Promoteme->GetAR());
		if (waitingtime >= pRest->GetPromLimit()) {

			NormalOrders.dequeue(Promoteme);

			Promoteme->SetType(TYPE_VIP);

			AddOrder(Promoteme);


		}
		else
		{
			return;
		}

	}


}