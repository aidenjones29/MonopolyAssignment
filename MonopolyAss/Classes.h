#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>

using namespace std;

const char POUND = 156;
const int numRounds = 20;
const int numPlayers = 2;
const int mapSize = 26;

enum character { EDogPlayer, ECarPlayer };

class CProperty;

class CPlayer
{
public:
	string PlayerName;
	vector<CProperty*> ownedProperties;
	int numMortgagedProperties;
	int currentSquare;
	int balance;
};

class CBase
{
public:
	virtual ~CBase() {};
	virtual void playerStep(CPlayer* player, vector<CBase*>& Board) = 0;

	string getName() { return name; }
	int getType() { return type; }

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
	bool mortgaged;
	int numProperties;
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

int RandomGen();

void mortgage(CPlayer*& currentPlayer, bool& gameLost, vector<CBase*>& Board);

bool ComparePrice(CProperty*& lhs, CProperty*& rhs);