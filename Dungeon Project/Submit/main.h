/***********************************************************************
 * File: main.h
 * Author:	陳仕興 B11115011
 *			王家宏 B11130038
 * Create Date: 2023-05-19
 * Editor:	陳仕興 B11115011
 *			王家宏 B11130038
 * Update Date: 2023-06-11
 * Description: This C++ program declare the function
***********************************************************************/

#include <iostream>
#include <math.h>		// pow() and sqrt()
#include <ctime>		// for time loop function
#include <conio.h>		// _getch() <= to read input without enter "ENTER" key
#include <algorithm>	// for max and min function
#include <vector>
#include <fstream>
#include "Position.h"

// Intent: Check whether the location is a valid one i.e. not a wall
// Pre: 'loc' parameter represents the given position to check
// Position: If 'loc' is a valid position return true, vice versa
bool isPositionValid(Position& loc);

// Intent: clip algroithm
// Pre: The given float are not NULL
// Post: Return the biggest float between minimum and min(maximum, n)
float clip(float n, float minimun, float maximum);

// Intent: Check whether two position is close enough，利用 call-by-referce 將計算得到的方向回傳
// Pre: 'cPos' represent the creature position, 'hPos' represent the hero position, 'dir' represents the direction
// Post: If the creature can see the hero, return true, vice versa
bool canSee(Position cPos, Position hPos, Position& dir);

// Intent: To get the board size for the other classes such as creatures classes and it derived classes
// Pre: None
// Post: Return the board size in a Position type
Position getBoardSize();

// Intent: To know whether a zombie is adjacent to the hero or not
// Pre: None
// Post: If the creature is adjacent to the hero return true, vice versa
bool isAdjacent(Position cPos, Position hPos);
