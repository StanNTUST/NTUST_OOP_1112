/***********************************************************************
 * File: Trigger.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Trigger class (derived class of Item)
***********************************************************************/

#pragma once

#include <string>
#include <iostream>
#include "Hero.h"

class Hero;
//************************************************************
// Trigger Class
//************************************************************
class Trigger:public Item
{
private:
	int tExp;
public:
	// Intent: Default constructor.
	// Pre: Nothing.
	// Post: The function returns nothing.
	Trigger();

	// Intent: Constructor.
	// Pre: The variable x and y must have a value.
	// Post: The function returns nothing.
	Trigger(int x, int y);

	Trigger(Position pos);

	// Intent: Copy constructor.
	// Pre: The variable ref must have a value.
	// Post: The function returns nothing.
	Trigger(const Trigger& ref);

	// Intent: To let the hero add exp if the position is the same.
	// Pre: The variable hero must have a value.
	// Post: The function returns nothing.
	bool update(Hero& hero) override;

	// Intent: To get exp amount.
	// Pre: Nothing.
	// Post: The function returns exp amount.
	int getExpAmount() const;
};

