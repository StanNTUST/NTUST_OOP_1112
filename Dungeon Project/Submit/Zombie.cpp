/***********************************************************************
 * File: Zombie.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Zombie class (derived class of Creature)
***********************************************************************/
#include "Zombie.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Zombie::Zombie() :Creature('Z', 20, 5, { 1,1 }) 
{
	this->name = "Zombie";
}

// Intent: Constructor.
// Pre: The variable icon, hp, power and position must have a value.
// Post: The function returns nothing.
Zombie::Zombie(char icon, int hp, int power, Position position) : Creature(icon, hp, power, position) 
{
	this->name = "Zombie";
}

// Intent: To attack or find hero.
// Pre: The variable hero must have a value.
// Post: The function returns position.
void Zombie::update(Hero& hero)
{
	Position hPos = hero.getPos();
	Position dir;

	// If find the hero, change the icon and set the message
	if (canSee(this->position, hPos, dir))
	{
		this->icon = '!';
		// Move towards the hero
		Position newPos = this->position;
		newPos.x += dir.x;
		if (isPositionValid(newPos) && dir.x != 0 && newPos != hPos)
		{
			setPos(newPos);
		}
		else
		{
			// Set newPos back to its original value
			newPos.x -= dir.x;	
			newPos.y += dir.y;

			if (isPositionValid(newPos) && dir.y != 0 && newPos != hPos)
			{
				setPos(newPos);
			}

		}
	}
	else
	{
		this->icon = 'Z';

		while (true)
		{
			Position dummy = this->getPos();

			// This rand() will generate a random number from 1 to 4
			// 1 means go up, 2 means go down
			// 3 means go left, 4 means go right
			int num = rand() % 4 + 1;
			// The creature will go up
			if (num == 1)	
			{
				dummy.y -= 1;
			}
			// The creature will go down
			else if (num == 2)	
			{
				dummy.y += 1;
			}
			// The creature will go left
			else if (num == 3)	
			{
				dummy.x -= 1;
			}
			// The creature will go right
			else if (num == 4)	
			{
				dummy.x += 1;
			}

			// Check whether the new position is valid or not
			//	If it is valid then break the loop 
			// and change the creature's position to dummy
			if (isPositionValid(dummy))
			{
				setPos(dummy);
				break;
			}
			// If it is not valid, change the value to the original value
			// And re generate new num
			else
			{
				dummy.y = this->getPos().y;
				dummy.x = this->getPos().x;
				continue;
			}
		}
	}

	// If the hero goes to the creature position, it means it is being attacked
	if (this->position == hero.getPos())
	{
		this->hp = this->hp - hero.getPower();
		if (this->hp <= 0)
		{
			remove();
		}
	}
	// If adjacent to hero, attack hero and drains hero's blood
	else if (isAdjacent(this->position, hero.getPos()))
	{
		hero.damage(power);
		this->hp += 2;
	}
	
}