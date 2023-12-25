/***********************************************************************
 * File: Item.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-25
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Item class (base class)
***********************************************************************/
#pragma once
#include "Position.h"

class Hero;

class Item
{
protected:
	char icon;
	Position pos;
	int appearance;
public:
	// Intent: Default constructor.
	// Pre: Nothing.
	// Post: The function returns nothing.
	Item();

	// Intent: Constructor.
	// Pre: The variable icon have a value.
	// Post: The function returns nothing.
	Item(char);

	// Intent: Constructor.
	// Pre: The variable icon, pos have a value.
	// Post: The function returns nothing.
	Item(char, Position);

	// Intent: To get icon.
	// Pre: Nothing.
	// Post: The function returns icon.
	char getIcon();

	// Intent: To set position.
	// Pre: "Pos" parameter represents the new position of the item.
	// Post: The object's pos is updated.
	void setPos(const Position& pos);

	// Intent: To get position.
	// Pre: Nothing.
	// Post: The function returns position.
	Position getPos();
	
	// Intent: To set the appearance of the item.
	// Pre: The given int is not null.
	// Post: Update the appearance of the item.
	void setAppearance(int);

	// Intent: To get appearance.
	// Pre: Nothing.
	// Post: The function return appearance.
	int getAppearance();

	// Intent: Virtual function (may differ according to the derived class needs).
	// Pre: "gHero" parameter is not NULL.
	// Post: Return true.
	virtual bool update(Hero& gHero);

	// Intent: To remove the creature from the board when its appearance has reached the maximum number in the current level.
	// Pre: None.
	// Post: Remove the item from the board.
	void remove();
};
#include "Hero.h"
