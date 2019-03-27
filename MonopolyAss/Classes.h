#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>

using namespace std;

const char POUND = 156; //Pound char for output text
const int numRounds = 200;
const int numPlayers = 2;
const int mapSize = 26;

enum character { EDogPlayer, ECarPlayer };

class CProperty; //Forwards decleration for use in CPlayer class.

class CPlayer //The game piece class.
{
public:
	string PlayerName;
	vector<CProperty*> ownedProperties; //Vector of properties in order of cost for mortgaging.
	int currentSquare; //Current board square.
	int balance; //Main wallet balance for the player.
};

class CBase //The main base for classes on the games map/board.
{
public:
	virtual ~CBase() {};
	virtual void playerStep(CPlayer* player, vector<CBase*>& Board) = 0;

	string getName() { return name; } //Gets the name of the tile.
	int getType() { return type; } //Gets the int value of tile type.

	void setName(string newName) { name = newName; }
	void setType(int newType) { type = newType; }

protected:
	string name;
	int type;

};

class CProperty : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);

	CPlayer* getOwner() { return owner; }
	int getCost() { return cost; }
	int getRent() { return rent; }
	int getGroup() { return group; }

	void setOwner(CPlayer* newOwner) { owner = newOwner; }
	void setCost(int newCost) { cost = newCost; }
	void setRent(int newRent) { rent = newRent; }
	void setGroup(int newGroup) { group = newGroup; }

	bool streetOwned;
	bool mortgaged; //Bool to check if the property is mortgaged.
	int numProperties; //Properties in the street for 2/3 house streets.
protected:
	CPlayer* owner;
	int cost;
	int rent;
	int group;
};

class CGo : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CBonus : public CBase
{
public:
	int bonus;
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CPenalty : public CBase
{
public:
	int penalty;
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CFreeParking : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CJail : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CGoToJail : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);
};

class CAirport : public CBase
{
public:
	void playerStep(CPlayer* player, vector<CBase*>& Board);

	CPlayer* getOwner() { return owner; }
	int getCost() { return cost; }
	int getRent() { return rent; }

	void setOwner(CPlayer* newOwner) { owner = newOwner; }
	void setCost(int newCost) { cost = newCost; }
	void setRent(int newRent) { rent = newRent; }

protected:
	CPlayer* owner;
	int cost = 200;
	int rent = 10;
};

class monopolyManager
{
public:
	void playGame();
};

int RandomGen(); //seeded random number generator.

void mortgage(CPlayer*& currentPlayer, bool& gameLost, vector<CBase*>& Board); //Checks the players mortgages and checks if the player can rebuy.

bool ComparePrice(CProperty*& lhs, CProperty*& rhs); //Sorting the owned property vector for each player.