#pragma once

// File: definition.h
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This header file include all definitions.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <Windows.h>

using namespace std;

class ViewManager;
class GameManager;
class Player;
class Chessman;

#define ROW 8
#define COL 8

// Game state
enum state { Standby, Playing, GameOver };

// Victory judgment
enum status { carry, draw, blackWin, whiteWin, blackSurrender, whiteSurrender };

// Color
enum color { black, white };

// Chessman type
enum type { king, queen, bishop, knight, rook, pawn, numOfType };

// Coordinate feature
enum feature { valid, blank, mine, opponent };

// Directions
enum direction { Up, Down, Left, Right, UpLeft, UpRight, DownLeft, DownRight };

// Icon Style
enum iconStyle { normal, special };

// A structure ti record promote imformations
struct promoteRecord {
	int promoteIndex;
	color promoteColor;
	type promoteType;
};

#define BLANK '0'

const char BLACK_SYMBOL[numOfType] = { 'k','q','b','n','r','p' };
const char WHITE_SYMBOL[numOfType] = { 'K','Q','B','N','R','P' };

#define MAIN_WINDOW_ICON "./images/Chess.ico"

#define STATUS_BAR_ICON "./images/Chess.png"

// Normal whose turn image path
#define NORMAL_BLACK_TURN_IMAGE "./images/blackTurn.png"
#define NORMAL_WHITE_TURN_IMAGE "./images/whiteTurn.png"

// Special whose turn image path
#define SPECIAL_BLACK_TURN_IMAGE "./images/specialBlackTurn.png"
#define SPECIAL_WHITE_TURN_IMAGE "./images/specialWhiteTurn.png"

// Main music path
#define MAIN_MUSIC "./sounds/dodge.wav"

// Ridicule video path
#define RIDICULE_VIDEO "./sounds/ridicule.wmv"

// Game over sound effect path
#define HOTPOT_SOUND_EFFECT "./sounds/hotpot.wav"

// Sound effect sound path
const string soundEffect[8] = {
	"./sounds/OpenCell.wav",
	"",
	"./sounds/cat.wav",
	"./sounds/Baby.wav",
	"./sounds/Sneezing.wav",
	"./sounds/fast.wav",
	"./sounds/scream.wav",
	"./sounds/baganono.wav"
};

// Normal icon image path
const string NORMAL_BLACK_ICON[numOfType] = {
	"./images/bKing.png",
	"./images/bQueen.png",
	"./images/bBishop.png",
	"./images/bKnight.png",
	"./images/bRook.png",
	"./images/bPawn.png"
};
const string NORMAL_WHITE_ICON[numOfType] = {
	"./images/wKing.png",
	"./images/wQueen.png",
	"./images/wBishop.png",
	"./images/wKnight.png",
	"./images/wRook.png",
	"./images/wPawn.png"
};

// Special icon image path
const string SPECIAL_BLACK_ICON[numOfType] = {
	"./images/specialBlackKing.png",
	"./images/specialBlackQueen.png",
	"./images/specialBlackBishop.png",
	"./images/specialBlackKnight.png",
	"./images/specialBlackRook.png",
	"./images/specialBlackPawn.png"
};
const string SPECIAL_WHITE_ICON[numOfType] = {
	"./images/specialWhiteKing.png",
	"./images/specialWhiteQueen.png",
	"./images/specialWhiteBishop.png",
	"./images/specialWhiteKnight.png",
	"./images/specialWhiteRook.png",
	"./images/specialWhitePawn.png"
};