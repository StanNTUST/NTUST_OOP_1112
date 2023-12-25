#pragma once

// File: definition.h
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This header file including library, declaration, and some definitions.

#include<iostream>
#include<fstream>
#include<cmath>
#include<cctype>
#include<vector>
#include<string>
#include<set>

using namespace std;

// Intent: Split a string with separator and store the words into a string vector.
// Pre: Input a string, a string vector, and a char.
// Post: The function returns nothing.
void split(string& str, vector<string>& splited, char separator);

enum type {
	normal,
	fire,
	water,
	electric,
	grass,
	ice,
	fighting,
	poison,
	ground,
	flying,
	psychic,
	bug,
	rock,
	ghost,
	dragon,
	dark,
	steel,
	fairy,
	numOfType
};

const string typeLibrary[numOfType] = { "Normal","Fire","Water","Electric","Grass","Ice","Fighting","Poison","Ground","Flying","Psychic","Bug","Rock","Ghost","Dragon","Dark","Steel","Fairy" };

const string potionName[4] = { "Potion","SuperPotion","HyperPotion ","MaxPotion" };

const type types[numOfType] = {
	normal,
	fire,
	water,
	electric,
	grass,
	ice,
	fighting,
	poison,
	ground,
	flying,
	psychic,
	bug,
	rock,
	ghost,
	dragon,
	dark,
	steel,
	fairy
};

enum status {
	normalStatus,
	paralysisStatus,
	burnStatus,
	poisonStatus,
	numOfStatus
};

enum gameStatus { carry, player1Win, player2Win };

enum move { battle, potion, swapPokemon };

enum gameType {
	exitGame = -1,
	loadFile,
	commandFile,
	combat
};

enum myPlayer { player1, player2 };

enum attackType { PHYSICAL, SPECIAL };

enum Con { PAR, BRN, PSN, NONE };

const string conLib[NONE] = { "PAR", "BRN", "PSN" };

const Con cons[Con::NONE] = { PAR, BRN, PSN };