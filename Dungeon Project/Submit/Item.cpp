/***********************************************************************
 * File: Item.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-25
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Item class (base class) 
***********************************************************************/

#include "Item.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Item::Item()
{
	this->icon = 'I';
	this->pos = { 0,0 };
	this->appearance = 0;
}

// Intent: Constructor.
// Pre: The variable icon have a value.
// Post: The function returns nothing.
Item::Item(char icon) 
{
	this->icon = icon;
	this->appearance = 1;
}

// Intent: Constructor.
// Pre: The variable icon, pos must have a value.
// Post: The function returns nothing.
Item::Item(char icon, Position pos)
{
	this->icon = icon;
	this->pos = pos;
	appearance = 1;
}

// Intent: To get icon.
// Pre: Nothing.
// Post: The function returns icon.
char Item::getIcon()
{
	return this->icon;
}

// Intent: To set position.
// Pre: "Pos" parameter represents the new position of the item.
// Post: The object's pos is updated.
void Item::setPos(const Position& pos)
{
	this->pos = pos;
}

// Intent: To get position.
// Pre: Nothing.
// Post: The function returns position.
Position Item::getPos()
{
	return this->pos;
}

// Intent: To set the appearance of the item.
// Pre: The given int is not null.
// Post: Update the appearance of the item.
void Item::setAppearance(int appearance)
{
	this->appearance = appearance;
}

// Intent: To get appearance.
// Pre: Nothing.
// Post: The function return appearance.
int Item::getAppearance()
{
	return this->appearance;
}

// Intent: Virtual function (may differ according to the derived class needs).
// Pre: "gHero" parameter is not NULL.
// Post: Return true.
bool Item::update(Hero& gHero)
{
	return true;
}

// Intent: To remove the creature from the board when its appearance has reached the maximum number in the current level.
// Pre: None.
// Post: Remove the item from the board.
void Item::remove()
{
	// Set the pos to (0,0) and icon to 'O' so that it will looks like that the object is gone
	setPos({0, 0});
	this->icon = 'O';
}
