/***********************************************************************
 * File: Ghost.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Ghost class (derived class of Creature)
***********************************************************************/
#pragma once

#include "Creature.h"

class Ghost : public Creature
{
public:
    // Intent: Default constructor.
    // Pre: Nothing.
    // Post: The function returns nothing.
    Ghost();

    // Intent: Constructor.
    // Pre: The variable icon, hp, power and position must have a value.
    // Post: The function returns nothing.
    Ghost(char, int, int, Position);

    // Intent: To attack or find hero.
    // Pre: The variable hero must have a value.
    // Post: The function returns position.
    void update(Hero&) override;
};
