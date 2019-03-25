#include "LoadFile.h"

void loadFile(int& seed, vector<CBase*>& board)
{
	ifstream SeedFile("seed.txt");

	SeedFile >> seed;

	ifstream infile("Monopoly.txt");

	for (int i = 0; i < 26; i++)
	{
		string type = "";;
		string fullName = "";;
		string Cost = "";
		string Rent = "";
		string group = "";
		string secondName = "";

		getline(infile, type, ' ');

		if (stoi(type) == 1)
		{
			getline(infile, fullName, ' ');
			getline(infile, secondName, ' ');
			getline(infile, Cost, ' ');
			getline(infile, Rent, ' ');
			getline(infile, group);

			CProperty* property(new CProperty);
			property->setName(fullName + " " + secondName);
			property->setCost(stoi(Cost));
			property->setType(stoi(type));
			property->setRent(stoi(Rent));
			property->setGroup(stoi(group));

			board.push_back(property);
		}
		else if (stoi(type) == 2)
		{
			getline(infile, fullName);
			CGo* go(new CGo);
			go->setName(fullName);
			go->setType(stoi(type));

			board.push_back(go);
		}
		else if (stoi(type) == 3)
		{
			getline(infile, fullName, ' ');
			getline(infile, secondName);

			CAirport* airport(new CAirport);
			airport->setName(fullName + " " + secondName);
			airport->setType(stoi(type));

			board.push_back(airport);
		}
		else if (stoi(type) == 4)
		{
			getline(infile, fullName);

			CBonus* Bonus(new CBonus);
			Bonus->setName(fullName);
			Bonus->setType(stoi(type));

			board.push_back(Bonus);
		}
		else if (stoi(type) == 5)
		{
			getline(infile, fullName);

			CPenalty* Penalty(new CPenalty);
			Penalty->setName(fullName);
			Penalty->setType(stoi(type));

			board.push_back(Penalty);
		}
		else if (stoi(type) == 6)
		{
			getline(infile, fullName);

			CJail* Jail(new CJail);
			Jail->setName(fullName);
			Jail->setType(stoi(type));

			board.push_back(Jail);
		}
		else if (stoi(type) == 7)
		{
			getline(infile, fullName);

			CGoToJail* goToJail(new CGoToJail);
			goToJail->setName(fullName);
			goToJail->setType(stoi(type));

			board.push_back(goToJail);
		}
		else if (stoi(type) == 8)
		{
			getline(infile, fullName);

			CFreeParking* freeParking(new CFreeParking);
			freeParking->setName(fullName);
			freeParking->setType(stoi(type));

			board.push_back(freeParking);
		}
	}
}