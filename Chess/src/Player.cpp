// File: Player.cpp
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This C++ program define the member functions of class "Player".

#include "definition.h"
#include "Player.h"

extern char gBoard[ROW][COL];
extern bool isDiagonalEat;
extern bool castlingRights[4];

status Player::game = carry;

// Intent: Set color and initialize the player.
// Pre: Input a color.
// Post: The function returns nothing.
void Player::setColor(color playerColor) {
	// Set color and the tempo.
	pColor = playerColor;
	myTurn = (pColor == white) ? true : false;

	for (int i = 0; i < myPieces.size(); i++) {
		delete myPieces[i];
	}
	myPieces.clear();

	// Give chessmen to player.
	Chessman* tmp;
	int settingRow = (pColor == black) ? 0 : 7;

	// Initialize all the chessman, and push back into the vector.
	tmp = new Chessman(pColor, rook, settingRow, 0, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, knight, settingRow, 1, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, bishop, settingRow, 2, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, queen, settingRow, 3, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, king, settingRow, 4, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, bishop, settingRow, 5, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, knight, settingRow, 6, &myOpponent, this); myPieces.push_back(tmp);
	tmp = new Chessman(pColor, rook, settingRow, 7, &myOpponent, this); myPieces.push_back(tmp);
	settingRow += (pColor == black) ? 1 : -1;
	for (int i = 0; i < COL; i++) {
		tmp = new Chessman(pColor, pawn, settingRow, i, &myOpponent, this); myPieces.push_back(tmp);
	}
}

// Intent: Set myOpponent to opponent player.
// Pre: None.
// Post: MyOpponent has been set to the opponent pointer.
void Player::setOpponent(Player* opponentPlayer) {
	myOpponent = opponentPlayer;
}

// Intent: Set all player's the chessman into myPiece vector.
// Pre: None.
// Post: Set all player's the chessman into myPiece vector.
void Player::setMyPieces() {
	type types[numOfType] = { king, queen, bishop, knight, rook, pawn };

	// Clear the pointer vector.
	myPieces.clear();

	Chessman* tmp;

	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			// If the coordinate is not chessman, continue.
			if (gBoard[i][j] == BLANK) { continue; }

			for (int k = 0; k < numOfType; k++) {
				// If the coordinate is white chessman.
				if (pColor == white && gBoard[i][j] == WHITE_SYMBOL[k]) {
					// Create the chessman.
					tmp = new Chessman(pColor, types[k], i, j, &myOpponent, this);

					// Check if the pawn has move.
					if (types[k] == pawn && i != 6) { tmp->pieceHasMoved = true; }

					// Push back the chessman.
					myPieces.push_back(tmp);
				}
				// If the coordinate is black chessman.
				else if (pColor == black && gBoard[i][j] == BLACK_SYMBOL[k]) {
					// Create the chessman.
					tmp = new Chessman(pColor, types[k], i, j, &myOpponent, this);

					// Check if the pawn has move.
					if (types[k] == pawn && i != 1) { tmp->pieceHasMoved = true; }

					// Push back the chessman.
					myPieces.push_back(tmp);
				}
			}
		}
	}
}

// Intent: Control the player's status.
// Pre: None.
// Post: Set the player status.
void Player::status() {
	// Set initial conditions.
	bool canMove = false;
	bool kingDanger = false;
	bool type[7] = { false }, oppoentType[7] = { false };

	// Find opponent if they can move and set which type of chessmen opponent has.
	for (int i = 0; i < myOpponent->myPieces.size(); i++) {
		// Find opponent's piece's valid destination and danger position.
		myOpponent->myPieces[i]->findValidDestination(true);
		myOpponent->myPieces[i]->findDangerPlace();

		// Set the oppoenent's chessman has this type.
		oppoentType[myOpponent->myPieces[i]->sType] = true;

		// Find if the piece has valid destination and if it can attack king
		for (int j = 0; j < ROW; j++) {
			for (int k = 0; k < COL; k++) {
				// If the one of the pieces has valid destinations, opponent can move.
				if (myOpponent->myPieces[i]->validDestinations[j][k] == true) canMove = true;

				// If one of the pieces can attack king, king danger is true
				if (myOpponent->myPieces[i]->kingDanger()) kingDanger = true;

				// If can move, break the loop.
				if (canMove) break;
			}

			// If can move, break the loop.
			if (canMove) break;
		}
		// Innitialize opponent's piece's valid destination and danger position
		myOpponent->myPieces[i]->initValidDestination();
		myOpponent->myPieces[i]->initDanger();
	}

	// Set the my chessman has this type.
	for (int i = 0; i < myPieces.size(); i++) {
		type[myPieces[i]->sType] = true;
	}

	// If opponent can move
	if (canMove) {
		// If king is not in the board
		if (!oppoentType[king]) {
			// If my turn's color is black, game is black win.
			if (pColor == black) game = blackWin;
			// Else game is white win
			else game = whiteWin;
		}

		// If each player has type queen, rook or pawn, game is carry.
		else if (type[queen] || oppoentType[queen] || type[rook] || oppoentType[rook] || type[pawn] || oppoentType[pawn]) game = carry;
		// If each other just has king, game is draw.
		else if (type[king] && oppoentType[king] && !type[knight] && !oppoentType[knight] && !type[bishop] && !oppoentType[bishop]) game = draw;
		// If each other has king and one of them has knight, game is draw.
		else if (type[king] && oppoentType[king] && type[knight] && !oppoentType[knight] && !type[bishop] && !oppoentType[bishop]) game = draw;
		// If each other has king and at least one of them has bishop, game is draw.
		else if (type[king] && oppoentType[king] && !type[knight] && !oppoentType[knight] && (type[bishop] || oppoentType[bishop])) game = draw;
		// Else game is carry.
		else game = carry;
	}
	// If opponent can not move
	else {
		// If king is danger
		if (kingDanger) {
			//If my turn's color is white, game is white win.
			if (pColor == white) game = whiteWin;
			//If my turn's color is black, game is black win.
			else if (pColor == black) game = blackWin;
		}
		// If king is not danger, game is draw.
		else game = draw;
	}
}

// Intent: Check if the chessman at (row, col) is the player's piece.
// Pre: Input row and column.
// Post: The function returns a bool.
bool Player::isMyPiece(int row, int col) {
	// Find the position if it is my pieces.
	for (int i = 0; i < numOfType; i++) {
		// If my turn's color is white, and the position is white symbol, return true.
		if (pColor == white && gBoard[row][col] == WHITE_SYMBOL[i]) { return true; }
		// If my turn's color is black, and the position is black symbol, return true.
		else if (pColor == black && gBoard[row][col] == BLACK_SYMBOL[i]) { return true; }
	}

	// Return false if the position is not my turn's piece.
	return false;
}

// Intent: Player want to move.
// Pre: Input row and column.
// Post: The function returns a bool that represent if the chessman has eat someone.
bool Player::wantMove(int row, int col) {
	// Player should choose his own piece before moving.
	if (!hasChoose && !isMyPiece(row, col)) { return false; }

	// Find the moving piece.
	for (int i = 0; i < myPieces.size(); i++) {
		if (myPieces[i]->rowPos == row && myPieces[i]->colPos == col) {
			movingPiece = myPieces[i];
		}
	}

	// Move the movingPiece if it can.
	bool hasEatSomeone = false;

	// If valid destination's position is true.
	if (movingPiece->validDestinations[row][col] == true) {

		// If the type is king and moving right two piece, it is long castling.
		if (movingPiece->sType == king && col - movingPiece->colPos == -2) {
			// Find the rook piece
			for (int i = 0; i < myPieces.size(); i++) {
				if (myPieces[i]->sType == rook && myPieces[i]->colPos == 0) {
					// Original position is blank.
					gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = BLANK;

					// Rook move to column 3.
					myPieces[i]->colPos = 3;

					// If moving piece is black, set black rook in the board.
					if (movingPiece->sColor == black) { gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = BLACK_SYMBOL[rook]; }
					// Else set white rook in the board.
					else { gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = WHITE_SYMBOL[rook]; }

					// Break the loop.
					break;
				}
			}
		}
		// If the type is king and moving left two piece, it is short castling
		else if (movingPiece->sType == king && col - movingPiece->colPos == +2) {
			// Find the rook piece
			for (int i = 0; i < myPieces.size(); i++) {
				if (myPieces[i]->sType == rook && myPieces[i]->colPos == 7) {
					// Original position is blank.
					gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = BLANK;

					// Rook move to column 5.
					myPieces[i]->colPos = 5;

					// If moving piece is black, set black rook in the board.
					if (movingPiece->sColor == black) { gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = BLACK_SYMBOL[rook]; }
					// Else set white rook in the board.
					else { gBoard[myPieces[i]->rowPos][myPieces[i]->colPos] = WHITE_SYMBOL[rook]; }

					// Break the loop.
					break;
				}
			}
		}

		// Move the piece and if moving eat someone, hasEatSomeone is true.
		if (movingPiece->move(row, col)) { hasEatSomeone = true; }

		// Has move is true.
		hasMoved = true;

		// Moving piece has move.
		movingPiece->pieceHasMoved = true;

		// If moving is diagonal eat, hasEatSomeone is true.
		if (isDiagonalEat) hasEatSomeone = true;
	}
	// Otherwise, find valid destination.
	else {
		// Find valid destination.
		movingPiece->findValidDestination(true);

		// Has Choose the piece.
		hasChoose = true;
	}

	return hasEatSomeone;
}