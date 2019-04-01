#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <deque>
#include <algorithm>
#include <memory>

using namespace std;


const char POUND = 156; //Pound char for output text
const int NUM_ROUNDS = 20;
const int NUM_PLAYERS = 2;
const int MAP_SIZE = 26;

enum character { EDogPlayer, ECarPlayer };

class CProperty; //Forwards decleration for use in CPlayer class.
class CBase;
class CPlayer;

typedef vector<unique_ptr<CBase>> board;
typedef unique_ptr<CPlayer> Player;

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
	virtual void playerStep(Player& player, board& Board) = 0;

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
	void playerStep(Player& player, board& Board);

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
	void playerStep(Player& player, board& Board);
};

class CBonus : public CBase
{
public:
	int bonus;
	void playerStep(Player& player, board& Board);
};

class CPenalty : public CBase
{
public:
	int penalty;
	void playerStep(Player& player, board& Board);
};

class CFreeParking : public CBase
{
public:
	void playerStep(Player& player, board& Board);
};

class CJail : public CBase
{
public:
	void playerStep(Player& player, board& Board);
};

class CGoToJail : public CBase
{
public:
	void playerStep(Player& player, board& Board);
};

class CAirport : public CBase
{
public:
	void playerStep(Player& player, board& Board);

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

void mortgage(unique_ptr<CPlayer>& currentPlayer, bool& gameLost, board& Board); //Checks the players mortgages and checks if the player can rebuy.

bool ComparePrice(CProperty*& lhs, CProperty*& rhs); //Sorting the owned property vector for each player.
