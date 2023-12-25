/***********************************************************************
 * File: Sword.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-25
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Sword class (derived class of Item)
***********************************************************************/
#pragma once
#include "Item.h"
class Item;

class Sword : public Item
{
public:
	// Intent: Constructor.
	// Pre: The parameter variable "pos" has a value.
	// Post: An object with the given "pos" is created.
	Sword(Position);

	// Intent: To check whether the position of the hero is the same with the object's position.
	// Pre: "gHero" parameter represents the hero.
	// Post: If the positions are the same, update the hero attack.
	bool update(Hero&) override;
};
