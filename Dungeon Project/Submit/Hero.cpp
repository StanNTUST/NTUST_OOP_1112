/***********************************************************************
 * File: Hero.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Hero class
***********************************************************************/
#include"Hero.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Hero::Hero()
{
	this->sPos.x = 0;
	this->sPos.y = 0;
	this->sLevel = 1;
	this->sCurrentExp = 0;
	this->sMaxExp = 15;
	this->sIcon = 'H';
	this->hp = 50;
	this->sPower = 5;
	this->maxHp = 50;
	this->bullet = 5;
}

// Intent: Constructor.
// Pre: The variable x and y must have a value.
// Post: The function returns nothing.
Hero::Hero(int x, int y) 
{
	this->sPos.x = x;
	this->sPos.y = y;
	this->sLevel = 1;
	this->sCurrentExp = 0;
	this->sMaxExp = 15;
	this->sIcon = 'H';
	this->hp = 50;
	this->sPower = 5;
	this->maxHp = 50;
	this->bullet = 5;
}

// Intent: to set position.
// Pre: The variable pos must have a value.
// Post: The function returns nothing.
void Hero::setPos(Position pos) { this->sPos = pos; }

// Intent: to set position.
// Pre: The variable x and y must have a value.
// Post: The function returns nothing.
void Hero::setPos(int x, int y) 
{
	this->sPos.x = x;
	this->sPos.y = y;
}

// Intent: To set icon.
// Pre: The variable icon must have a value.
// Post: The function returns nothing.
void Hero::setIcon(char& icon) { this->sIcon = icon; }

// Intent: To set level.
// Pre: The variable level must have a value.
// Post: The function returns nothing.
void Hero::setLevel(int level) { this->sLevel = level; }

// Intent: To set exp.
// Pre: The variable exp must have a value.
// Post: The function returns nothing.
void Hero::setExp(int exp) { this->sCurrentExp = exp; }

// Intent: To set maxexp.
// Pre: The variable maxexp must have a value.
// Post: The function returns nothing.
void Hero::setMaxExp(int maxexp) { this->sMaxExp = maxexp; }

// Intent: To set hp.
// Pre: The variable hp must have a value.
// Post: The function returns nothing.
void Hero::setHP(int hp) { this->hp = hp; }

// Intent: To set power.
// Pre: The variable power must have a value.
// Post: The function returns nothing.
void Hero::setPower(int power) { this->sPower = power; }

// Intent: To set the max hp of the hero.
// Pre: "maxHp" parameter represents this object new maxHp.
// Post: Update this object max hp.
void Hero::setMaxHp(int maxHp) { this->maxHp = maxHp; }

// Intent: To set the amount of bullet possesed by the hero.
// Pre: "bullet" parameter represents the updated amount of the hero's bullet.
// Post: Update this object bullet.
void Hero::setBullet(int bullet) { this->bullet = bullet; }

// Intent: To get position.
// Pre: Nothing.
// Post: The function returns position.
Position Hero::getPos(void) { return this->sPos; }

// Intent: To get icon.
// Pre: Nothing.
// Post: The function returns icon.
char Hero::getIcon(void) { return this->sIcon; }

// Intent: To get level.
// Pre: Nothing.
// Post: The function returns level.
int Hero::getLevel(void) { return this->sLevel; }

// Intent: To get exp.
// Pre: Nothing.
// Post: The function returns exp.
int Hero::getExp(void) { return this->sCurrentExp; }

// Intent: To get maxexp.
// Pre: Nothing.
// Post: The function returns maxexp.
int Hero::getMaxExp(void) { return this->sMaxExp; }

// Intent: To get hp.
// Pre: Nothing.
// Post: The function returns hp.
int Hero::getHP() { return this->hp; }

// Intent: To get power.
// Pre: Nothing.
// Post: The function returns power.
int Hero::getPower() { return this->sPower; }

// Intent: To get max hp.
// Pre: Nothing.
// Post: The function returns max hp.
int Hero::getMaxHp() { return this->maxHp; }

// Intent: To get bullet.
// Pre: Nothing.
// Post: The function returns bullet.
int Hero::getBullet() { return this->bullet; }

// Intent: To move the piece.
// Pre: The variable delta must have a value.
// Post: The function returns nothing.
void Hero::move(Position delta)
{
	// Compute the next position
	Position next = this->sPos + delta;

	// If position is valid, move the piece
	if (isPositionValid(next)) this->sPos = next;
	// Else output error
	else
	{
		std::cout << "Invalid location\n";
	}
}

// Intent: To gain the exp.
// Pre: The variable points must have a value.
// Post: The function returns nothing.
void Hero::gainEXP(int points)
{
	int number = points;

	while (number > 0)
	{
		// If number can level up, up the level and set new maxexp and level
		if (sCurrentExp + number >= sMaxExp)
		{
			number -= (sMaxExp - sCurrentExp);
			sCurrentExp = 0;
			sMaxExp = (int)((float)sMaxExp * 1.2f);
			levelUp();
		}

		// Else current exp add points
		else
		{
			sCurrentExp += number;
			number = 0;
		}
	}
}

// Intent: To minus the hero's hp.
// Pre: The variable points must have a value.
// Post: The function returns nothing.
void Hero::damage(int points)
{
	// Hp minus points
	hp = hp - points;

	// If hp is less than 0, hp is 0 
	if (hp < 0) hp = 0;
}

// Intent: To upgrade the level of the hero
// Pre: The exp of the hero has reached the max amount
// Post: Upgrade the hero level
void Hero::levelUp()
{
	// Increment the player level and add it max by 50
	sLevel++;
	maxHp += 50;
	
	// Give the hero 50 hp bonus but if it's exceed the maxHp set the new hp to maxHp
	if (hp + 50 > maxHp)
	{
		hp = maxHp;
	}
	else
	{
		hp += 50;
	}
}
