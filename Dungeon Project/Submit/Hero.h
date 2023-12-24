/***********************************************************************
 * File: Hero.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Hero class
***********************************************************************/
#pragma once

#include <string>
#include <vector>
#include "main.h"
#include "Item.h"
//************************************************************
// Hero Class, only has requirement part for example
//************************************************************
class Hero
{
private:
	Position sPos;		// Hero location
	char sIcon = 'H';	// Hero icon
	int hp;
	int sLevel = 1;     // Level
	int sMaxExp;		// Level update experience
	int sCurrentExp;	// current exp hero has
	int sPower;
	int maxHp;
	int bullet;
public:
	// Intent: Default constructor.
	// Pre: Nothing.
	// Post: The function returns nothing.
	Hero();

	// Intent: Constructor.
	// Pre: The variable x and y must have a value.
	// Post: The function returns nothing.
	Hero(int x, int y);

	// Intent: to set position.
	// Pre: The variable pos must have a value.
	// Post: The function returns nothing.
	void setPos(Position pos);

	// Intent: to set position.
	// Pre: The variable x and y must have a value.
	// Post: The function returns nothing.
	void setPos(int x, int y);

	// Intent: To set icon.
	// Pre: The variable icon must have a value.
	// Post: The function returns nothing.
	void setIcon(char& icon);

	// Intent: To set level.
	// Pre: The variable level must have a value.
	// Post: The function returns nothing.
	void setLevel(int level);

	// Intent: To set exp.
	// Pre: The variable exp must have a value.
	// Post: The function returns nothing.
	void setExp(int exp);

	// Intent: To set maxexp.
	// Pre: The variable maxexp must have a value.
	// Post: The function returns nothing.
	void setMaxExp(int maxexp);

	// Intent: To set hp.
	// Pre: The variable hp must have a value.
	// Post: The function returns nothing.
	void setHP(int hp);

	// Intent: To set power.
	// Pre: The variable power must have a value.
	// Post: The function returns nothing.
	void setPower(int power);

	// Intent: To set the max hp of the hero.
	// Pre: "maxHp" parameter represents this object new maxHp.
	// Post: Update this object max hp.
	void setMaxHp(int maxHp);

	// Intent: To set the amount of bullet possesed by the hero.
	// Pre: "bullet" parameter represents the updated amount of the hero's bullet.
	// Post: Update this object bullet.
	void setBullet(int bullet);

	// Intent: To get position.
	// Pre: Nothing.
	// Post: The function returns position.
	Position getPos(void);

	// Intent: To get icon.
	// Pre: Nothing.
	// Post: The function returns icon.
	char getIcon(void);

	// Intent: To get level.
	// Pre: Nothing.
	// Post: The function returns level.
	int getLevel(void);

	// Intent: To get exp.
	// Pre: Nothing.
	// Post: The function returns exp.
	int getExp(void);

	// Intent: To get maxexp.
	// Pre: Nothing.
	// Post: The function returns maxexp.
	int getMaxExp(void);

	// Intent: To get hp.
	// Pre: Nothing.
	// Post: The function returns hp.
	int getHP();

	// Intent: To get power.
	// Pre: Nothing.
	// Post: The function returns power.
	int getPower();

	// Intent: To get max hp.
	// Pre: Nothing.
	// Post: The function returns max hp.
	int getMaxHp();

	// Intent: To get bullet.
	// Pre: Nothing.
	// Post: The function returns bullet.
	int getBullet();

	// Intent: To move the piece.
	// Pre: The variable delta must have a value.
	// Post: The function returns nothing.
	void move(Position delta);

	// Intent: To gain the exp.
	// Pre: The variable points must have a value.
	// Post: The function returns nothing.
	void gainEXP(int points);

	// Intent: To minus the hero's hp.
	// Pre: The variable points must have a value.
	// Post: The function returns nothing.
	void damage(int points);

	// Intent: To upgrade the level of the hero
	// Pre: The exp of the hero has reached the max amount
	// Post: Upgrade the hero level
	void levelUp();
};