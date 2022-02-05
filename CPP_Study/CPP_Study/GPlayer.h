#pragma once
#include "Creature.h"

enum PlayerType
{
	PT_Knight = 1,
	PT_Archer = 2,
	PT_Mage = 3,
};

class GPlayer : public Creature
{
public:
	GPlayer(int playerType) : Creature(CT_PLAYER), _playerType(playerType)
	{

	}
	virtual ~GPlayer()
	{

	}

	virtual void PrintInfo();

protected:
	int _playerType;
};

class GKnight : public GPlayer
{
public:
	GKnight() : GPlayer(PT_Knight)
	{
		_hp = 150;
		_attack = 10;
		_defence = 5;
	}
};

class GArcher : public GPlayer
{
public:
	GArcher() : GPlayer(PT_Archer)
	{
		_hp = 80;
		_attack = 15;
		_defence = 3;
	}
};

class GMage : public GPlayer
{
public:
	GMage() : GPlayer(PT_Mage)
	{
		_hp = 50;
		_attack = 25;
		_defence = 0;
	}
};

