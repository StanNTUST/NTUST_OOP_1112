/***********************************************************************
 * File: Position.cpp
 * Author:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Create Date: 2023-05-19
 * Editor:	³¯¥K¿³ B11115011
 *			¤ý®a§» B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program define Position class
***********************************************************************/
#include "Position.h"

// Intent: Default constructor.
// Pre: Nothing.
// Post: The function returns nothing.
Position::Position() :x(0), y(0)
{
}

// Intent: Constructor.
// Pre: The variable x and y must have a value.
// Post: The function returns nothing.
Position::Position(int x, int y)
{
	this->x = x;
	this->y = y;
}


// Intent: To get x.
// Pre: Nothing.
// Post: The function returns x position.
int Position::getX()const { return x; }

// Intent: To get y.
// Pre: Nothing.
// Post: The function returns y position.
int Position::getY()const { return y; }

// Intent: To get x.
// Pre: The variable x must have a value.
// Post: The function returns nothing.
void Position::setX(int x) { this->x = x; }

// Intent: To get x.
// Pre: The variable y must have a value.
// Post: The function returns nothing.
void Position::setY(int y) { this->y = y; }

// Intent: operator to let position is equal to position.
// Pre: The Position pos must have a value.
// Post: The function returns the new position.
Position& Position:: operator=(const Position& position) {
	this->x = position.x;
	this->y = position.y;
	return *this;
}

// Intent: operator to let position add position.
// Pre: The Position pos must have a value.
// Post: The function returns the new position.
Position Position::operator+(const Position& pos) const {
	//create new position
	Position newPos;

	//position add position
	newPos.x = x + pos.x;
	newPos.y = y + pos.y;

	//return new position
	return newPos;
}

// Intent: operator to let position add position and equal to the new position.
// Pre: The Position pos must have a value.
// Post: The function nothing.
void Position::operator+=(const Position& pos) {
	//position add new position
	x = x + pos.x;
	y = y + pos.y;
}

// Intent: operator to let position minus position.
// Pre: The Position pos must have a value.
// Post: The function returns the new position.
Position Position::operator-(const Position& pos) const {
	//create new position
	Position newPos;

	//position minus position
	newPos.x = x - pos.x;
	newPos.y = y - pos.y;

	//return new position
	return newPos;
}

// Intent: operator to let position minus position and equal to the new position.
// Pre: The Position pos must have a value.
// Post: The function returns nothing.
void Position::operator-=(const Position& pos) {
	//position minus position
	x = x - pos.x;
	y = y - pos.y;
}

// Intent: operator to let position product number.
// Pre: The variable number must have a value.
// Post: The function returns the new position.
Position Position::operator*(int scale) const {
	return Position(x * scale, y * scale);
}

// Intent: operator to let judge if the position is the same.
// Pre: The Position rhs must have a value.
// Post: The function returns true if the position is the same or return false if not.
bool Position::operator==(const Position& rhs) const {
	//return true if the position is the same or return false if not
	return (x == rhs.x && y == rhs.y);
}

// Intent: operator to let judge if the position is not the same.
// Pre: The Position rhs must have a value.
// Post: The function returns true if the position is not the same or return false if is the same.
bool Position::operator!=(const Position& rhs) const {
	//return true if the position is not the same or return false if is the same
	return (x != rhs.x || y != rhs.y);
}

// Intent: Operator to set the form of input the position.
// Pre: The istream strm and Position position must have a value.
// Post: The function returns istream strm.
std::ostream& operator<<(std::ostream& oStream, const Position& pos) {
	return oStream << pos.x << " " << pos.y;
}

// Intent: Operator to set the form of output the position.
// Pre: The ostream strm and Position position must have a value.
// Post: The function returns ostream strm.
std::istream& operator>>(std::istream& iStream, Position& pos) {
	return iStream >> pos.x >> pos.y;
}
