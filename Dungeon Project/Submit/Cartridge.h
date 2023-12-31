/***********************************************************************
 * File: Cartridge.h
 * Author:	���K�� B11115011
 *			���a�� B11130038
 * Create Date: 2023-06-10
 * Editor:	���K�� B11115011
 *			���a�� B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Cartridge class (derived class of Item)
***********************************************************************/
#pragma once

#include"Item.h"
class Item;

class Cartridge : public Item
{
public:
	// Intent: Constructor.
	// Pre: The parameter variable "pos" has a value.
	// Post: An object with the given "pos" is created.
	Cartridge(Position);

	// Intent: To check whether the position of the hero is the same with the object's position.
	// Pre: "gHero" parameter represents the hero.
	// Post: If the positions are the same, update the hero hp and remove the object from the board.
	bool update(Hero&) override;
};
#include "Item.h"