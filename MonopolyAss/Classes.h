#pragma once

#include <iostream>

using namespace std;

class CBase
{
public:
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
	string name;
	CPlayer* owner;
	int type;
	int cost;
	int rent;
	int group;
private:
};

class CGo : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CBonus : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CPenalty : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CFreeParking : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CJail : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CGoToJail : public CBase
{
public:
	string name;
	int type;
	void playerStep();
};

class CAirport : public CBase
{
public:
	string name;
	int type;
	void playerStep();
	CPlayer* owner;
	int cost;
	int rent;
};
