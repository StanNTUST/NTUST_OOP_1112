/***********************************************************************
 * File: Creature.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Creature class (base class) 
***********************************************************************/
#pragma once

#include <time.h>
#include "Hero.h"

class Hero;

using namespace std;

class Creature
{
public:
	char icon;
	int hp;
	int power;
	Position position;
	string name;

	// Intent: Default constructor.
	// Pre: Nothing.
	// Post: The function returns nothing.
	Creature();

	// Intent: Constructor.
	// Pre: The variable icon, hp, power and position must have a value.
	// Post: The function returns nothing.
	Creature(char, int, int, Position);

	// Intent: To get icon.
	// Pre: Nothing.
	// Post: The function returns icon.
	char getIcon()const;

	// Intent: To get hp.
	// Pre: Nothing.
	// Post: The function returns hp.
	int getHP()const;

	// Intent: To get power.
	// Pre: Nothing.
	// Post: The function returns power.
	int getPower()const;

	// Intent: To get position.
	// Pre: Nothing.
	// Post: The function returns position.
	Position getPos()const;

	// Intent: To get the name of the creature.
	// Pre: None.
	// Post: The function return the name of the creature.
	string getName()const;

	// Intent: To set icon.
	// Pre: The variable icon must have a value.
	// Post: The function returns nothing.
	void setIcon(char& icon);

	// Intent: To set hp.
	// Pre: The variable hp must have a value.
	// Post: The function returns nothing.
	void setHP(int hp);

	// Intent: To set power.
	// Pre: The variable power must have a value.
	// Post: The function returns nothing.
	void setPower(int power);

	// Intent: To set position.
	// Pre: The variable pos must have a value.
	// Post: The function returns nothing.
	void setPos(Position pos);

	// Intent: To attack or find hero.
	// Pre: The variable hero must have a value.
	// Post: The function returns position.
	virtual void update(Hero& hero);

	// Intent: To minus the creature's hp.
	// Pre: The variable power must have a value.
	// Post: The function returns nothing.
	void damage(int power);

	// Intent: To remove the creature from the board when its dead.
	// Pre: This creature hp is 0.
	// Post: Remove the creature from the board.
	void remove();

	friend class Hero;
};
