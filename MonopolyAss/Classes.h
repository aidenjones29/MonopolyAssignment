#pragma once

#include <iostream>

using namespace std;

class CBase
{
public:
	string name;
	int type;

	virtual ~CBase() {};
	virtual void playerStep() = 0;
};

class CPlayer
{
private:
	int balance;
	string type;
	int currentSquare;
};

class CProperty : public CBase
{
public:
	void playerStep();
	CPlayer* owner;
	int cost;
	int rent;
	int group;
private:
};

class CGo : public CBase
{
public:
	void playerStep();
};

class CBonus : public CBase
{
public:
	void playerStep();
};

class CPenalty : public CBase
{
public:
	void playerStep();
};

class CFreeParking : public CBase
{
public:
	void playerStep();
};

class CJail : public CBase
{
public:
	void playerStep();
};

class CGoToJail : public CBase
{
public:
	void playerStep();
};

class CAirport : public CBase
{
public:
	void playerStep();
	CPlayer* owner;
	int cost;
	int rent;
};
