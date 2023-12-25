// File: Player.h
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This header file declare the class "Player" and it's member functions.

#pragma once

#include"definition.h"
#include "Pokemon.h"

class Player {
private:
	int numOfPokemon;
	vector<Pokemon*> pokemon;
	Pokemon* currentPokemon;
	Player* opponentPlayer;
	myPlayer playerName;
	
	friend class GameManager;

public:
	// Intent: Default constructor.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	Player();

	// Intent: Set number of pokemons that player have.
	// Pre: Input an int.
	// Post: The function returns nothing.
	void setNumOfPokemon(int num);

	// Intent: Set the opponent of the player.
	// Pre: Input a pointer of opponent.
	// Post: The function returns nothing.
	void setOpponent(Player* opponentPlayer);

	// Intent: Set the name of the player.
	// Pre: Input myPlayer.
	// Post: The function returns nothing.
	void setPlayerName(myPlayer player);

	// Intent: Add a pokemon to a player.
	// Pre: Input a pointer of Pokemon.
	// Post: The function returns nothing.
	void addPokemon(Pokemon* pokemonName);

	// Intent: Output the imformation.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void information();

	// Intent: Output the information of potion.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void potionInformation();
};
