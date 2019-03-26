#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Classes.h"
#include "LoadFile.h"

using namespace std;

const int numRounds = 20;
const int numPlayers = 2;
const int mapSize = 26;

enum character {EDogPlayer, ECarPlayer};

int main()
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

	cout << "Welcome to Monopoly \n \n";

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

			cout << currentPlayersTurn->PlayerName << " has " << POUND << currentPlayersTurn->balance <<endl;

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

	system("Pause");
}