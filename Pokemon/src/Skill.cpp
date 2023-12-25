// File: Skill.cpp
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This C++ program define the member functions of class "Skill".

#include "Skill.h"

// Intent: Construct the skill.
// Pre: Input the imformation.
// Post: The function returns nothing.
Skill::Skill(string skillName, type skillType, attackType PS, int power, int accuracy, int PP, Con con) :
	skillName(skillName), skillType(skillType), PS(PS), power(power), accuracy(accuracy), PP(PP), con(con) {}

// Intent: Output the skill.
// Pre: Input nothing.
// Post: The function returns nothing.
void Skill::outputSkill() {
	cout << skillName << " "
		<< typeLibrary[skillType] << " "
		<< ((PS == PHYSICAL) ? "Physical" : "Special") << " "
		<< "power:" << power << " "
		<< "acc:" << accuracy << " "
		<< "con:" << con << " "
		<< "PP:" << PP;

	if (con != NONE) {
		cout << " " << conLib[con] << endl;
	}
	else {
		cout << endl;
	}
}