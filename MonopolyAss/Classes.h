#pragma once

#include <iostream>

using namespace std;

class CPlayer
{
public:
	int balance;
	string type;
	int currentSquare;
};

class CBase
{
public:
	string name;
	int type;

	virtual ~CBase() {};
	virtual void playerStep(CPlayer* player) = 0;
};

class CProperty : public CBase
{
public:
	void playerStep(CPlayer* player);
	CPlayer* owner;
	int cost;
	int rent;
	int group;
private:
};

class CGo : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CBonus : public CBase
{
public:
	void playerStep(CPlayer* player);
};

class CPenalty : public CBase
{
public:
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
	CPlayer* owner;
	int cost;
	int rent;
};
