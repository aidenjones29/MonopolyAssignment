#include "Classes.h"

string PenaltyName[6]{ "Pay food bill. Player loses ", "Pay phone bill. Player loses ", "Pay heating bill. Player loses ", "Pay vehicle tax. Player loses ", "Pay fuel bill. Player loses ", "Pay windfall tax. Player loses " };
string BonusNames[6]{ "Find some money. Player gains ", "Win competition. Player gains ", "Tax rebate. Player gains ", "Win lottery. Player gains ", "Bequest. Player gains ", "Birthday. Player gains "};
int SpecialValues[6]{ 20, 50, 100, 150, 200, 300 };

void CProperty::playerStep(CPlayer* player)
{
	if (CProperty::owner != NULL) //If property IS owned but not current player
	{
		if (CProperty::owner != player)
		{
			player->balance -= CProperty::rent;
			CProperty::owner->balance += CProperty::rent;
			cout << player->PlayerName << " pays " << POUND << CProperty::rent << endl;
		}
		else
		{
			cout << player->PlayerName << " owns " << CProperty::name << endl;
		}
	}
	else
	{
		if (player->balance > 0)
		{
			player->balance -= CProperty::cost;
			CProperty::owner = player;
			cout << player->PlayerName << " buys " << CProperty::name << " for " << POUND <<CProperty::cost << endl;

			CProperty temp = new CProperty;
			temp.cost = CProperty::cost; temp.group = CProperty::group; temp.name = CProperty::name; temp.owner = CProperty::owner; temp.rent = CProperty::rent;

			player->ownedProperties.push_back(temp);
		}
	}
}

void CAirport::playerStep(CPlayer* player)
{
	if (CAirport::owner != NULL && CAirport::owner != player) //If property IS owned but not current player
	{
		player->balance -= 10;
		CAirport::owner->balance += 10;
		cout << player->PlayerName << " pays " << POUND << "10 of goods" << endl; 
	}
	else
	{
		if (player->balance > 0)
		{
			player->balance -= 200;
			CAirport::owner = player;
			cout << player->PlayerName << " buys " << CAirport::name << " for " << POUND << "200" << endl;
		}
	}
}

void CFreeParking::playerStep(CPlayer* player)
{
	cout << player->PlayerName << " is resting" << endl;
}

void CJail::playerStep(CPlayer* player)
{
	cout << player->PlayerName << " is just visiting" << endl;
}

void CGoToJail::playerStep(CPlayer* player)
{
	player->currentSquare = 6;
	player->balance -= 50;

	cout << player->PlayerName << " goes to jail" << endl;
	cout << player->PlayerName << " pays "<< POUND << "50" << endl;
}

void CGo::playerStep(CPlayer* player)
{
	
}

void CBonus::playerStep(CPlayer* player)
{
	CBonus::bonus = RandomGen();
	CBonus::bonus -= 1;

	cout << BonusNames[bonus] << POUND << SpecialValues[bonus] << endl;

	player->balance += SpecialValues[bonus];
}

void CPenalty::playerStep(CPlayer* player)
{
	CPenalty::penalty = RandomGen();
	CPenalty::penalty -= 1;

	cout << PenaltyName[penalty] << POUND << SpecialValues[penalty] << endl;

	player->balance -= SpecialValues[penalty];
}

void CMonopolyManager::startGame()
{
	vector<CBase*> Board;
	CPlayer* car(new CPlayer);
	CPlayer* dog(new CPlayer);
	CPlayer* currentPlayersTurn = dog;

	dog->balance = 1500; dog->currentSquare = 0; dog->PlayerName = "Dog";
	car->balance = 1500; car->currentSquare = 0; car->PlayerName = "Car";

	int seed;
	int diceRoll = NULL;

	loadFile(seed, Board);
	srand(seed);

	cout << "Welcome to Monopoly \n" << "By Aiden Jones" << endl;

	for (int gameRound = 0; gameRound < numRounds; gameRound++)
	{
		cout << endl;
		for (int playerCount = 0; playerCount < numPlayers; playerCount++)
		{
			diceRoll = RandomGen();

			cout << currentPlayersTurn->PlayerName << " rolls " << diceRoll << endl;

			currentPlayersTurn->currentSquare += diceRoll;

			if (currentPlayersTurn->currentSquare >= mapSize)
			{
				currentPlayersTurn->currentSquare -= mapSize;
				currentPlayersTurn->balance += 200;
				cout << currentPlayersTurn->PlayerName << " passes GO and collects " << POUND << "200" << endl;
			}

			cout << currentPlayersTurn->PlayerName << " lands on " << Board[currentPlayersTurn->currentSquare]->getName() << endl;

			Board[currentPlayersTurn->currentSquare]->playerStep(currentPlayersTurn);

			cout << currentPlayersTurn->PlayerName << " has " << POUND << currentPlayersTurn->balance << endl;

			if (currentPlayersTurn == dog)
			{
				currentPlayersTurn = car;
			}
			else
			{
				currentPlayersTurn = dog;
			}
		}
	}
}


int RandomGen()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
