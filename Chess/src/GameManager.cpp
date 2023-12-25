// File: GameManager.cpp
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/04
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/04
// Description : This C++ program define the member functions of class "GameManager".

#include "definition.h"
#include "GameManager.h"

char gBoard[ROW][COL] = { 0 };
string pass = "-";
bool castlingRights[4] = { true,true,true,true };
vector<promoteRecord> promotion;

// Intent: Split a string with separator and store the words into a string vector.
// Pre: Input a string, a string vector, and a char.
// Post: The function returns nothing.
void split(string& str, vector<string>& splited, char separator) {
	// Append a separator because it's the ending condition.
	str += separator;

	string tmp;

	// Spliting
	for (int i = 0; i < str.length(); i++) {
		// Append the char into the string if it is not separator.
		if (str[i] != separator) {
			tmp += str[i];
		}
		// Push back the word if meet a separator.
		else {
			splited.push_back(tmp);
			tmp.clear();
		}
	}
}

// Intent: Initialize game board and players.
// Pre: Input nothing.
// Post: The function returns nothing.
GameManager::GameManager() {
	// Innitialize the game board.
	initializeGameBoard();

	// Set players' color.
	blackPlayer.setColor(black);
	whitePlayer.setColor(white);

	// Set players' opponent.
	blackPlayer.setOpponent(&whitePlayer);
	whitePlayer.setOpponent(&blackPlayer);
}

// Intent: Initialize game board.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::initializeGameBoard() {
	setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -");
}

// Intent: Change player.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::changePlayer() {
	// Change the turn
	whoseTurn = (whoseTurn == white) ? black : white;

	// If turn is black, blackPlayer's myTurn is true, else myTurn is false
	blackPlayer.myTurn = (whoseTurn == black) ? true : false;

	// If turn is white, whitePlayer's myTurn is true, else myTurn is false
	whitePlayer.myTurn = (whoseTurn == white) ? true : false;
}

// Intent: Get game state.
// Pre: Input nothing.
// Post: The function returns a string.
string GameManager::getGameState() {
	//return game state
	if (gState == Standby) { return "Standby"; }
	else if (gState == Playing) { return "Playing"; }
	else if (gState == GameOver) { return "GameOver"; }
}

// Intent: Print game board.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::printGameBoard() {
	// Print game board.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << gBoard[i][j] << " ";
		}
		cout << endl;
	}

	// Print FEN.
	cout << getFEN() << endl;
}

// Intent: Print record.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::printRecord() {
	cout << "Record : \n";

	// Print all records.
	for (int i = 0; i < stepRecord.size(); i++) {
		cout << stepRecord[i] << endl;
	}
}

// Intent: Get FEN from gBoard.
// Pre: Input nothing.
// Post: The function returns a string.
string GameManager::getFEN() {
	string FEN;
	int blankCount = 0;

	// Input the board to the FEN.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			// If position is blank, blank count add 1.
			if (gBoard[i][j] == BLANK) { blankCount++; }
			// If not, input the blank count and piece's symbol to the FEN.
			else {
				// If blank count is not 0, input the blank count to the FEN and reset 0.
				if (blankCount) {
					FEN += '0' + blankCount;
					blankCount = 0;
				}

				// Input piece's symbol to the FEN.
				FEN += gBoard[i][j];
			}
		}

		// If blank count is not 0, input the blank count to the FEN.
		if (blankCount) { FEN += '0' + blankCount; }

		// Reset blank count.
		blankCount = 0;

		// If row is not the last row, input '/' to the FEN.
		if (i != ROW - 1) { FEN += '/'; }
	}

	// If turn is white, input 'w' to the FEN.
	if (whoseTurn == white) { FEN += " w "; }
	// Else input 'b' to the FEN.
	else { FEN += " b "; }

	// Input castling string to the FEN.
	FEN += checkCastling();

	// If record index is 0.
	if (recordIndex == 0) {
		pass = "";
		bool found = false;
		string transfer = "abcdefgh";

		// Search the white pieces when not found. 
		for (int i = 0; i < whitePlayer.myPieces.size() && !found; i++) {
			// If the piece is en passant.
			if (whitePlayer.myPieces[i]->isEnPassant) {
				// Pass add the charactor by colum position.
				pass += transfer[whitePlayer.myPieces[i]->colPos];

				// Pass add row position.
				pass += '0' + ((whitePlayer.myPieces[i]->sColor == white) ? 3 : 6);

				found = true;
			}
		}

		// Search the black pieces when not found. 
		for (int i = 0; i < blackPlayer.myPieces.size() && !found; i++) {
			// If the piece is en passant.
			if (blackPlayer.myPieces[i]->isEnPassant) {
				// Pass add the charactor by colum position.
				pass += transfer[blackPlayer.myPieces[i]->colPos];

				// Pass add row position.
				pass += '0' + ((blackPlayer.myPieces[i]->sColor == white) ? 3 : 6);

				found = true;
			}
		}

		// If pass is empty, pass add '-'.
		if (pass == "") { pass += "-"; }
	}

	// Input pass to the FEN.
	FEN += " " + pass;

	return FEN;
}

// Intent: Set the game status by FEN.
// Pre: Input a string representing FEN.
// Post: The function returns nothing.
void GameManager::setFEN(string FEN) {
	vector<string> words;

	// Split the FEN to the words.
	split(FEN, words, ' ');

	// If words size is less then 3, return.
	if (words.size() < 3) { return; }

	int setRow = 0, setCol = 0;

	// Set up gBoard by the first word's letters.
	for (int i = 0; i < words[0].length(); i++) {
		// If the letter is '/', row add 1 and reset col.
		if (FEN[i] == '/') {
			setRow++;
			setCol = 0;
		}
		// If the letter is digit, set the blank by its number.
		else if (isdigit(FEN[i])) {
			// Set the blank by its number.
			for (int blankCount = 0; blankCount < FEN[i] - '0'; blankCount++) {
				gBoard[setRow][setCol] = BLANK;
				setCol++;
			}
		}
		// Else set the symbol to the board.
		else {
			gBoard[setRow][setCol] = FEN[i];
			setCol++;
		}
	}

	// Set up pieces.
	whitePlayer.setMyPieces();
	blackPlayer.setMyPieces();

	// Inntialize hasChoose and hasMove.
	whitePlayer.hasChoose = false;
	whitePlayer.hasMoved = false;
	blackPlayer.hasChoose = false;
	blackPlayer.hasMoved = false;

	// Set whose turn.
	if (words[1] == "b" && whoseTurn == white) { changePlayer(); }
	else if (words[1] == "w" && whoseTurn == black) { changePlayer(); }

	// Innitialize the castling rights.
	for (int i = 0; i < 4; i++) {
		castlingRights[i] = false;
	}

	// Set castling rights.
	for (int i = 0; i < words[2].size(); i++) {
		if (words[2][i] == 'K') { castlingRights[0] = true; }
		else if (words[2][i] == 'Q') { castlingRights[1] = true; }
		else if (words[2][i] == 'k') { castlingRights[2] = true; }
		else if (words[2][i] == 'q') { castlingRights[3] = true; }
	}

	// If words is 3, return.
	if (words.size() == 3) { return; }

	// If the third word, inntialize both players' pieces' isEnPassant.
	if (words[3] == "-") {
		for (int i = 0; i < blackPlayer.myPieces.size(); i++) {
			blackPlayer.myPieces[i]->isEnPassant = false;
		}

		for (int i = 0; i < whitePlayer.myPieces.size(); i++) {
			whitePlayer.myPieces[i]->isEnPassant = false;
		}
	}
	// If the word is '3', inntialize both players' pieces' isEnPassant and find the isEnPassant piece in white pieces.
	else if (words[3][1] == '3') {
		// Inntialize black pieces' isEnpassant.
		for (int i = 0; i < blackPlayer.myPieces.size(); i++) {
			blackPlayer.myPieces[i]->isEnPassant = false;
		}

		// Inntialize white pieces' isEnpassant and find the isEnPassant piece.
		for (int i = 0; i < whitePlayer.myPieces.size(); i++) {
			// if rosPos is 4 and colPos is the same, the piece is enPassant.
			if (whitePlayer.myPieces[i]->rowPos == 4 && whitePlayer.myPieces[i]->colPos == words[3][0] - 'a') {
				whitePlayer.myPieces[i]->isEnPassant = true;
			}
			// else Inntialize white piece's isEnpassant.
			else {
				whitePlayer.myPieces[i]->isEnPassant = false;
			}
		}
	}
	// If the word is '6', inntialize both players' pieces' isEnPassant and find the isEnPassant piece in black pieces.
	else if (words[3][1] == '6') {
		// Inntialize black pieces' isEnpassant and find the isEnPassant piece.
		for (int i = 0; i < blackPlayer.myPieces.size(); i++) {
			// if rosPos is 6 and colPos is the same, the piece is enPassant.
			if (blackPlayer.myPieces[i]->rowPos == 3 && blackPlayer.myPieces[i]->colPos == words[3][0] - 'a') {
				blackPlayer.myPieces[i]->isEnPassant = true;
			}
			// else Inntialize white piece's isEnpassant.
			else {
				blackPlayer.myPieces[i]->isEnPassant = false;
			}
		}

		// Inntialize white pieces' isEnpassant.
		for (int i = 0; i < whitePlayer.myPieces.size(); i++) {
			whitePlayer.myPieces[i]->isEnPassant = false;
		}
	}
}

// Intent: Record the FEN.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::record() {
	// Erase the step index when then promote index is above record index - 1.
	if (recordIndex != stepRecord.size() - 1) {
		stepRecord.erase(stepRecord.begin() + recordIndex + 1, stepRecord.end());
	}

	// Erase the promotion when the promote index is above record index - 1.
	for (int i = 0; i < promotion.size(); i++) {
		if (promotion[i].promoteIndex > recordIndex) {
			promotion.erase(promotion.begin() + i, promotion.end());
		}
	}

	// Record index add 1.
	recordIndex++;

	// Step record push back new FEN.
	stepRecord.push_back(getFEN());
}

// Intent: Count the death chessman.
// Pre: Input FEN.
// Post: The function returns nothing.
void GameManager::deathCount(string FEN) {
	vector<string> words;
	int whitePiece[numOfType] = { 1,1,2,2,2,8 };
	int blackPiece[numOfType] = { 1,1,2,2,2,8 };

	// Split the FEN to the words.
	split(FEN, words, ' ');

	// Minus type in the board.
	for (int i = 0; i < words[0].length(); i++) {
		// Search which type.
		for (int j = 0; j < numOfType; j++) {
			// If board's symbol is white type's symbol, white type - 1.
			if (FEN[i] == WHITE_SYMBOL[j]) { whitePiece[j]--; }
			// If board's symbol is black type's symbol, black type - 1.
			else if (FEN[i] == BLACK_SYMBOL[j]) { blackPiece[j]--; }
		}
	}

	// Set new white piece to the deadChessman.
	for (int i = 0; i < numOfType; i++) {
		whitePlayer.deadChessman[i] = whitePiece[i];
		blackPlayer.deadChessman[i] = blackPiece[i];
	}
}

// Intent: Undo
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::undo() {
	// If record index > 0.
	if (recordIndex > 0) {
		// Record index - 1.
		recordIndex--;

		// Set the previous FEN
		setFEN(stepRecord[recordIndex]);

		// Set the previous deathCount
		deathCount(stepRecord[recordIndex]);

		// Update deadChessMan due to promotion
		for (int i = 0; i < promotion.size(); i++) {
			// If promote index is above record index, break the loop.
			if (promotion[i].promoteIndex > recordIndex) { break; }

			// "Player's" pawn deadChessman - 1.
			((promotion[i].promoteColor == white) ? whitePlayer.deadChessman : blackPlayer.deadChessman)[pawn]--;

			// "Player's" type deadChessman + 1.
			((promotion[i].promoteColor == white) ? whitePlayer.deadChessman : blackPlayer.deadChessman)[promotion[i].promoteType]++;
		}
	}
}

// Intent: Redo
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::redo() {
	// If record index is less then step record - 1.
	if (recordIndex < stepRecord.size() - 1) {
		recordIndex++;

		// Set the later FEN
		setFEN(stepRecord[recordIndex]);

		// Set the later deathCount
		deathCount(stepRecord[recordIndex]);

		// Update deadChessMan due to promotion
		for (int i = 0; i < promotion.size(); i++) {
			// If promote index is above record index, break the loop.
			if (promotion[i].promoteIndex > recordIndex) { break; }

			// "Player's" pawn deadChessman - 1.
			((promotion[i].promoteColor == white) ? whitePlayer.deadChessman : blackPlayer.deadChessman)[pawn]--;

			// "Player's" type deadChessman + 1.
			((promotion[i].promoteColor == white) ? whitePlayer.deadChessman : blackPlayer.deadChessman)[promotion[i].promoteType]++;
		}
	}
}

// Intent: Get system time.
// Pre: Input nothing.
// Post: The function returns a string.
string GameManager::getTime() {
	stringstream ss;

	// Get the current time from 1970
	time_t currentTime = time(nullptr);

	// Set the time to the normal type 
	ss << put_time(localtime(&currentTime), "%y%m%d_%H%M%S");

	// Return the string
	return ss.str();
}

// Intent: Save file.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::saveFile() {
	char winner;

	// Open the output file.
	ofstream outputFile("./history/" + getTime() + ".txt");

	// If game is the "status", winner is a "symbol".
	if (Player::game == whiteWin) { winner = 'W'; }
	else if (Player::game == blackWin) { winner = 'B'; }
	else if (Player::game == draw) { winner = 'd'; }
	else if (Player::game == blackSurrender) { winner = 'w'; }
	else if (Player::game == whiteSurrender) { winner = 'b'; }

	// Set the symbol to the output file
	outputFile << winner << endl;

	// Set all the record to the output file.
	for (int i = 0; i < stepRecord.size(); i++) {
		outputFile << stepRecord[i] << endl;
	}

	// Close the file
	outputFile.close();
}

// Intent: Check if it can castling.
// Pre: Input nothing.
// Post: The function returns a string.
string GameManager::checkCastling() {
	string castling = "";
	string tmp = "KQkq";

	// Set the castling rights string
	for (int i = 0; i < 4; i++) {
		if (castlingRights[i]) { castling += tmp[i]; }
	}

	// If the string is empty, set '-'
	if (castling.length() == 0) { castling += "-"; }

	return castling;
}