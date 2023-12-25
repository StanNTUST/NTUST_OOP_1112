// File: Player.cpp
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This C++ program define the member functions of class "Player".

#include "Player.h"

// Intent: Default constructor.
// Pre: Input nothing.
// Post: The function returns nothing.
Player::Player() {}

// Intent: Set number of pokemons that player have.
// Pre: Input an int.
// Post: The function returns nothing.
void Player::setNumOfPokemon(int num) { numOfPokemon = num; }

// Intent: Set the opponent of the player.
// Pre: Input a pointer of opponent.
// Post: The function returns nothing.
void Player::setOpponent(Player* opponentPlayer) {
	this->opponentPlayer = opponentPlayer;
}

// Intent: Set the name of the player.
// Pre: Input myPlayer.
// Post: The function returns nothing.
void Player::setPlayerName(myPlayer player) { playerName = player; }

// Intent: Output the imformation.
// Pre: Input nothing.
// Post: The function returns nothing.
void Player::information() {
	cout << "Please input integer to carry your turn" << endl;
	cout << "[0]: Attack" << endl;
	cout << "[1]: Use potion" << endl;
	cout << "[2]: Change pokemon" << endl;
}

// Intent: Output the information of potion.
// Pre: Input nothing.
// Post: The function returns nothing.
void Player::potionInformation() {
	cout << "Please input integer to use the potion" << endl;
	cout << "[0]: Potion" << endl;
	cout << "[1]: Super Potion" << endl;
	cout << "[2]: Hyper Potion" << endl;
	cout << "[3]: Max Potion" << endl;
	cout << "[4]: Back" << endl;
}

// Intent: Add a pokemon to a player.
// Pre: Input a pointer of Pokemon.
// Post: The function returns nothing.
void Player::addPokemon(Pokemon* pokemonName) {
	Pokemon* newPokemon = new Pokemon(
		pokemonName->name,
		pokemonName->hp,
		pokemonName->physicalAttack,
		pokemonName->defense,
		pokemonName->specialAttack,
		pokemonName->specialDefense,
		pokemonName->speed
	);

	for (int i = 0; i < pokemonName->pType.size(); i++) {
		newPokemon->pType.push_back(pokemonName->pType[i]);
	}

	pokemon.push_back(newPokemon);
}