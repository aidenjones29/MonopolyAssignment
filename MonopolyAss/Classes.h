#pragma once
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include "LoadFile.h"

using namespace std;

const char POUND = 156;
const int numRounds = 20;
const int numPlayers = 2;
const int mapSize = 26;

enum character { EDogPlayer, ECarPlayer };

class CPlayer
{
public:
	string PlayerName;
	vector<CProperty*> ownedProperties;
	int currentSquare;
	int balance;
};

class CBase
{
public:
	virtual ~CBase() {};
	virtual void playerStep(CPlayer* player) = 0;

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
	void playerStep(CPlayer* player);

	CPlayer* getOwner() { return owner; }
	int getCost() { return cost; }
	int getRent() { return rent; }
	int getGroup() { return group; }

	void setOwner(CPlayer* newOwner) { owner = newOwner; }
	void setCost(int newCost) { cost = newCost; }
	void setRent(int newRent) { rent = newRent; }
	void setGroup(int newGroup) { group = newGroup; }

protected:
	CPlayer* owner;
	int cost;
	int rent;
	int group;
};

class CGo : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CBonus : public CBase
{
public:
	int bonus;
	void playerStep(CPlayer* player);
};

class CPenalty : public CBase
{
public:
	int penalty;
	void playerStep(CPlayer* player);
};

class CFreeParking : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CJail : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CGoToJail : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CAirport : public CBase
{
public:
	void playerStep(CPlayer* player);

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

class CMonopolyManager
{
	void startGame();
};

int RandomGen();