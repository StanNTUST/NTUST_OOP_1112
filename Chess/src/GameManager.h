#pragma once

// File: GameManager.h
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/04
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/04
// Description : This header file declare the class "GameManager" and it's member functions.

#include "definition.h"
#include "Player.h"

class GameManager {
private:
	state gState = Standby;
	Player blackPlayer, whitePlayer;
	int whoseTurn = white;
	vector<string> stepRecord;
	int recordIndex = -1;

	friend class ViewManager;

public:
	// Intent: Initialize game board and players.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	GameManager();

	// Intent: Initialize game board.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void initializeGameBoard();

	// Intent: Change player.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void changePlayer();

	// Intent: Get game state.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string getGameState();

	// Intent: Print game board.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printGameBoard();

	// Intent: Print record.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printRecord();

	// Intent: Get FEN from gBoard.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string getFEN();

	// Intent: Set the game status by FEN.
	// Pre: Input a string representing FEN.
	// Post: The function returns nothing.
	void setFEN(string FEN);

	// Intent: Record the FEN.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void record();

	// Intent: Count the death chessman.
	// Pre: Input FEN.
	// Post: The function returns nothing.
	void deathCount(string FEN);

	// Intent: Undo
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void undo();

	// Intent: Redo
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void redo();

	// Intent: Get system time.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string getTime();

	// Intent: Save file.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void saveFile();

	// Intent: Check if it can castling.
	// Pre: Input nothing.
	// Post: The function returns a string.
	string checkCastling();
};