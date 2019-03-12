#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Classes.h"
#include "LoadFile.h"

using namespace std;

enum character {DogPlayer, CarPlayer};

void loadFile(int& seed, vector<CBase*>& board);

int main()
{

	vector<CBase*> Board;
	int seed;

	CPlayer* dog(new CPlayer);
	CPlayer* car(new CPlayer);

	loadFile(seed, Board);
	srand(seed);

	int randomNumber[10];

	system("Pause");
}

int RandomGen()
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * 6.0f + 1);
}
