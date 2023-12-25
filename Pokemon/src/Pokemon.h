// File: Pokemong
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This header file declare the class "Pokemon" and it's member functions.

#pragma once

#include"definition.h"
#include "Skill.h"

class Pokemon {
private:
	string name;
	int maxHp;
	int hp;
	int physicalAttack;
	int defense;
	int specialAttack;
	int specialDefense;
	int speed;
	int level = 50;
	int accuacy = 100;
	vector<int> pType;
	vector<Skill*> skill;
	set<string> pStatus;
	friend class Player;
	friend class GameManager;

public:
	// Intent: Default constructor.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	Pokemon();

	// Intent: Constructor.
	// Pre: Input pokemon's imformation.
	// Post: The function returns nothing.
	Pokemon(string name, int hp, int physicalAttack, int defense, int specialAttack, int specialDefense, int speed);

	// Intent: Increase hp.
	// Pre: Input an int.
	// Post: The function returns nothing.
	void changeHp(float num) {
		this->hp += int(num);
	}

	// Intent: Set hp.
	// Pre: Input an int.
	// Post: The function returns nothing.
	void setHp(int num) {
		this->hp = num;
	}

	// Intent: Get name.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string getName() { return name; }

	// Intent: Get maxHp.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getMaxHp() { return maxHp; }

	// Intent: Get hp.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getHp() { return hp; }

	// Intent: Get physicalAttack.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getPhysicalAttack() { return physicalAttack; }

	// Intent: Get defense.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getDefense() { return defense; }

	// Intent: Get specialAttack.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getSpecialAttack() { return specialAttack; }

	// Intent: Get specialDefense.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getSpecialDefense() { return specialDefense; }

	// Intent: Get speed.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getSpeed() { return speed; }

	// Intent: Get level.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getLevel() { return level; }

	// Intent: Get accuacy.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getAccuracy() { return accuacy; }

	// Intent: Get type.
	// Pre: Input nothing.
	// Post: The function returns a vector int.
	vector<int> getType() { return pType; }

	// Intent: Get status.
	// Pre: Input nothing.
	// Post: The function returns status.
	set<string> getStatus() { return pStatus; }

	// Intent: Get skill.
	// Pre: Input nothing.
	// Post: The function returns a pointer vector of Skill.
	vector<Skill*> getSkill() { return skill; }

	int getSkillSize() { return skill.size(); }

	// Intent: Add type to the pokemon.
	// Pre: Input type name.
	// Post: The function returns nothing.
	void addType(vector<string> typeName);

	// Intent: Add skill to the pokemon.
	// Pre: Input a Skill.
	// Post: The function returns nothing.
	void addSkill(Skill* skillName);
};
