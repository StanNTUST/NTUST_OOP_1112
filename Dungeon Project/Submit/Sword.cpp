/***********************************************************************
 * File: Sword.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-25
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Sword class (derived class of Item)
***********************************************************************/

#include "Sword.h"

// Intent: Constructor.
// Pre: The parameter variable "pos" has a value.
// Post: An object with the given "pos" is created.
Sword::Sword(Position pos) : Item('S', pos) {}

// Intent: To check whether the position of the hero is the same with the object's position.
// Pre: "gHero" parameter represents the hero.
// Post: If the positions are the same, update the hero attack.
bool Sword::update(Hero& gHero)
{
	// If the hero position is the same with the object position, give the hero 5 power and return true
	if (pos == gHero.getPos())
	{
		gHero.setPower(gHero.getPower() + 5);
		return true;
	}
	// If the position is not the same with the hero positon, return false
	return false;
}
