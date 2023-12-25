#pragma once

// File: Chessman.h
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/04
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/04
// Description : This header file declare the class "Chessman" and it's member functions.

#include "definition.h"
#include "Player.h"

class Chessman {
private:
	color sColor;
	type sType;
	int rowPos;
	int colPos;
	bool validDestinations[ROW][COL];
	bool pieceHasMoved = false;
	Player** opponentPlayer;
	Player* currentPlayer;
	bool danger[ROW][COL];
	bool isEnPassant = false;

	friend class ViewManager;
	friend class GameManager;
	friend class Player;

public:
	// Intent: Contruct the chessman.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	Chessman();

	// Intent: Set up the chessman
	// Pre: Input color, type, row, column, opponent player, and current player.
	// Post: The function returns nothing.
	Chessman(color chessmanColor, type chessmanType, int row, int col, Player** chessmanOpponent, Player* chessmanCurrent);

	// Intent: Initialize the board of valid destinations.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void initValidDestination();

	// Intent: Initialize the board of danger.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void initDanger();

	// Intent: Check if the position is valid, is blank, is mine, or is opponent.
	// Pre: Input a coordinate and a feature that want to check.
	// Post: The function returns a bool.
	bool check(int row, int col, feature f);

	// Intent: This function is used to find valid destinition for queen, bishop, and rook in specific direction.
	// Pre: Input a direction and a bool.
	// Post: The function returns nothing.
	void movingRule(direction d, bool currPlayerMoving);

	// Intent: This function is used to find valid destinition for knight and king.
	// Pre: Input a coordinate and a bool.
	// Post: The function returns nothing.
	void open(int row, int col, bool currPlayerMoving);

	// Intent: let the chessman do a virtual move to make sure the slot is safe.
	// Pre: Input a coordinate.
	// Post: The function returns nothing, but checked the slot is safe or not.
	void virtualMove(int row, int col);

	// Intent: Find valid destination and fill bool into validDestinations.
	// Pre: Input a bool.
	// Post: The function returns nothing.
	void findValidDestination(bool currPlayerMoving);

	// Intent: Move the chessman.
	// Pre: Input the destination's position.
	// Post: The function returns a bool that represent if the chessman has eat someone.
	bool move(int destRow, int destCol);

	// Intent: find a danger space of an opponent chessman.
	// Pre: Input a coordinate.
	// Post: set the danger place
	void findDangerPlace(int row = -1, int col = -1);

	// Intent: Check if the king is in danger.
	// Pre: Input nothing.
	// Post: Return whether king is in danger or not.
	bool kingDanger();

	// Intent: Check if the destination is danger.
	// Pre: Input the destination's position.
	// Post: The function returns a bool.
	bool isDanger(int destRow, int destCol);
};
