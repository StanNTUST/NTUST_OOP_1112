/***********************************************************************
 * File: Position.h
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare Position class
***********************************************************************/
#pragma once

#include<iostream>

class Position
{
public:
	int x, y;
	Position();
	Position(int, int);

	// Intent: To get x.
	// Pre: Nothing.
	// Post: The function returns x position.
	int getX()const;

	// Intent: To get y.
	// Pre: Nothing.
	// Post: The function returns y position.
	int getY()const;

	// Intent: To get x.
	// Pre: The variable x must have a value.
	// Post: The function returns nothing.
	void setX(int x);

	// Intent: To get x.
	// Pre: The variable y must have a value.
	// Post: The function returns nothing.
	void setY(int y);

	// Intent: operator to let position is equal to position.
	// Pre: The Position pos must have a value.
	// Post: The function returns the new position.
	Position& operator=(const Position& position);

	// Intent: operator to let position add position.
	// Pre: The Position pos must have a value.
	// Post: The function returns the new position.
	Position operator+(const Position& pos) const;

	// Intent: operator to let position add position and equal to the new position.
	// Pre: The Position pos must have a value.
	// Post: The function nothing.
	void operator+=(const Position& pos);

	// Intent: operator to let position minus position.
	// Pre: The Position pos must have a value.
	// Post: The function returns the new position.
	Position operator-(const Position& pos) const;

	// Intent: operator to let position minus position and equal to the new position.
	// Pre: The Position pos must have a value.
	// Post: The function returns nothing.
	void operator-=(const Position& pos);

	// Intent: operator to let position product number.
	// Pre: The variable number must have a value.
	// Post: The function returns the new position.
	Position operator*(int scale) const;

	// Intent: operator to let judge if the position is the same.
	// Pre: The Position rhs must have a value.
	// Post: The function returns true if the position is the same or return false if not.
	bool operator==(const Position& rhs) const;

	// Intent: operator to let judge if the position is not the same.
	// Pre: The Position rhs must have a value.
	// Post: The function returns true if the position is not the same or return false if is the same.
	bool operator!=(const Position& rhs) const;

	// Intent: Operator to set the form of input the position.
	// Pre: The istream strm and Position position must have a value.
	// Post: The function returns istream strm.
	friend std::ostream& operator<<(std::ostream& oStream, const Position& pos);

	// Intent: Operator to set the form of output the position.
	// Pre: The ostream strm and Position position must have a value.
	// Post: The function returns ostream strm.
	friend std::istream& operator>>(std::istream& iStream, Position& pos);
};
