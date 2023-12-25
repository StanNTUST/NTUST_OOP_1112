/***********************************************************************
 * File: HealthPotion.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-25
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define HealthPotion class (derived class of Item)
***********************************************************************/

#include "HealthPotion.h"

// Intent: Constructor.
// Pre: The parameter variable "pos" has a value.
// Post: An object with the given "pos" is created.
HealthPotion::HealthPotion(Position pos) : Item('P', pos) {}

// Intent: To check whether the position of the hero is the same with the object's position.
// Pre: "gHero" parameter represents the hero.
// Post: If the positions are the same, update the hero hp.
bool HealthPotion::update(Hero& gHero)
{
	if (pos == gHero.getPos())	// If the positions are same
	{
		int hMaxHp = gHero.getMaxHp();
		int heroHp = gHero.getHP();
		
		// If the hero hp + 10 does not exceed the max hp, set the new hp to hero hp + 10
		if (heroHp + 10 <= hMaxHp)
		{
			gHero.setHP(heroHp + 10);
		}
		// If the hero hp + 10 exceed the max hp, set the new hp to hero's max hp
		else
		{
			gHero.setHP(hMaxHp);
		}
		return true;	// Return true
	}
	return false;	// If the position is not the same, return false
}
