/***********************************************************************
 * File: Cartridge.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-06-10
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Cartridge class (derived class of Item)
***********************************************************************/

#include "Cartridge.h"

// Intent: Constructor.
// Pre: The parameter variable "pos" has a value.
// Post: An object with the given "pos" is created.
Cartridge::Cartridge(Position pos) : Item('B', pos) {}

// Intent: To check whether the position of the hero is the same with the object's position.
// Pre: "gHero" parameter represents the hero.
// Post: If the positions are the same, update the hero hp and remove the object from the board.
bool Cartridge::update(Hero& gHero)
{
	if (pos == gHero.getPos())	// If the positions are same
	{
		gHero.setBullet(gHero.getBullet() + 3);
		return true;	// Return true
	}
	return false;	// If the position is not the same, return false
}
