// File: Board.cpp
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005, B11130038
// Update Date : 2023/04/12
// Description : This C++ program define the member functions of class "Board".

#include "Board.h"

// Intent: Print specified information.
// Pre: Input a string.
// Post: The function returns nothing.
void Board::print(string& cmd) {
	// If cmd is GameBoard and the board has load, print out the game board.
	if (cmd == "GameBoard" && hasLoad) {
		// New line
		OUT << endl;
		// Print out the game board.
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				OUT << map[i][j] << " ";
			}
			OUT << endl;
		}
	}

	// If cmd is GameState, print out the state.
	else if (cmd == "GameState") {
		if (state == Standby) { OUT << "Standby\n"; }
		if (state == Playing) { OUT << "Playing\n"; }
		if (state == GameOver) { OUT << "GameOver\n"; }
	}

	// If cmd is GameAnswer, print out game answer.
	else if (cmd == "GameAnswer" && hasLoad) {
		// New line
		OUT << endl;
		// Print out game answer
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				OUT << mapAns[i][j] << " ";
			}
			OUT << endl;
		}
	}

	// If cmd are those value, print out the value.
	else if (cmd == "BombCount" && state != Standby) {
		OUT << BombCount << endl;
	}
	else if (cmd == "FlagCount" && state != Standby) {
		OUT << FlagCount << endl;
	}
	else if (cmd == "OpenBlankCount" && state != Standby) {
		OUT << OpenBlankCount << endl;
	}
	else if (cmd == "RemainBlankCount" && state != Standby) {
		OUT << RemainBlankCount << endl;
	}

	// If nothing can be print, just print out a new line to conforms to the format.
	else { OUT << endl; }
}

// Intent: Load the board.
// Pre: Input a string vector of cmds.
// Post: The function returns nothing.
void Board::loadBoard(vector<string>& cmds) {
	// Use a bool to record whether the loading is success.
	bool success = false;

	// If the load mode is BoardFile.
	if (cmds.size() == 3 && cmds[1] == "BoardFile") {
		// Open the file.
		ifstream file;
		file.open(cmds[2]);

		// If fail to open, the loading is not success.
		success = !file.fail();

		// If success to open the file.
		if (success) {
			// File input row and col.
			file >> row >> col;

			// Check if row and col are valid.
			success = (MIN_WIDTH <= row && row <= MAX_WIDTH && MIN_WIDTH <= col && col <= MAX_WIDTH);

			if (success) {
				// Load the board.
				for (int i = 0; i < row; i++) {
					string rows;
					file >> rows;
					for (int j = 0; j < col; j++) {
						// If the coordinate is not bomb, fill in 0.
						if (rows[j] != BOMB) {
							mapAns[i][j] = '0';
						}
						// Otherwise, fill in the icon of bomb and increase BombCount.
						else if (rows[j] == BOMB) {
							mapAns[i][j] = BOMB;
							BombCount++;
						}
					}
				}
				// If the coordinate is bomb, increase the number of surrounding coordinate.
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						if (mapAns[i][j] == BOMB) {
							if (IS_VALID(i - 1, j - 1) && mapAns[i - 1][j - 1] != BOMB) { mapAns[i - 1][j - 1]++; }
							if (IS_VALID(i - 1, j/**/) && mapAns[i - 1][j/**/] != BOMB) { mapAns[i - 1][j/**/]++; }
							if (IS_VALID(i - 1, j + 1) && mapAns[i - 1][j + 1] != BOMB) { mapAns[i - 1][j + 1]++; }
							if (IS_VALID(i/**/, j - 1) && mapAns[i/**/][j - 1] != BOMB) { mapAns[i/**/][j - 1]++; }
							if (IS_VALID(i/**/, j + 1) && mapAns[i/**/][j + 1] != BOMB) { mapAns[i/**/][j + 1]++; }
							if (IS_VALID(i + 1, j - 1) && mapAns[i + 1][j - 1] != BOMB) { mapAns[i + 1][j - 1]++; }
							if (IS_VALID(i + 1, j/**/) && mapAns[i + 1][j/**/] != BOMB) { mapAns[i + 1][j/**/]++; }
							if (IS_VALID(i + 1, j + 1) && mapAns[i + 1][j + 1] != BOMB) { mapAns[i + 1][j + 1]++; }
						}
					}
				}
			}
		}

		// Close the file.
		file.close();
	}

	// If the load mode is RandomCount.
	else if (cmds.size() == 5 && cmds[1] == "RandomCount") {
		// Input row and col.
		row = stoi(cmds[2]);
		col = stoi(cmds[3]);
		// Input the number of bombs.
		int upperBound = stoi(cmds[4]);

		// Check if row and col are valid.
		success = (MIN_WIDTH <= row && row <= MAX_WIDTH && MIN_WIDTH <= col && col <= MAX_WIDTH);
		// Check if the upper bound is valid.
		success = success && (0 <= upperBound && upperBound <= row * col);

		if (success) {

			// Set a seed.
			srand(time(NULL));

			// Fill the board with 0.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					mapAns[i][j] = '0';
				}
			}
			// Fill in the bomb.
			while (BombCount != upperBound) {
				int randRow = rand() % row, randCol = rand() % col;
				if (mapAns[randRow][randCol] != BOMB) {
					mapAns[randRow][randCol] = BOMB;
					BombCount++;
				}
			}
			// If the coordinate is bomb, increase the number of surrounding coordinate.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (mapAns[i][j] == BOMB) {
						if (IS_VALID(i - 1, j - 1) && mapAns[i - 1][j - 1] != BOMB) { mapAns[i - 1][j - 1]++; }
						if (IS_VALID(i - 1, j/**/) && mapAns[i - 1][j/**/] != BOMB) { mapAns[i - 1][j/**/]++; }
						if (IS_VALID(i - 1, j + 1) && mapAns[i - 1][j + 1] != BOMB) { mapAns[i - 1][j + 1]++; }
						if (IS_VALID(i/**/, j - 1) && mapAns[i/**/][j - 1] != BOMB) { mapAns[i/**/][j - 1]++; }
						if (IS_VALID(i/**/, j + 1) && mapAns[i/**/][j + 1] != BOMB) { mapAns[i/**/][j + 1]++; }
						if (IS_VALID(i + 1, j - 1) && mapAns[i + 1][j - 1] != BOMB) { mapAns[i + 1][j - 1]++; }
						if (IS_VALID(i + 1, j/**/) && mapAns[i + 1][j/**/] != BOMB) { mapAns[i + 1][j/**/]++; }
						if (IS_VALID(i + 1, j + 1) && mapAns[i + 1][j + 1] != BOMB) { mapAns[i + 1][j + 1]++; }
					}
				}
			}
		}
	}

	// If the load mode is RandomRate.
	else if (cmds.size() == 5 && cmds[1] == "RandomRate") {
		// Input row and col.
		row = stoi(cmds[2]);
		col = stoi(cmds[3]);
		// Input the probability.
		double probability = stod(cmds[4]);

		// Check if row and col are valid.
		success = (MIN_WIDTH <= row && row <= MAX_WIDTH && MIN_WIDTH <= col && col <= MAX_WIDTH);
		// Check if probability is valid.
		success = success && (0 <= probability && probability <= 1);

		if (success) {

			// Set a seed.
			srand(time(NULL));

			probability *= 100;

			// Fill int the bomb.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (probability > rand() % 100) {
						mapAns[i][j] = BOMB;
						BombCount++;
					}
					else {
						mapAns[i][j] = '0';
					}
				}
			}
			// If the coordinate is bomb, increase the number of surrounding coordinate.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (mapAns[i][j] == BOMB) {
						if (IS_VALID(i - 1, j - 1) && mapAns[i - 1][j - 1] != BOMB) { mapAns[i - 1][j - 1]++; }
						if (IS_VALID(i - 1, j/**/) && mapAns[i - 1][j/**/] != BOMB) { mapAns[i - 1][j/**/]++; }
						if (IS_VALID(i - 1, j + 1) && mapAns[i - 1][j + 1] != BOMB) { mapAns[i - 1][j + 1]++; }
						if (IS_VALID(i/**/, j - 1) && mapAns[i/**/][j - 1] != BOMB) { mapAns[i/**/][j - 1]++; }
						if (IS_VALID(i/**/, j + 1) && mapAns[i/**/][j + 1] != BOMB) { mapAns[i/**/][j + 1]++; }
						if (IS_VALID(i + 1, j - 1) && mapAns[i + 1][j - 1] != BOMB) { mapAns[i + 1][j - 1]++; }
						if (IS_VALID(i + 1, j/**/) && mapAns[i + 1][j/**/] != BOMB) { mapAns[i + 1][j/**/]++; }
						if (IS_VALID(i + 1, j + 1) && mapAns[i + 1][j + 1] != BOMB) { mapAns[i + 1][j + 1]++; }
					}
				}
			}
		}
	}

	// After loading the board of answer, set the game board and compute RemainBlankCount.
	if (success) {
		// Fill the game board with the icon of blank.
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				map[i][j] = BLANK;
			}
		}

		// Compute RemainBlankCount.
		RemainBlankCount = row * col - BombCount;

		// Record it has load the board.
		hasLoad = true;

		// Print out message.
		OUT << "Success\n";
	}

	// If not success to loading, print out Failed.
	else { OUT << "Failed\n"; }
}

// Intent: LeftClick.
// Pre: Input a coordinate.
// Post: The function returns nothing.
void Board::leftClick(int clickRow, int clickCol) {
	// The coordinate should be valid and the icon should be blank or question mark.
	if (!IS_VALID(clickRow, clickCol) || (map[clickRow][clickCol] != BLANK && map[clickRow][clickCol] != QUESTION_MARK)) {
		OUT << "Failed\n";
		return;
	}
	OUT << "Success\n";

	// If the bomb was clicked, game over, and print out the message.
	if (mapAns[clickRow][clickCol] == BOMB) {
		state = GameOver;
		OUT << "You lose the game\n";

		// Show the answer
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				map[i][j] = mapAns[i][j];
			}
		}
	}
	// If a 0 was clicked, diffuse.
	else if (mapAns[clickRow][clickCol] == '0') {
		diffuse(clickRow, clickCol);
	}
	// If a number was clicked, open it and change the record.
	else {
		map[clickRow][clickCol] = mapAns[clickRow][clickCol];
		OpenBlankCount++;
		RemainBlankCount--;
	}

	// Check if the player won the game after clicking.
	if (RemainBlankCount == 0) {
		state = GameOver;
		OUT << "You win the game\n";

		// Show the answer
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				map[i][j] = mapAns[i][j];
			}
		}
	}
}

// Intent: When function leftClick is called, diffuse if it can.
// Pre: Input a coordinate that represents the origin of the diffusion.
// Post: The function returns nothing.
void Board::diffuse(int diffuseRow, int diffuseCol) {
	// If is not valid.
	if (!IS_VALID(diffuseRow, diffuseCol)) { return; }
	// If cannot be open.
	if (map[diffuseRow][diffuseCol] != BLANK && map[diffuseRow][diffuseCol] != QUESTION_MARK) { return; }
	// If the answer is a bomb, it cannot be diffused.
	else if (mapAns[diffuseRow][diffuseCol] == BOMB) { return; }

	// If it can be diffused, open it and change the record.
	map[diffuseRow][diffuseCol] = mapAns[diffuseRow][diffuseCol];
	OpenBlankCount++;
	RemainBlankCount--;

	// If still need to diffuse, diffuse the surrounding coordinates.
	if (mapAns[diffuseRow][diffuseCol] == '0') {
		diffuse(diffuseRow - 1, diffuseCol - 1);
		diffuse(diffuseRow - 1, diffuseCol/**/);
		diffuse(diffuseRow - 1, diffuseCol + 1);
		diffuse(diffuseRow/**/, diffuseCol - 1);
		diffuse(diffuseRow/**/, diffuseCol + 1);
		diffuse(diffuseRow + 1, diffuseCol - 1);
		diffuse(diffuseRow + 1, diffuseCol/**/);
		diffuse(diffuseRow + 1, diffuseCol + 1);
	}
}

// Intent: rightClick.
// Pre: Input a coordinate.
// Post: The function returns nothing.
void Board::rightClick(int clickRow, int clickCol) {
	// The coordinate should be valid and the icon should be blank, flag, or question mark.
	if (!IS_VALID(clickRow, clickCol) || (map[clickRow][clickCol] >= '0' && map[clickRow][clickCol] <= '8')) {
		OUT << "Failed\n";
		return;
	}
	OUT << "Success\n";

	// Change between blank, flag, and question mark.
	if (map[clickRow][clickCol] == BLANK) {
		map[clickRow][clickCol] = FLAG;
		FlagCount++;
	}
	else if (map[clickRow][clickCol] == FLAG) {
		map[clickRow][clickCol] = QUESTION_MARK;
		FlagCount--;
	}
	else if (map[clickRow][clickCol] == QUESTION_MARK) {
		map[clickRow][clickCol] = BLANK;
	}
}