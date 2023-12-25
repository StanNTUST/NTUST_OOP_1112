/***********************************************************************
 * File: Trigger.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Trigger class (derived class of Item)
***********************************************************************/
#include"Trigger.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Trigger::Trigger() : tExp(10), Item('T') { }

// Intent: Constructor.
// Pre: The variable x and y must have a value.
// Post: The function returns nothing.
Trigger::Trigger(int x, int y) : tExp(10), Item('T',Position(x,y))  { }

Trigger::Trigger(Position pos) :tExp(10), Item('T', pos) {}

// Intent: Copy constructor.
// Pre: The variable ref must have a value.
// Post: The function returns nothing.
Trigger::Trigger(const Trigger& ref) { *this = ref; }

// Intent: To let the hero add exp if the position is the same.
// Pre: The variable hero must have a value.
// Post: The function returns nothing.
bool Trigger::update(Hero& hero) 
{
	if (hero.getPos().x == pos.x && hero.getPos().y == pos.y)
	{
		hero.gainEXP(tExp);
		return true;
	}
	return false;
}

// Intent: To get exp amount.
// Pre: Nothing.
// Post: The function returns exp amount.
int Trigger::getExpAmount() const { return this->tExp; }