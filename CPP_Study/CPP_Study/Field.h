#pragma once

class GPlayer;
class Monster;

class Field
{
public:
	Field();
	~Field();

	void Update(GPlayer* player);
	void CreateMonster();
	void StartBattle(GPlayer* player);

private:
	Monster* _monster;
};

