#pragma once
#include "linkedlist.h"
#include "Monster.h"

class Player
{
private:
	Lista<Monster> defeatedMonsters;
	std::string Name;
	std::string Race;
	int HP;
	int MP;
public:
	Player(const std::string& playerName, const std::string& playerRace) : Name(playerName), Race(playerRace), MP(100), HP(100) {}

	bool newDefeatedMonster(Monster& defeated)
	{
		return defeatedMonsters.insertarInicio(defeated);
	}


	void showDefeatedMonsters() {
		defeatedMonsters.printMonsterName();
	}
};

