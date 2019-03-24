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

int RandomGen();
//void loadFile(int& seed, vector<CBase*>& board);

int main()
{

	vector<CBase*> Board;

	int seed;
	int diceRoll = NULL;

	CPlayer* dog(new CPlayer);
	CPlayer* car(new CPlayer);

	CPlayer* currentPlayersTurn = dog;

	dog->balance = 1500; dog->currentSquare = 0; dog->type = "Dog";
	car->balance = 1500; car->currentSquare = 0; car->type = "Car";

	loadFile(seed, Board);
	srand(seed);

	cout << "Welcome to Monopoly \n \n";

	for (int gameRound = 0; gameRound <= numRounds; gameRound++)
	{
		for (int playerCount = 0; playerCount < numPlayers; playerCount++)
		{
			diceRoll = RandomGen();

			cout << currentPlayersTurn->type << " rolls " << diceRoll << endl;

			currentPlayersTurn->currentSquare += diceRoll;

			if (currentPlayersTurn->currentSquare >= mapSize)
			{
				currentPlayersTurn->currentSquare -= mapSize;
			}

			cout << currentPlayersTurn->type << " lands on " << Board[currentPlayersTurn->currentSquare]->name << endl;

			Board[currentPlayersTurn->currentSquare]->playerStep(currentPlayersTurn);

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

int RandomGen()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
