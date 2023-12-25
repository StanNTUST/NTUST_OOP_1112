// File: Chessman.cpp
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/04
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/04
// Description : This C++ program define the member functions of class "Chessman".

#include "definition.h"
#include "Chessman.h"

extern char gBoard[ROW][COL];
extern bool isCheating;
bool isDiagonalEat;
extern string pass;
extern bool castlingRights[4];

// Intent: Contruct the chessman.
// Pre: Input nothing.
// Post: The function returns nothing.
Chessman::Chessman() {
	// Initialize the valid destination of chessman.
	initValidDestination();

	// Initialize the danger position of chessman.
	initDanger();
}

// Intent: Set up the chessman
// Pre: Input color, type, row, column, opponent player, and current player.
// Post: The function returns nothing.
Chessman::Chessman(color chessmanColor, type chessmanType, int row, int col, Player** chessmanOpponent, Player* chessmanCurrent) :Chessman() {
	sColor = chessmanColor;
	sType = chessmanType;
	rowPos = row;
	colPos = col;
	opponentPlayer = chessmanOpponent;
	currentPlayer = chessmanCurrent;
}

// Intent: Initialize the board of valid destinations.
// Pre: Input nothing.
// Post: The function returns nothing.
void Chessman::initValidDestination() {
	// Innitiaize the board of valid destinations.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			validDestinations[i][j] = false;
		}
	}
}

// Intent: Initialize the board of danger.
// Pre: Input nothing.
// Post: The function returns nothing.
void Chessman::initDanger() {
	// Initialize the board of danger.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			danger[i][j] = false;
		}
	}
}

// Intent: Check if the position is valid, is blank, is mine, or is opponent.
// Pre: Input a coordinate and a feature that want to check.
// Post: The function returns a bool.
bool Chessman::check(int row, int col, feature f) {
	// The coordinate should be valid.
	if (!(0 <= row && row < ROW && 0 <= col && col < COL)) { return false; }

	// If valid, return true.
	if (f == valid) { return true; }

	// If the gBoard's position is blank, return true, else return false.
	if (f == blank) {
		if (gBoard[row][col] == BLANK) { return true; }
		return false;
	}

	// If the gBoard's position is my chessman, return true, else return false.
	if (f == mine) {
		// If current player is white and the position is my piece, return true.
		if (sColor == white && isupper(gBoard[row][col])) { return true; }
		// If current player is black and the position is my piece, return true.
		else if (sColor == black && islower(gBoard[row][col])) { return true; }
		// Else return false.
		return false;
	}

	// If the gBoard's position is opposite chessman, return true, else return false.
	if (f == opponent) {
		// If current player is white and the position is opponent's piece, return true.
		if (sColor == white && islower(gBoard[row][col])) { return true; }
		// If current player is black and the position is opponent's piece, return true.
		else if (sColor == black && isupper(gBoard[row][col])) { return true; }
		// Else return false.
		return false;
	}
}

// Intent: This function is used to find valid destinition for queen, bishop, and rook in specific direction.
// Pre: Input a direction and a bool.
// Post: The function returns nothing.
void Chessman::movingRule(direction d, bool currPlayerMoving) {
	for (int i = 1;; i++) {
		int row = 0, col = 0;

		// Set the direction to find the piece.
		if (d == Up) { row = -i; }
		else if (d == Down) { row = i; }
		else if (d == Left) { col = -i; }
		else if (d == Right) { col = i; }
		else if (d == UpLeft) { row = -i; col = -i; }
		else if (d == UpRight) { row = -i; col = i; }
		else if (d == DownLeft) { row = i; col = -i; }
		else if (d == DownRight) { row = i; col = i; }

		// If the position is not valid, break the loop.
		if (!check(rowPos + row, colPos + col, valid)) { break; }

		// If the position is my piece, break the loop.
		if (check(rowPos + row, colPos + col, mine)) { break; }

		// Virtual move the piece to find the danger place.
		if (currPlayerMoving) { virtualMove(rowPos + row, colPos + col); }

		// If king is not danger, valid destination is true.
		if (!kingDanger()) { validDestinations[rowPos + row][colPos + col] = true; }

		// If the position is opponent piece, break the loop.
		if (check(rowPos + row, colPos + col, opponent)) { break; }
	}
}

// Intent: This function is used to find valid destinition for knight and king.
// Pre: Input a coordinate and a bool.
// Post: The function returns nothing.
void Chessman::open(int row, int col, bool currPlayerMoving) {
	// If the position is blank or opponent
	if (check(row, col, blank) || check(row, col, opponent)) {
		// Virtual move if current player is moving.
		if (currPlayerMoving) { virtualMove(row, col); }

		// If the king is save, the destination is valid.
		if (!kingDanger()) { validDestinations[row][col] = true; }
	}
}

// Intent: let the chessman do a virtual move to make sure the slot is safe.
// Pre: Input a coordinate.
// Post: The function returns nothing, but checked the slot is safe or not.
void Chessman::virtualMove(int row, int col) {
	// Record the symbol of two coordinates.
	char currSymbol = gBoard[rowPos][colPos];
	char destSymbol = gBoard[row][col];

	// Virtual move to the destination.
	gBoard[rowPos][colPos] = BLANK;
	gBoard[row][col] = (sColor == white) ? WHITE_SYMBOL[sType] : BLACK_SYMBOL[sType];

	// Find danger place.
	initDanger();
	findDangerPlace(row, col);

	// Move back.
	gBoard[rowPos][colPos] = currSymbol;
	gBoard[row][col] = destSymbol;
}

// Intent: Find valid destination and fill bool into validDestinations.
// Pre: Input a bool.
// Post: The function returns nothing.
void Chessman::findValidDestination(bool currPlayerMoving) {
	// If is cheating, all the position is valid wherever current player's chess is not on the position.
	if (isCheating) {
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				if (sColor == white && !isupper(gBoard[i][j])) { validDestinations[i][j] = true; }
				if (sColor == black && !islower(gBoard[i][j])) { validDestinations[i][j] = true; }
			}
		}

		return;
	}

	// Initialize the board of valid destinations.
	initValidDestination();

	// Find valid destination and fill bool into validDestinations

	// Pawn
	if (sType == pawn) {
		// white
		if (sColor == white) {
			// front
			if (check(rowPos - 1, colPos, blank)) {
				// 1 step
				if (currPlayerMoving) { virtualMove(rowPos - 1, colPos); }
				if (!kingDanger()) { validDestinations[rowPos - 1][colPos] = true; }

				// 2 step
				if (pieceHasMoved == false && check(rowPos - 2, colPos, blank)) {
					if (currPlayerMoving) { virtualMove(rowPos - 2, colPos); }
					if (!kingDanger()) { validDestinations[rowPos - 2][colPos] = true; }
				}
			}
			// Left front
			if (check(rowPos - 1, colPos - 1, opponent)) {
				if (currPlayerMoving) { virtualMove(rowPos - 1, colPos - 1); }
				if (!kingDanger()) { validDestinations[rowPos - 1][colPos - 1] = true; }
			}
			// Right front
			if (check(rowPos - 1, colPos + 1, opponent)) {
				if (currPlayerMoving) { virtualMove(rowPos - 1, colPos + 1); }
				if (!kingDanger()) { validDestinations[rowPos - 1][colPos + 1] = true; }
			}
			// Left en passant
			if (check(rowPos, colPos - 1, opponent)) {
				for (int i = 0; i < (*opponentPlayer)->myPieces.size(); i++) {
					// Find the pawn.
					if ((*opponentPlayer)->myPieces[i]->rowPos == rowPos && (*opponentPlayer)->myPieces[i]->colPos == colPos - 1) {
						// If the pawn is en passant.
						if ((*opponentPlayer)->myPieces[i]->isEnPassant) {
							// Check if the position is valid.
							if (currPlayerMoving) { virtualMove(rowPos - 1, colPos - 1); }
							if (!kingDanger()) { validDestinations[rowPos - 1][colPos - 1] = true; }
						}
						else { break; }
					}
				}
			}
			// Right en passant
			if (check(rowPos, colPos + 1, opponent)) {
				for (int i = 0; i < (*opponentPlayer)->myPieces.size(); i++) {
					// Find the pawn.
					if ((*opponentPlayer)->myPieces[i]->rowPos == rowPos && (*opponentPlayer)->myPieces[i]->colPos == colPos + 1) {
						// If the pawn is en passant.
						if ((*opponentPlayer)->myPieces[i]->isEnPassant) {
							// Check if the position is valid.
							if (currPlayerMoving) { virtualMove(rowPos - 1, colPos + 1); }
							if (!kingDanger()) { validDestinations[rowPos - 1][colPos + 1] = true; }
						}
						else { break; }
					}
				}
			}
		}
		// black
		else if (sColor == black) {
			// front
			if (check(rowPos + 1, colPos, blank)) {
				// 1 step
				if (currPlayerMoving) { virtualMove(rowPos + 1, colPos); }
				if (!kingDanger()) { validDestinations[rowPos + 1][colPos] = true; }

				// 2 step
				if (pieceHasMoved == false && check(rowPos + 2, colPos, blank)) {
					if (currPlayerMoving) { virtualMove(rowPos + 2, colPos); }
					if (!kingDanger()) { validDestinations[rowPos + 2][colPos] = true; }
				}
			}
			// Left front
			if (check(rowPos + 1, colPos - 1, opponent)) {
				if (currPlayerMoving) { virtualMove(rowPos + 1, colPos - 1); }
				if (!kingDanger()) { validDestinations[rowPos + 1][colPos - 1] = true; }
			}
			// Right front
			if (check(rowPos + 1, colPos + 1, opponent)) {
				if (currPlayerMoving) { virtualMove(rowPos + 1, colPos + 1); }
				if (!kingDanger()) { validDestinations[rowPos + 1][colPos + 1] = true; }
			}
			// Left en passant
			if (check(rowPos, colPos - 1, opponent)) {
				for (int i = 0; i < (*opponentPlayer)->myPieces.size(); i++) {
					// Find the pawn.
					if ((*opponentPlayer)->myPieces[i]->rowPos == rowPos && (*opponentPlayer)->myPieces[i]->colPos == colPos - 1) {
						// If the pawn is en passant.
						if ((*opponentPlayer)->myPieces[i]->isEnPassant) {
							// Check if the position is valid.
							if (currPlayerMoving) { virtualMove(rowPos + 1, colPos - 1); }
							if (!kingDanger()) { validDestinations[rowPos + 1][colPos - 1] = true; }
						}
						else { break; }
					}
				}
			}
			// Right en passant
			if (check(rowPos, colPos + 1, opponent)) {
				for (int i = 0; i < (*opponentPlayer)->myPieces.size(); i++) {
					// Find the pawn.
					if ((*opponentPlayer)->myPieces[i]->rowPos == rowPos && (*opponentPlayer)->myPieces[i]->colPos == colPos + 1) {
						// If the pawn is en passant.
						if ((*opponentPlayer)->myPieces[i]->isEnPassant) {
							// Check if the position is valid.
							if (currPlayerMoving) { virtualMove(rowPos + 1, colPos + 1); }
							if (!kingDanger()) { validDestinations[rowPos + 1][colPos + 1] = true; }
						}
						else { break; }
					}
				}
			}
		}
	}

	// Rook
	else if (sType == rook) {
		// Check four directions.
		movingRule(Up, currPlayerMoving);
		movingRule(Down, currPlayerMoving);
		movingRule(Left, currPlayerMoving);
		movingRule(Right, currPlayerMoving);
	}

	// Knight
	else if (sType == knight) {
		// Check 8 destinations.
		open(rowPos - 2, colPos - 1, currPlayerMoving);
		open(rowPos - 2, colPos + 1, currPlayerMoving);
		open(rowPos + 2, colPos - 1, currPlayerMoving);
		open(rowPos + 2, colPos + 1, currPlayerMoving);
		open(rowPos - 1, colPos - 2, currPlayerMoving);
		open(rowPos + 1, colPos - 2, currPlayerMoving);
		open(rowPos - 1, colPos + 2, currPlayerMoving);
		open(rowPos + 1, colPos + 2, currPlayerMoving);
	}

	// Bishop
	else if (sType == bishop) {
		// Check four directions.
		movingRule(UpLeft, currPlayerMoving);
		movingRule(UpRight, currPlayerMoving);
		movingRule(DownLeft, currPlayerMoving);
		movingRule(DownRight, currPlayerMoving);
	}

	// Queen
	else if (sType == queen) {
		// Check eight direction.
		movingRule(Up, currPlayerMoving);
		movingRule(Down, currPlayerMoving);
		movingRule(Left, currPlayerMoving);
		movingRule(Right, currPlayerMoving);
		movingRule(UpLeft, currPlayerMoving);
		movingRule(UpRight, currPlayerMoving);
		movingRule(DownLeft, currPlayerMoving);
		movingRule(DownRight, currPlayerMoving);
	}

	// King
	else if (sType == king) {
		// Normal move
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				// Surrounding 8 coordinates.
				if (i == 0 && j == 0) { continue; }

				// If current player is moving.
				if (currPlayerMoving) {
					// If the coordinate is blank or opponent.
					if (check(rowPos + i, colPos + j, blank) || check(rowPos + i, colPos + j, opponent)) {
						// Check if the position is valid.
						virtualMove(rowPos + i, colPos + j);
						if (!isDanger(rowPos + i, colPos + j)) { validDestinations[rowPos + i][colPos + j] = true; }
					}
				}
				// If the moving player is not current player.
				else {
					// open the coordinate directly.
					open(rowPos + i, colPos + j, currPlayerMoving);
				}
			}
		}
		// long castling
		// If all the conditions meet the requirements of long castling.
		if (check(rowPos, colPos - 1, blank) &&
			check(rowPos, colPos - 2, blank) &&
			check(rowPos, colPos - 3, blank) &&
			((sColor == black && castlingRights[3]) || (sColor == white && castlingRights[1])) &&
			!kingDanger() &&
			!isDanger(rowPos, colPos - 2) &&
			!isDanger(rowPos, colPos - 1))
		{
			// Check if the destination is valid.
			if (currPlayerMoving) { virtualMove(rowPos, colPos - 2); }
			if (!kingDanger()) { validDestinations[rowPos][colPos - 2] = true; }
		}
		// short castling
		// If all the conditions meet the requirements of short castling.
		if (check(rowPos, colPos + 1, blank) &&
			check(rowPos, colPos + 2, blank) &&
			((sColor == black && castlingRights[2]) || (sColor == white && castlingRights[0])) &&
			!kingDanger() &&
			!isDanger(rowPos, colPos + 2) &&
			!isDanger(rowPos, colPos + 1))
		{
			// Check if the destination is valid.
			if (currPlayerMoving) { virtualMove(rowPos, colPos + 2); }
			if (!kingDanger()) { validDestinations[rowPos][colPos + 2] = true; }
		}
	}
}

// Intent: Move the chessman.
// Pre: Input the destination's position.
// Post: The function returns a bool that represent if the chessman has eat someone.
bool Chessman::move(int destRow, int destCol) {
	// Initialize the string "pass".
	pass = "";

	// Check the en passants.
	if (sType == pawn && abs(destRow - rowPos) == 2) {
		// Transfer the FEN coordinate into our coordinate system.
		string transfer = "abcdefgh";

		pass += transfer[colPos];
		pass += '0' + ((sColor == white) ? 3 : 6);

		isEnPassant = true;
	}
	// If there isn't any en passant, set the pass to "-".
	else {
		pass = "-";
	}

	// The bool to record if the chessman has eat someone.
	bool hasEatSomeone = false;

	// Check if the chessman gas eat someone.
	if (gBoard[destRow][destCol] != BLANK) { hasEatSomeone = true; }

	// The pawn's diagnal eat
	if (sType == pawn && gBoard[destRow][destCol] == BLANK) {
		// If white pawn is diagonal eating.
		if (sColor == white && islower(gBoard[destRow + 1][destCol])) {
			isDiagonalEat = true;
			hasEatSomeone = true;
			gBoard[destRow + 1][destCol] = BLANK;
		}
		// If black pawn is diagonal eating.
		else if (sColor == black && isupper(gBoard[destRow - 1][destCol])) {
			isDiagonalEat = true;
			hasEatSomeone = true;
			gBoard[destRow - 1][destCol] = BLANK;
		}
	}

	// Black castlingRights
	if (sColor == black && sType == rook) {
		if (rowPos == 0 && colPos == 0) {
			castlingRights[3] = false;
		}
		else if (rowPos == 0 && colPos == 7) {
			castlingRights[2] = false;
		}
	}
	else if (sColor == black && sType == king) {
		castlingRights[2] = false;
		castlingRights[3] = false;
	}
	// White castlingRights
	if (sColor == white && sType == rook) {
		if (rowPos == 7 && colPos == 0) {
			castlingRights[1] = false;
		}
		else if (rowPos == 7 && colPos == 7) {
			castlingRights[0] = false;
		}
	}
	else if (sColor == white && sType == king) {
		castlingRights[0] = false;
		castlingRights[1] = false;
	}

	// Manage the castling if the rook has been eat.
	if (hasEatSomeone && gBoard[destRow][destCol] == WHITE_SYMBOL[rook]) {
		if (castlingRights[0] && destRow == 7 && destCol == 7) { castlingRights[0] = false; }
		else if (castlingRights[1] && destRow == 7 && destCol == 0) { castlingRights[1] = false; }
	}
	if (hasEatSomeone && gBoard[destRow][destCol] == BLACK_SYMBOL[rook]) {
		if (castlingRights[2] && destRow == 0 && destCol == 7) { castlingRights[2] = false; }
		else if (castlingRights[3] && destRow == 0 && destCol == 0) { castlingRights[3] = false; }
	}

	// Move to the destination.
	gBoard[rowPos][colPos] = BLANK;
	if (sColor == black) { gBoard[destRow][destCol] = BLACK_SYMBOL[sType]; }
	else { gBoard[destRow][destCol] = WHITE_SYMBOL[sType]; }

	// Change the coordinate into the coordinate of destination.
	rowPos = destRow;
	colPos = destCol;

	// Initialize the valid destination and danger place.
	initValidDestination();
	initDanger();

	// Return if the chessman has eat someone.
	return hasEatSomeone;
}

// Intent: find a danger space of an opponent chessman.
// Pre: Input a coordinate.
// Post: set the danger place
void Chessman::findDangerPlace(int row, int col) {
	for (int i = 0; i < (*opponentPlayer)->myPieces.size(); i++) {
		// If the coordinate is the current coordinate, continue.
		if ((*opponentPlayer)->myPieces[i]->rowPos == row && (*opponentPlayer)->myPieces[i]->colPos == col) { continue; }

		// My danger place equals to opponent's valid destination.
		(*opponentPlayer)->myPieces[i]->findValidDestination(false);

		// Check if the place is danger.
		for (int j = 0; j < ROW; j++) {
			for (int k = 0; k < COL; k++) {
				danger[j][k] = danger[j][k] || (*opponentPlayer)->myPieces[i]->validDestinations[j][k];
			}
		}

		// Initialize the opponent's valid destination.
		(*opponentPlayer)->myPieces[i]->initValidDestination();
	}
}

// Intent: Check if the king is in danger.
// Pre: Input nothing.
// Post: Return whether king is in danger or not.
bool Chessman::kingDanger() {
	// Record king symbol.
	char kingSymbol = (sColor == black) ? BLACK_SYMBOL[king] : WHITE_SYMBOL[king];

	// Find the coordinate and return if the coordinate is danger.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (gBoard[i][j] == kingSymbol) {
				return danger[i][j];
			}
		}
	}
}

// Intent: Check if the destination is danger.
// Pre: Input the destination's position.
// Post: The function returns a bool.
bool Chessman::isDanger(int destRow, int destCol) {
	return check(destRow, destCol, valid) && danger[destRow][destCol];
}