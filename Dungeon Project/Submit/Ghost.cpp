/***********************************************************************
 * File: Ghost.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Ghost class (derived class of Creature)
***********************************************************************/

#include "Ghost.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Ghost::Ghost() : Creature('G', 10, 10, { 1,1 }) 
{
	this->name = "Ghost";
}

// Intent: Constructor.
// Pre: The variable icon, hp, power and position must have a value.
// Post: The function returns nothing.
Ghost::Ghost(char icon, int hp, int power, Position position) : Creature(icon, hp, power, position) 
{
	this->name = "Ghost";
}

// Intent: To attack or find hero.
// Pre: The variable hero must have a value.
// Post: The function returns position.
void Ghost::update(Hero& hero)
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
			newPos.x -= dir.x;	// Set newPos back to its original value
			newPos.y += dir.y;
			if (isPositionValid(newPos) && dir.y != 0 && newPos != hPos)
			{
				setPos(newPos);
			}

		}
	}
	else
	{
		this->icon = 'G';
		while (true)
		{
			Position dummy = this->position;
			// This rand() will generate a random number from 1 to 20
			// 5 means teleport, other number, move randomly
			int num = rand() % 20 + 1;

			if (num == 5)
			{
				while (true)
				{
					Position boardSize = getBoardSize();
					Position newPos;
					newPos.x = rand() % (boardSize.x - 1);
					newPos.y = rand() & (boardSize.y - 1);

					if (isPositionValid(newPos))
					{
						setPos(newPos);
						break;
					}
				}
			}

			else
			{
				// Generates new number from 1 to 4
				// 1 means go up, 2 means go down
				// 3 means go left, 4 means go right
				num = rand() % 4 + 1;
				if (num == 1)	// The creature will go up
				{
					dummy.y -= 1;
				}

				else if (num == 2)	// The creature will go down
				{
					dummy.y += 1;
				}

				else if (num == 3)	// The creature will go left
				{
					dummy.x -= 1;
				}

				else if (num == 4)	// The creature will go right
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
					dummy = this->position;
				}
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
	// If adjacent to hero, attack hero
	else if (isAdjacent(this->position, hero.getPos()))
	{
		hero.damage(power);
	}

}