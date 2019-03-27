#include "LoadFile.h"
#include "Classes.h"

void loadFile(int& seed, vector<CBase*>& board) //File loading function for the seed and main game map.
{
	ifstream SeedFile("seed.txt");

	SeedFile >> seed; //Gets the line from the seedfile which is just the number of the seed.

	ifstream infile("Monopoly.txt");

	for (int i = 0; i < 26; i++) //Runs to the size of the board
	{
		string type = "";	 
		string fullName = "";  
		string Cost = "";	
		string Rent = "";	   
		string group = "";	   
		string secondName = "";

		getline(infile, type, ' '); //Gets the first char of the file which is the type.

		//*************** Property loading ***************//
		if (stoi(type) == 1) 
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName, ' ');
			getline(infile, secondName, ' ');
			getline(infile, Cost, ' ');
			getline(infile, Rent, ' ');
			getline(infile, group);
			
			//Creates a temp of the current type and sets their respected class variables.
			CProperty* property(new CProperty);
			property->setName(fullName + " " + secondName);
			property->setCost(stoi(Cost));
			property->setType(stoi(type));
			property->setRent(stoi(Rent));
			property->setGroup(stoi(group));
			property->streetOwned = false;
			property->numProperties = 2;
			property->mortgaged = false;

			if (stoi(Rent) == 45 || stoi(Rent) == 25) //Checks for the streets with the specific values to check for 3 property streets.
			{
				property->numProperties = 3;
			}

			board.push_back(property); //Pushes back the tile on the board vector.
		}
		//*************** Go tile loading ***************//
		else if (stoi(type) == 2)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CGo* go(new CGo);
			go->setName(fullName);
			go->setType(stoi(type));

			board.push_back(go); //Pushes back the tile on the board vector.
		}
		//*************** airport loading ***************//
		else if (stoi(type) == 3)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName, ' ');
			getline(infile, secondName);

			//Creates a temp of the current type and sets their respected class variables.
			CAirport* airport(new CAirport);
			airport->setName(fullName + " " + secondName);
			airport->setType(stoi(type));

			board.push_back(airport); //Pushes back the tile on the board vector.
		}
		//*************** bonus loading ***************//
		else if (stoi(type) == 4)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CBonus* Bonus(new CBonus);
			Bonus->setName(fullName);
			Bonus->setType(stoi(type));

			board.push_back(Bonus); //Pushes back the tile on the board vector.
		}
		//*************** penalty loading ***************//
		else if (stoi(type) == 5)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CPenalty* Penalty(new CPenalty);
			Penalty->setName(fullName);
			Penalty->setType(stoi(type));

			board.push_back(Penalty); //Pushes back the tile on the board vector.
		}
		//*************** jail loading ***************//
		else if (stoi(type) == 6)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CJail* Jail(new CJail);
			Jail->setName(fullName);
			Jail->setType(stoi(type));

			board.push_back(Jail); //Pushes back the tile on the board vector.
		}
		//*************** goJail loading ***************//
		else if (stoi(type) == 7)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CGoToJail* goToJail(new CGoToJail);
			goToJail->setName(fullName);
			goToJail->setType(stoi(type));

			board.push_back(goToJail); //Pushes back the tile on the board vector.
		}
		//*************** parking loading ***************//
		else if (stoi(type) == 8)
		{
			//gets the rest of the line and stores them in their respected variables.
			getline(infile, fullName);

			//Creates a temp of the current type and sets their respected class variables.
			CFreeParking* freeParking(new CFreeParking);
			freeParking->setName(fullName);
			freeParking->setType(stoi(type));

			board.push_back(freeParking); //Pushes back the tile on the board vector.
		}
	}
}