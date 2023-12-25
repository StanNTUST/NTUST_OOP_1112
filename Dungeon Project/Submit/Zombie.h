/***********************************************************************
 * File: Zombie.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Zombie class (derived class of Creature)
***********************************************************************/
#pragma once

#include "Creature.h"

class Zombie : public Creature
{
public:
    // Intent: Default constructor.
    // Pre: Nothing.
    // Post: The function returns nothing.
    Zombie();

    // Intent: Constructor.
    // Pre: The variable icon, hp, power and position must have a value.
    // Post: The function returns nothing.
    Zombie(char icon, int hp, int power, Position position);

    // Intent: To attack or find hero.
    // Pre: The variable hero must have a value.
    // Post: The function returns position.
    void update(Hero&) override;
};
