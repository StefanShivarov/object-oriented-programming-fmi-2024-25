// practicum_11.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Player.h"
#include "Guest.h"
#include "LoggedUser.h"
#include "PremiumPlayer.h"
#include <crtdbg.h>
using std::cout;
using std::endl;
int main()
{
	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	while(true)
	{
		

		char** subjects= new char*[3];
		subjects[0] = new char[100];
		subjects[1] = new char[100];
		subjects[2] = new char[100];

		strcpy(subjects[0], "English");
		strcpy(subjects[1], "Math");
		strcpy(subjects[2], "OOP");

		Player* p = new Guest(100);
		int playerSize = 10;
		Player** players = new Player * [playerSize] {nullptr};
		players[0] = new LoggedUser("1234");
		players[1] = new PremiumPlayer("Serhan", subjects, 3);
		players[0]->setPoints(400);
		players[0]->levelUp();
		cout << players[0]->getStar();
		p->setPoints(5000);
		p->levelUp();
		cout << p->getStar();
		p->levelUp();
		p->levelUp();
		p->levelUp();
		for (int i = 0; i < 3; i++)
		{
			delete[] subjects[i];
		}
		delete[] subjects;
		delete p;
		for (int i = 0; i < playerSize; i++)
		{
			delete players[i];
		}
		delete[] players;
	}
	_CrtDumpMemoryLeaks();

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
