// File: GameManager.h
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This header file declare the class "GameManager" and it's member functions.

#pragma once

#include"Pokemon.h"
#include"Player.h"
#include"definition.h"
#include"Skill.h"

class GameManager {
private:
	int turnCount = 1;
	string testMode = "";
	string moveLibFileName;
	Player* player1;
	Player* player2;
	vector<Pokemon*> pokemonLibrary;
	vector<Skill*> moveLibrary;
	vector<string> turnMessage;
	gameStatus game;
	string opponent = "";

public:
	// Intent: Default constructor.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	GameManager();

	// Intent: Print turn message
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printTurnMessage();

	// Intent: Attack.
	// Pre: Input attacker and defender and the index of skill.
	// Post: The function returns nothing.
	void attack(Player* attacker, Player* defender, int skillNumber);

	// Intent: Calculate damage.
	// Pre: Input attacker and defender and the index of the skill.
	// Post: The function returns a float.
	float damageCal(Pokemon* attacker, Pokemon* defender, int skillOrder);

	// Intent: Check the type.
	// Pre: Input attack and defence.
	// Post: The function returns a float.
	float typeCheck(int atk, int def);

	// Intent: The pokemon is faint.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void faint();

	// Intent: Set the pokemon library.
	// Pre: Input a string.
	// Post: The function returns nothing.
	void setPokeMonLibrary(string fileName);

	// Intent: Set Game data.
	// Pre: Input a string.
	// Post: The function returns nothing.
	void setGameData(string fileName);

	// Intent: Set moveing library.
	// Pre: Input a string.
	// Post: The function returns nothing.
	void setMoveLibrary(string fileName);

	// Intent: Set command file.
	// Pre: Input a string.
	// Post: The function returns nothing.
	void setCommandFile(string fileName);

	// Intent: Show combat information.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void showCombatImformation();

	// Intent: Combat.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void combat();

	// Intent: Carry one turn.
	// Pre: Input a vector string.
	// Post: The function returns nothing.
	void carryOneTurn(vector<string> cmds);
};
