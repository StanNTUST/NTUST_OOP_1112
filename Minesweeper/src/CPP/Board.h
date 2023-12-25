#pragma once

// File: Board.h
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005, B11130038
// Update Date : 2023/04/12
// Description : This header file declare the class "Board" and it's member functions.
// All the global value and preprocessor like #include or #define are also in this header file.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// External global values
extern ifstream iFile;
extern ofstream oFile;
extern int ioMode;

// Record IO mode.
enum mode {
	fileIO, commandIO, GUI
};

// Check if use file IO, if yes, using fstream to IO, if not, using iostream to IO.
#define IN ((ioMode == fileIO) ? iFile : cin)
#define OUT ((ioMode == fileIO) ? oFile : cout)

// Check if the coordinate is valid.
#define IS_VALID(i,j) (( 0<=(i) && (i)<row && 0<=(j) && (j)<col ) ? true : false)

// Define the max and min width of the board.
#define MAX_WIDTH 100
#define MIN_WIDTH 1

// Define the icons.
#define BOMB 'X'
#define BLANK '#'
#define FLAG 'f'
#define QUESTION_MARK '?'

// Game state
enum state {
	Standby,
	Playing,
	GameOver
};

class Board
{
private:
	char map[MAX_WIDTH][MAX_WIDTH] = { 0 };
	char mapAns[MAX_WIDTH][MAX_WIDTH] = { 0 };
	int row = 0;
	int col = 0;
	int BombCount = 0;
	int FlagCount = 0;
	int OpenBlankCount = 0;
	int RemainBlankCount = 0;

public:
	state state = Standby;
	bool hasLoad = false;

	// Default constructor
	Board() {}

	// Deconstructor
	~Board() {}

	// Intent: Print specified information.
	// Pre: Input a string.
	// Post: The function returns nothing.
	void print(string& cmd);

	// Intent: Load the board.
	// Pre: Input a string vector of cmds.
	// Post: The function returns nothing.
	void loadBoard(vector<string>& cmds);

	// Intent: LeftClick.
	// Pre: Input a coordinate.
	// Post: The function returns nothing.
	void leftClick(int row, int col);

	// Intent: When function leftClick is called, diffuse if it can.
	// Pre: Input a coordinate that represents the origin of the diffusion.
	// Post: The function returns nothing.
	void diffuse(int row, int col);

	// Intent: rightClick.
	// Pre: Input a coordinate.
	// Post: The function returns nothing.
	void rightClick(int row, int col);
};