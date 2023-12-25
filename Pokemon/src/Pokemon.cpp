// File: Pokemon.cpp
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This C++ program define the member functions of class "Pokemon".

#include"Pokemon.h"

// Intent: Constructor.
// Pre: Input pokemon's imformation.
// Post: The function returns nothing.
Pokemon::Pokemon(string name, int hp, int physicalAttack, int defense, int specialAttack, int specialDefense, int speed) :
	name(name),
	maxHp(hp),
	hp(hp),
	physicalAttack(physicalAttack),
	defense(defense),
	specialAttack(specialAttack),
	specialDefense(specialDefense),
	speed(speed)
{}

// Intent: Add type to the pokemon.
// Pre: Input type name.
// Post: The function returns nothing.
void Pokemon::addType(vector<string> typeName) {
	for (int i = 0; i < typeName.size(); i++) {
		// Find type name in the type library.
		for (int j = 0; j <= 18; j++) {
			if (typeName[i] == typeLibrary[j]) {
				pType.push_back(j);
				break;
			}
		}
	}
}

// Intent: Add skill to the pokemon.
// Pre: Input a Skill.
// Post: The function returns nothing.
void Pokemon::addSkill(Skill* skillName) {
	Skill* newSkill = new Skill(
		skillName->skillName,
		skillName->skillType,
		skillName->PS,
		skillName->power,
		skillName->accuracy,
		skillName->PP,
		skillName->con);

	skill.push_back(newSkill);
}
