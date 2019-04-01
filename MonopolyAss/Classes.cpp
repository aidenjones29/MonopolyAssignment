#include "Classes.h"
#include "LoadFile.h"

//Text output for the penalty tiles.
const string PenaltyName[6]{ "Pay food bill. Player loses ", "Pay phone bill. Player loses ", "Pay heating bill. Player loses ", "Pay vehicle tax. Player loses ", "Pay fuel bill. Player loses ", "Pay windfall tax. Player loses " };
//Text output for the bonus tiles.
const string BonusNames[6]{ "Find some money. Player gains ", "Win competition. Player gains ", "Tax rebate. Player gains ", "Win lottery. Player gains ", "Bequest. Player gains ", "Birthday. Player gains " };
//money value of bonus and penalty changes.
const int SpecialValues[6]{ 20, 50, 100, 150, 200, 300 };

void CProperty::playerStep(Player& player, board& Board)
{
	if (CProperty::owner != NULL) //checks to make sure property IS owned to charge rent.
	{
		//Gets the board square as a Cproperty to allow for property checks.
		CProperty* temp = new CProperty;
		temp = static_cast<CProperty*>(Board[player->currentSquare].get());

			if (CProperty::owner != player.get()) //Makes sure the player doesnt own the current square.
			{
				if (temp->mortgaged != true)
				{
					//Changes the rent from the player to the owner of the property.
					player->balance -= CProperty::rent;
					CProperty::owner->balance += CProperty::rent;
					cout << player->PlayerName << " pays " << POUND << CProperty::rent << endl;
				}
				else //If the property is mortgaged.
				{
					cout << player->PlayerName << " doesnt pay rent due to mortgaging." << endl;
				}
			}
			else //If the current player owns the current square.
			{
				cout << player->PlayerName << " owns " << CProperty::name << endl;
			}
	}
	else //If the tile isnt currently owned.
	{
		if (player->balance > 0) //Checks if the player is able to purchase the property.
		{
			//Takes the cost of the property from the player and sets the player as the owner.
			player->balance -= CProperty::cost;
			CProperty::owner = player.get();
			cout << player->PlayerName << " buys " << CProperty::name << " for " << POUND <<CProperty::cost << endl;

			//Creation of a temp value of the boards property and adds it to the players owned properties vector.
			CProperty* temp = new CProperty;
			temp->cost = CProperty::cost; temp->group = CProperty::group; temp->name = CProperty::name; temp->owner = CProperty::owner; temp->rent = CProperty::rent; temp->numProperties = CProperty::numProperties; temp->mortgaged = CProperty::mortgaged;
			player->ownedProperties.push_back(temp);

			//Sorts the players vector of owned properties based on cost.
			sort(player->ownedProperties.begin(), player->ownedProperties.end(), ComparePrice);
		}
	}
}

void CAirport::playerStep(Player& player, board& Board)
{
	if (CAirport::owner != NULL && CAirport::owner != player.get()) //If property IS owned but not current player
	{
		//Charges the player the service fee and gives it to the owner.
		player->balance -= 10;
		CAirport::owner->balance += 10;
		cout << player->PlayerName << " pays " << POUND << "10 of goods" << endl; 
	}
	else //If the property is unowned.
	{
		if (player->balance > 0) //Checks to see if the player can purchase the tile.
		{
			//Charges the player for the building and sets the owner to the tile.
			player->balance -= 200;
			CAirport::owner = player.get();
			cout << player->PlayerName << " buys " << CAirport::name << " for " << POUND << "200" << endl;
		}
	}
}

void CFreeParking::playerStep(Player& player, board& Board)
{
	cout << player->PlayerName << " is resting" << endl; //If the player lands on the free parking square they just rest.
}

void CJail::playerStep(Player& player, board& Board)
{
	cout << player->PlayerName << " is just visiting" << endl;
}

void CGoToJail::playerStep(Player& player, board& Board)
{
	player->currentSquare = 6; //Sets the player to the current jail square.
	player->balance -= 50;     //Charges the player the #50 to get out of jail.

	cout << player->PlayerName << " goes to jail" << endl;
	cout << player->PlayerName << " pays "<< POUND << "50" << endl;
}

void CGo::playerStep(Player& player, board& Board)
{
	//Nothing happens when the player lands on go.
}

void CBonus::playerStep(Player& player, board& Board)
{
	CBonus::bonus = RandomGen(); //Gets the next seeded random number for a bonus selection.
	CBonus::bonus -= 1;          //Minus' one to account for the array value.

	cout << BonusNames[bonus] << POUND << SpecialValues[bonus] << endl; //Outputs the bonus text and bonus money from the arrays from random.

	player->balance += SpecialValues[bonus]; //Gives the player the bonus.
}

void CPenalty::playerStep(Player& player, board& Board)
{
	CPenalty::penalty = RandomGen(); //Gets the next seeded random number for a penalty selection.
	CPenalty::penalty -= 1; //Minus' one to account for the array value.

	cout << PenaltyName[penalty] << POUND << SpecialValues[penalty] << endl;//Outputs the penalty text and penalty balance in the arrays from random.

	player->balance -= SpecialValues[penalty]; //Gives the player the penalty to its balance.
}

//****************************************************** Main game ******************************************************//
void monopolyManager::playGame()
{
	board Board; //The main games map.

	int seed;             //Place holder for the seed from file.
	int diceRoll = NULL;  //Holder for the random number gen for each roll.
	int tmpRent = 0;      //Rent holder for doubling rent.
	
	bool gameLost = false; //Check for game being lost when a player goes bankrupt.

	//***** Main game characters *****//
	Player dog(new CPlayer);
	Player car(new CPlayer);

	//turn pointer for current turn.
	Player currentPlayersTurn;

	currentPlayersTurn.reset(dog.get());

	//Initial setup of the players classes.
	dog->balance = 1500; dog->currentSquare = 0; dog->PlayerName = "Dog";
	car->balance = 1500; car->currentSquare = 0; car->PlayerName = "Car";

	//***** Functions for loading *****//
	loadFile(seed, Board); //Loads the files for board and seed.
	srand(seed); //sets the seed for the random function.

	cout <<  "Welcome to Monopoly" << endl << "--- Aiden Jones ---" << endl;

	//********** GAME LOOP START **********//

	for (int gameRound = 0; gameRound < NUM_ROUNDS; gameRound++)
	{
		if (gameLost != true) //Checks if any of the players have gone bankrupt.
		{
			cout << endl;
			for (int playerCount = 0; playerCount < NUM_PLAYERS; playerCount++)
			{
				diceRoll = RandomGen(); //Gets the dice roll from the random generator.

				cout << currentPlayersTurn->PlayerName << " rolls " << diceRoll << endl;

				currentPlayersTurn->currentSquare += diceRoll;    //Adds the dice roll to the players square.

				if (currentPlayersTurn->currentSquare >= MAP_SIZE) //Checks if the player has gone past the end of the board.
				{
					currentPlayersTurn->currentSquare -= MAP_SIZE; //Sets the player to the start of the board + how many they went over.
					currentPlayersTurn->balance += 200;           //Gives the player 200 for passing go.
					cout << currentPlayersTurn->PlayerName << " passes GO and collects " << POUND << "200" << endl;
				}

				cout << currentPlayersTurn->PlayerName << " lands on " << Board[currentPlayersTurn->currentSquare]->getName() << endl;

				Board[currentPlayersTurn->currentSquare]->playerStep(currentPlayersTurn, Board); //Calls the polymorfic function of the player step.


				if (Board[currentPlayersTurn->currentSquare]->getType() == 1) //Check to see the current square being a property
				{
					CProperty* temp = new CProperty; //Holds a temp value of the current players square as a Cproperty cast.
					temp = dynamic_cast<CProperty*>(Board[currentPlayersTurn->currentSquare].get());

					if (temp->getOwner() == currentPlayersTurn.get() && temp->streetOwned == false) // Check if the owner is the current player.
					{
						if (temp->numProperties == 2) //Check if its a 2 house street
						{
							//A temp to check behind the player if it is the property.
							CProperty* tempTwo = new CProperty;
							tempTwo = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare - 1].get());

							if (tempTwo->getType() != 1) //Checks if the square behind isnt a property.
							{
								//If the square behind isnt a property then the temp moves infront to get the property details.
								tempTwo = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare + 1].get());
							}
							
							if (tempTwo->getOwner() == temp->getOwner()) //Checks both property squares for owner being the same.
							{
								tmpRent = temp->getRent();    //saves the current rent.
								temp->setRent(tmpRent * 2);   //Doubles the rent of the first property in the street.
								tempTwo->setRent(tmpRent * 2);//Doubles the rent of the second property in the street.
								temp->streetOwned = true;     //Sets the street bool to owned.
								tempTwo->streetOwned = true;  //Sets the street bool to owned.
							}
						}
						else if (temp->numProperties == 3) //If the property is on a 3 property street.
						{
							CProperty* tempInFront = new CProperty; //Holds the square ahead of the player.
							tempInFront = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare + 1].get());

							CProperty* tempBehind = new CProperty;  //Holds the square behind the player.
							tempBehind = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare - 1].get());

							if (tempInFront->getType() != 1) //Checks if the tile infront of the player is not a property.
							{
								tempInFront = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare - 2].get()); //Moves the temp to the back of the street.
							}
							else if (tempBehind->getType() != 1) //Checks if the tile behind the player is not a property.
							{
								tempBehind = static_cast<CProperty*>(Board[currentPlayersTurn->currentSquare + 2].get());  //Moves the temp to the front of the street.
							}

							if (temp->getOwner() == tempInFront->getOwner() && temp->getOwner() == tempBehind->getOwner()) //Compares owners of all three properties.
							{
								tmpRent = temp->getRent();         //saves the current rent.
								temp->setRent(tmpRent * 2);		   //Doubles the rent of the first property in the street.
								tempInFront->setRent(tmpRent * 2); //Doubles the rent of the second property in the street.
								tempBehind->setRent(tmpRent * 2);  //Doubles the rent of the third property in the street.
							}
						}
					}
				}

				mortgage(currentPlayersTurn, gameLost, Board); //Checks for the player being below 0 and then sellsand buys properties accordingly.

				cout << currentPlayersTurn->PlayerName << " has " << POUND << currentPlayersTurn->balance << endl;

				if (gameLost != true) //Check to ensure game isnt lost.
				{
					if (currentPlayersTurn == dog) //Alternates turns between the two players.
					{
						currentPlayersTurn.release();
						currentPlayersTurn.reset(car.get());
					}
					else
					{
						currentPlayersTurn.release();
						currentPlayersTurn.reset(dog.get());
					}
				}
			}
		}
		else //Runs when one of the players lose the game.
		{
			cout << endl << currentPlayersTurn->PlayerName << " lost the game" << endl;
			break;
		}
	}

	currentPlayersTurn.release();
	cout << endl;
	system("Pause");
	//****************************************************** GAME  END ******************************************************//
}



int RandomGen() //Generates a random balue from the seed between 1 - 6
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1); 
}

bool ComparePrice(CProperty*& CostOne, CProperty*& CostTwo) //Sorts the vectors of the players owned properties based on cost.
{
	return CostOne->getCost() < CostTwo->getCost();
}

void mortgage(unique_ptr<CPlayer>& currentPlayer, bool& gameLost, vector<unique_ptr<CBase>>& Board) //Mortgages and buys back properties when required.
{
	while (currentPlayer->balance < 0) //Check the players balance being below 0
	{
		for (int i = 0; i < currentPlayer->ownedProperties.size(); i++) //Runs through the players properties;
		{
			if (currentPlayer->ownedProperties[i]->mortgaged != true) //Checks to make sure the property isnt already mortgaged.
			{
				currentPlayer->ownedProperties[i]->mortgaged = true;
				currentPlayer->balance += currentPlayer->ownedProperties[i]->getCost(); //Adds the value of the property to the players balance.
				cout << currentPlayer->PlayerName << " has mortgaged " << currentPlayer->ownedProperties[i]->getName() << endl;

				for (int j = 0; j < Board.size(); j++) //Search the board against the current mortgaged properties and sets the boards values.
				{
					if (currentPlayer->ownedProperties[i]->getName() == Board[j]->getName())
					{
						CProperty* temp = new CProperty;
						temp = dynamic_cast<CProperty*>(Board[j].get());

						temp->mortgaged = currentPlayer->ownedProperties[i]->mortgaged;//Changes the main boards mortgage values.
					}
				}

				break;
			}
		}

		if (currentPlayer->balance < 0) //Checks if the players balance is still 0 after mortgages and causes game to be lost.
		{
			gameLost = true;
			break;
		}
	}

	for (int i = 0; i < currentPlayer->ownedProperties.size(); i++) //Checks all of the properties the player owns.
	{
		if (currentPlayer->ownedProperties[i]->mortgaged == true) //Checks to make sure the property is mortgaged.
		{
			if (currentPlayer->balance > currentPlayer->ownedProperties[i]->getCost()) //Checks if the players balance is greater than the cost of the property.
			{
				currentPlayer->ownedProperties[i]->mortgaged = false;
				currentPlayer->balance -= currentPlayer->ownedProperties[i]->getCost(); //takes the value of the property from the player.
				cout << currentPlayer->PlayerName << " has rebought " << currentPlayer->ownedProperties[i]->getName() << endl;
			}
		}
	}
}