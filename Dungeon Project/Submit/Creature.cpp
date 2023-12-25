/***********************************************************************
 * File: Creature.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Creature class (base class) 
***********************************************************************/
#include "Creature.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Creature::Creature() { }

// Intent: Constructor.
// Pre: The variable icon, hp, power and position must have a value.
// Post: The function returns nothing.
Creature::Creature(char icon, int hp, int power, Position position)
{
	this->icon = icon;
	this->hp = hp;
	this->power = power;
	this->position = position;
}

// Intent: To get icon.
// Pre: Nothing.
// Post: The function returns icon.
char Creature::getIcon(void) const { return this->icon; }

// Intent: To get hp.
// Pre: Nothing.
// Post: The function returns hp.
int Creature::getHP() const { return this->hp; }

// Intent: To get power.
// Pre: Nothing.
// Post: The function returns power.
int Creature::getPower() const { return this->power; }

// Intent: To get position.
// Pre: Nothing.
// Post: The function returns position.
Position Creature::getPos() const { return position; }

// Intent: To get the name of the creature.
// Pre: None.
// Post: The function return the name of the creature.
string Creature::getName() const { return name; }

// Intent: To set icon.
// Pre: The variable icon must have a value.
// Post: The function returns nothing.
void Creature::setIcon(char& icon) { this->icon = icon; }

// Intent: To set hp.
// Pre: The variable hp must have a value.
// Post: The function returns nothing.
void Creature::setHP(int hp) { this->hp = hp; }

// Intent: To set power.
// Pre: The variable power must have a value.
// Post: The function returns nothing.
void Creature::setPower(int power) { this->power = power; }

// Intent: to set position.
// Pre: The variable pos must have a value.
// Post: The function returns nothing.
void Creature::setPos(Position pos) { this->position = pos; }

// Intent: To attack or find hero.
// Pre: The variable hero must have a value.
// Post: The function returns position.
void Creature::update(Hero& hero) {
	Position hPos = hero.getPos();

	Position dir;

	//if find the hero, change the icon and set the message
	if (canSee(this->position, hPos, dir)) {
		std::cout << "Creature has find the Hero in the ( " << dir.x << ", " << dir.y << " ) direction\n";
		this->icon = '!';
	}
	else {
		std::cout << "Creature didn't find the Hero\n";
		this->icon = 'C';
	}

	// If meet hero, attack hero
	if (!(hPos != position)) {
		hero.damage(power);
	}
}

// Intent: To minus the creature's hp.
// Pre: The variable power must have a value.
// Post: The function returns nothing.
void Creature::damage(int power){

}

// Intent: To remove the creature from the board when its dead.
// Pre: This creature hp is 0.
// Post: Remove the creature from the board.
void Creature::remove()
{
	// Set the pos to (0,0) and icon to 'O' so that it will looks like that the object is gone
	setPos({ 0, 0 });
	this->icon = 'O';
	this->hp = 0;
}
