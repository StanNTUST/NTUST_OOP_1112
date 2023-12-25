#pragma once

// File: Skill.h
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This header file declare the class "Skill" and it's member functions.

#include "definition.h"

class Skill {
private:
	string skillName;
	type skillType;
	attackType PS;
	int power;
	int accuracy;
	int PP;
	Con con;

	friend class Pokemon;
	friend class Player;
	friend class GameManager;

public:
	// Intent: Construct the skill.
	// Pre: Input the imformation.
	// Post: The function returns nothing.
	Skill(string skillName, type skillType, attackType PS, int power, int accuracy, int PP, Con con);

	// Intent: Get name.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string getName() { return skillName; }

	// Intent: Get type.
	// Pre: Input nothing.
	// Post: The function returns type.
	type getType() { return skillType; }

	// Intent: Get PS.
	// Pre: Input nothing.
	// Post: The function returns attackType.
	attackType getPS() { return PS; }

	// Intent: Get power.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getPower() { return power; }

	// Intent: Get accuracy.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getAcc() { return accuracy; }

	// Intent: Get PP.
	// Pre: Input nothing.
	// Post: The function returns an int.
	int getPP() { return PP; }

	// Intent: Get con.
	// Pre: Input nothing.
	// Post: The function returns Con.
	Con getCon() { return con; }

	// Intent: Output the skill.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void outputSkill();
};