#include <cstdlib>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string> 


using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\Events\CancellationEvent.h"
#include "..\Events\PromotionEvent.h"
Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		StepByStep();
		break;
	case MODE_SLNT:
		Silent();
		break;

	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}

}

bool Restaurant::ThereIsActiveOrders() {

	return(region[0].ThereIsActiveOrders() || region[1].ThereIsActiveOrders() || region[2].ThereIsActiveOrders() || region[3].ThereIsActiveOrders());


}


Restaurant::~Restaurant()
{
		delete pGUI;
}

/////////////////////////////////////////////////////////////////////////////////
void Restaurant:: Load(ifstream &InFile)
{
	int MSpeedN, MSpeedF, MSpeedV;//speed of motorcycles Normal,VIP and Frozen
	InFile >> MSpeedN;
	InFile >> MSpeedF;
	InFile >> MSpeedV;

	int n,f,v; //Number of motorcycles
	//Region A
	InFile >> n >>f>>v;
	region[0].SetNofMotorCyc(n,f,v);
	//Region B
	InFile >> n>>f>>v;
	region[1].SetNofMotorCyc(n,f,v);
	//Region C
	InFile >> n>>f>>v;
	region[2].SetNofMotorCyc(n,f,v); 
	//Region D
	InFile >> n>>f>>v;
	region[3].SetNofMotorCyc(n,f,v); 
	
	int ID = 1;

	//Setting Motorcycles in each region
	region[0].SetMotorCycles(ID,TYPE_NRM, A_REG, MSpeedN,MSpeedF,MSpeedV);
	region[1].SetMotorCycles(ID, TYPE_NRM, B_REG, MSpeedN, MSpeedF, MSpeedV);
	region[2].SetMotorCycles(ID, TYPE_NRM, C_REG, MSpeedN, MSpeedF, MSpeedV);
	region[3].SetMotorCycles(ID, TYPE_NRM, D_REG, MSpeedN, MSpeedF, MSpeedV);

	InFile >> PromLimit;
	InFile >> NofEvents;


	//Reading Events
	Event*pev=NULL;
	string eventtype;
	int TS, Id;
	for(int i=0;i<NofEvents;i++)
	{
		InFile >> eventtype;
		InFile >> TS;
		if (eventtype == "X"|| eventtype == "x")
		{
			InFile >> Id;
			pev = new CancellationEvent(TS,Id);
		}
		else if (eventtype == "P"|| eventtype == "p")
		{
			InFile >> Id;
			int exmon;
			InFile >> exmon;
			pev = new PromotionEvent(TS, Id,exmon);
		}
		else if (eventtype == "R"|| eventtype == "r")
		{
			string typname;
			string regname;

			ORD_TYPE typ;
			int dist; double mon;
			REGION reg;

			InFile >> typname;

			//checking the type of the order
			if (typname == "N"|| typname == "n") { typ = TYPE_NRM; }
			else if (typname == "F"|| typname == "f") { typ = TYPE_FROZ; }
			else if (typname == "V"|| typname == "v") { typ = TYPE_VIP; }
				
			InFile >> Id;
			InFile >> dist;
			InFile >>mon;
			InFile >> regname;


			if (regname == "A"|| regname == "a")
			{ reg = A_REG; }
			else if (regname == "B"||regname == "b")
			{ reg = B_REG; }
			else if (regname == "C"|| regname == "c")
			{ reg =C_REG ; }
			else if (regname == "D"|| regname == "d")
			{reg =D_REG ; }


			pev = new ArrivalEvent(TS,typ ,Id,dist,mon,reg);
		}
		AddEvent(pev);
	}
}

void Restaurant::Save()
{
	
	pGUI->PrintMessage("Enter Out filename: ");
	ofstream file(pGUI->GetString() + ".txt");	
	file << "FT   ID   AT   WT   ST" << endl;
	Order*ptr;
	while (!AllDelvOrdersSorted.isEmpty()) {

		AllDelvOrdersSorted.dequeue(ptr);
		file << ptr->GetFT() << "   " << ptr->GetID() << "    " << ptr->GetAR() << "     " << ptr->GetWT() << "     " << ptr->GetSV() << endl;

	}



	int servedVip, servedNorm, servedFroz, totalSurvReg;
	int SumServVIP = 0, SumServNorm = 0, SumServFroz = 0, totalSurvRest = 0;
	int nofMotorVip, nofMotorNorm, nofMotorFroz, totalnoMotorCReg;
	int SumnofMotorVip = 0, SumnofMotorNorm = 0, SumnofMotorFroz = 0, totalnofMotorCRest = 0;
	float AvgWaitRest=0, AvgServRest=0;
	float AvgWaitReg, AvgServReg;

	file << endl;
	for (int i = 0; i < REG_CNT; i++) //Saving Regions Info
	{
		file << endl;
		if (i == 0) {
			file << "Region A:" << endl;
		}
		else if (i == 1){
		
			file << "Region B:" << endl;

		}
		else if (i == 2) {

			file << "Region C:" << endl;

		}
		else if (i == 3) {

			file << "Region D:" << endl;

		}
		servedVip = region[i].GetNofVIPServed();
		servedNorm = region[i].GetNofNormalServed();
		servedFroz = region[i].GetNofFrozenServed();
		totalSurvReg = servedFroz + servedNorm + servedVip;
		file << "Orders: "<<totalSurvReg;
		file << "[Norm:" << servedNorm << ", Froz:" << servedFroz << ", VIP:" << servedVip << "]" << endl;


		nofMotorFroz = region[i].GetNofFrozMotorC();
		nofMotorNorm = region[i].GetNofNormalMotorC();
		nofMotorVip = region[i].GetNofVIPMotorC();
		totalnoMotorCReg = nofMotorFroz + nofMotorNorm + nofMotorVip;
		file << "MotorC: " << totalnoMotorCReg;
		file << "[Norm:" <<nofMotorNorm << ", Froz:" << nofMotorFroz << ", VIP:" << nofMotorVip << "]" << endl;


		AvgWaitReg = region[i].GetTotalWaitingTime() / float(servedFroz + servedNorm + servedVip);
		AvgServReg = region[i].GetTotalServiceTime() / float(servedFroz + servedNorm + servedVip);
		file << "Avg Wait: " <<AvgWaitReg <<", ";
		file << "Avg Serv: " <<AvgServReg << endl;


		AvgServRest += AvgServReg;
		AvgWaitRest += AvgWaitReg;

		SumnofMotorFroz += nofMotorFroz;
		SumnofMotorNorm += nofMotorNorm;
		SumnofMotorVip += nofMotorVip;
		totalnofMotorCRest += totalnoMotorCReg;

		totalSurvRest += totalSurvReg;
		SumServFroz += servedFroz;
		SumServNorm += servedNorm;
		SumServVIP += servedVip;
		file << endl;
	}

	//Saving Restaurant Info
	file << "Whole Restaurant:" << endl;

	file << "Orders: " << totalSurvRest;
	file << "[Norm:" << SumServNorm << ", Froz:" << SumServFroz << ", VIP:" << SumServVIP << "]" << endl;

	file << "MotorC: " << totalnofMotorCRest;
	file << "[Norm:" << SumnofMotorNorm << ", Froz:" << SumnofMotorFroz << ", VIP:" << SumnofMotorVip << "]" << endl;

	file << "Avg Wait: " << AvgWaitRest << ", ";
	file << "Avg Serv: " << AvgServRest << endl;
}

void Restaurant::AddOrder(Order* O) {


	region[O->GetRegion()].AddOrder(O);


}

bool Restaurant::CancelOrder(int id) {

	for (int i = 0; i < REG_CNT; i++)
	{
		if (region[i].CancelOrder(id)) return true;

	}
	return false;
}

bool Restaurant::PromoteOrder(int id , double exmny) {
	
	Order* PromotedOrder =NULL;
	for (int i = 0; i < REG_CNT; i++)
	{
		PromotedOrder = region[i].CancelToPromoteOrder(id);

		if (PromotedOrder) 
		{
			double newmoney = PromotedOrder->GetTM() + exmny;
			PromotedOrder->SetTM(newmoney);
			PromotedOrder->SetType(TYPE_VIP);
			this->AddOrder(PromotedOrder);
			return true;
		}
	}
	return false;
}


void Restaurant::AddMotorcycle(Motorcycle* M) {

	
	region[M->GetRegion()].AddMotorcycle(M);


	}

void Restaurant::Interactive() {

	string ServedA, ServedB, ServedC, ServedD;
	string NofServedA, NofServedB, NofServedC, NofServedD;
	int CurrentTimeStep = 0;
	pGUI->PrintMessage("Enter filename: ");
	ifstream file(pGUI->GetString() + ".txt");	//get user input as a string 
	if (file.is_open())
	{
		Load(file);
		pGUI->UpdateInterface();
		pGUI->PrintMessage("Click to move to the next time step ");

		while (!EventsQueue.isEmpty() || ThereIsActiveOrders() || ThereIsMotorcyclesOut())
		{


			pGUI->waitForClick();
			CurrentTimeStep++;
			string timestep = to_string(CurrentTimeStep);
			pGUI->PrintMessage("Current time step: " + timestep);
			ExecuteEvents(CurrentTimeStep);
			pGUI->UpdateInterface();

			for (int i = 0; i < REG_CNT; i++)
			{
				region[i].AddToDraw(this->pGUI);
			}

			ReturnToGarage(CurrentTimeStep);  //Check if there are any motorcycles that should return to Garage Or if there are
											//any orders that are delivered so we can increase the Number of delivered orders

			AutoPromote(CurrentTimeStep); //Auto promote any normal orders whose waiting time exceeds the promotion time limit.

			NofServedA = region[0].NumberofServed();
			NofServedB = region[1].NumberofServed();
			NofServedC = region[2].NumberofServed();
			NofServedD = region[3].NumberofServed();



			//for region A
			pGUI->PrintMessage(10, 540, "-->For Region A: ");
			pGUI->PrintMessage(115, 540, region[0].PrintInfo());
			pGUI->PrintMessage(480, 540, " --- " + NofServedA + " --- ");
			pGUI->PrintMessage(700, 540, "Assigned: "+ ServedA );
			//for region B
			pGUI->PrintMessage(10, 560, "-->For Region B: ");
			pGUI->PrintMessage(115, 560, region[1].PrintInfo());
			pGUI->PrintMessage(480, 560, " --- " + NofServedB + " --- ");
			pGUI->PrintMessage(700, 560, "Assigned: " + ServedB );
			//for region C
			pGUI->PrintMessage(10, 580, "-->For Region C: ");
			pGUI->PrintMessage(115, 580, region[2].PrintInfo());
			pGUI->PrintMessage(480, 580, " --- " + NofServedC + " --- ");
			pGUI->PrintMessage(700, 580, "Assigned: " + ServedC);
			//for region D
			pGUI->PrintMessage(10, 600, "-->For Region D: ");
			pGUI->PrintMessage(115, 600, region[3].PrintInfo());
			pGUI->PrintMessage(480, 600, " --- " + NofServedD + " --- ");
			pGUI->PrintMessage(700, 600, "Assigned: " + ServedD );

			//Serve All Orders that can be served in that time step
			ServedA = region[0].ServeOrders(CurrentTimeStep);
			ServedB = region[1].ServeOrders(CurrentTimeStep);
			ServedC = region[2].ServeOrders(CurrentTimeStep);
			ServedD = region[3].ServeOrders(CurrentTimeStep);
			
			pGUI->ResetDrawingList();

		}
	}
	Sleep(1000);
	pGUI->UpdateInterface();
	pGUI->waitForClick();
	SortAllDelvOrders();
	Save();
}
void Restaurant::StepByStep()
{
	string ServedA, ServedB, ServedC, ServedD;
	string NofServedA, NofServedB, NofServedC, NofServedD;
	int CurrentTimeStep = 0;
	pGUI->PrintMessage("Enter filename: ");
	ifstream file(pGUI->GetString() + ".txt");	//get user input as a string
	if (file.is_open())
	{
		Load(file);
		pGUI->UpdateInterface();

		while (!EventsQueue.isEmpty() || ThereIsActiveOrders() || ThereIsMotorcyclesOut())
		{
			Sleep(1000);

			CurrentTimeStep++;
			string timestep = to_string(CurrentTimeStep);
			pGUI->PrintMessage("Current time step: " + timestep);
			ExecuteEvents(CurrentTimeStep);
			pGUI->UpdateInterface();
			for (int i = 0; i < REG_CNT; i++)
			{
				region[i].AddToDraw(this->pGUI);
			}

			ReturnToGarage(CurrentTimeStep);
			AutoPromote(CurrentTimeStep);

			NofServedA = region[0].NumberofServed();
			NofServedB = region[1].NumberofServed();
			NofServedC = region[2].NumberofServed();
			NofServedD = region[3].NumberofServed();

			//for region A
			pGUI->PrintMessage(10, 540, "-->For Region A: ");
			pGUI->PrintMessage(115, 540, region[0].PrintInfo());
			pGUI->PrintMessage(480, 540, " --- " + NofServedA + " --- ");
			pGUI->PrintMessage(700, 540, "Assigned: " + ServedA);


			//for region B
			pGUI->PrintMessage(10, 560, "-->For Region B: ");
			pGUI->PrintMessage(115, 560, region[1].PrintInfo());
			pGUI->PrintMessage(480, 560, " --- " + NofServedB + " --- ");
			pGUI->PrintMessage(700, 560, "Assigned: " + ServedB);

			//for region C
			pGUI->PrintMessage(10, 580, "-->For Region C: ");
			pGUI->PrintMessage(115, 580, region[2].PrintInfo());
			pGUI->PrintMessage(480, 580, " --- " + NofServedC + " --- ");
			pGUI->PrintMessage(700, 580, "Assigned: " + ServedC);

			//for region D
			pGUI->PrintMessage(10, 600, "-->For Region D: ");
			pGUI->PrintMessage(115, 600, region[3].PrintInfo());
			pGUI->PrintMessage(480, 600, " --- " + NofServedD + " --- ");
			pGUI->PrintMessage(700, 600, "Assigned: " + ServedD);

			ServedA = region[0].ServeOrders(CurrentTimeStep);
			ServedB = region[1].ServeOrders(CurrentTimeStep);
			ServedC = region[2].ServeOrders(CurrentTimeStep);
			ServedD = region[3].ServeOrders(CurrentTimeStep);

			pGUI->ResetDrawingList();


		}
	}
	Sleep(1000);
	pGUI->UpdateInterface();
	SortAllDelvOrders();
	Save();
	pGUI->PrintMessage("Click to END the program");
	pGUI->waitForClick();
	
}
void Restaurant:: Silent()
{
	string ServedA, ServedB, ServedC, ServedD;
	string NofServedA, NofServedB, NofServedC, NofServedD;
	int CurrentTimeStep = 0;
	pGUI->PrintMessage("Enter filename: ");
	ifstream file(pGUI->GetString() + ".txt");	//get user input as a string
	if (file.is_open())
	{
		Load(file);
		pGUI->UpdateInterface();

		while (!EventsQueue.isEmpty() || ThereIsActiveOrders()|| ThereIsMotorcyclesOut())
		{

			CurrentTimeStep++;
			
			ExecuteEvents(CurrentTimeStep);
			
			ReturnToGarage(CurrentTimeStep);
			AutoPromote(CurrentTimeStep);

			NofServedA = region[0].NumberofServed();
			NofServedB = region[1].NumberofServed();
			NofServedC = region[2].NumberofServed();
			NofServedD = region[3].NumberofServed();

			ServedA = region[0].ServeOrders(CurrentTimeStep);
			ServedB = region[1].ServeOrders(CurrentTimeStep);
			ServedC = region[2].ServeOrders(CurrentTimeStep);
			ServedD = region[3].ServeOrders(CurrentTimeStep);

		}
	}
	SortAllDelvOrders();
	Save();
	pGUI->PrintMessage("Click to END the program");
	pGUI->waitForClick();
}


void Restaurant::ReturnToGarage(int timestep)
{

	for (int i = 0; i < REG_CNT; i++)
	{
		region[i].ReturnToGarage(timestep, this);

	}


}

bool  Restaurant::ThereIsMotorcyclesOut() {


	return(region[0].ThereIsMotorcyclesOut() || region[1].ThereIsMotorcyclesOut() || region[2].ThereIsMotorcyclesOut() || region[3].ThereIsMotorcyclesOut());


}
void Restaurant::AddtoAllDelvOrders(Order* O) {

	AllDelvOrders.enqueue(O);

}

void Restaurant::SortAllDelvOrders() {

	while (!AllDelvOrders.isEmpty()) {

		Order *sortme;
		Order *checkme;
		PriorityQueue<Order*> tempsort;
		AllDelvOrders.dequeue(sortme);

		double priority = 1 / double(sortme->GetSV());

		tempsort.PriorEnqueue(sortme, priority);

		while (AllDelvOrders.peekFront(checkme)) {

			if (checkme->GetFT() == sortme->GetFT()) {

				AllDelvOrders.dequeue(checkme);

				priority= 1 / double(checkme->GetSV());

				tempsort.PriorEnqueue(checkme, priority);

			}
			else
			{
				break;
			}


		}

		Order* Addme;

		while (tempsort.dequeue(Addme)) {

			AllDelvOrdersSorted.enqueue(Addme);

		}





	}




}

int Restaurant::GetPromLimit()const {

	return PromLimit;
}

void Restaurant::AutoPromote(int timestep) {

	for (int i = 0; i < REG_CNT; i++)
	{
		region[i].AutoPromote(timestep, this);

	}


}