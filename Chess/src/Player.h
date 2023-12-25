#pragma once

// File: Player.h
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This header file declare the class "Player" and it's member functions.

#include "definition.h"
#include "Chessman.h"

class Player {
private:
	color pColor;
	bool myTurn;
	bool hasChoose = false;
	bool hasMoved = false;
	vector<Chessman*>	myPieces;
	Chessman* movingPiece = nullptr;
	int deadChessman[numOfType] = { 0 };
	Player* myOpponent;
	static status game;

	friend class ViewManager;
	friend class GameManager;
	friend class Chessman;

public:
	// Default constructor.
	Player() {}

	// Intent: Set color and initialize the player.
	// Pre: Input a color.
	// Post: The function returns nothing.
	void setColor(color playerColor);

	// Intent: Set myOpponent to opponent player.
	// Pre: None.
	// Post: MyOpponent has been set to the opponent pointer.
	void setOpponent(Player* opponentPlayer);

	// Intent: Set all player's the chessman into myPiece vector.
	// Pre: None.
	// Post: Set all player's the chessman into myPiece vector.
	void setMyPieces();

	// Intent: Control the player's status.
	// Pre: None.
	// Post: Set the player status.
	void status();

	// Intent: Check if the chessman at (row, col) is the player's piece.
	// Pre: Input row and column.
	// Post: The function returns a bool.
	bool isMyPiece(int row, int col);

	// Intent: Player want to move.
	// Pre: Input row and column.
	// Post: The function returns a bool that represent if the chessman has eat someone.
	bool wantMove(int row, int col);
};