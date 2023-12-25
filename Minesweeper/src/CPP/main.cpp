// File: main.cpp
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005, B11130038
// Update Date : 2023/04/12
// Description : This C++ program allows user to play mine sweeper.

// All the preprocessor like #include or #define are in this header file,
// and also the declaration of class "Board".
#include "Board.h"

// The declaration and definition of split function is in this header file.
#include "split.h"

// Global values : These values are shared with other files in the project.
ifstream iFile;
ofstream oFile;
int ioMode = commandIO;

int main(int argc, char* argv[]) {
	// Record IO mode.
	if (argc == 1) { ioMode = commandIO; }
	else if (argc == 4 && strcmp(argv[1], "CommandFile") == 0) { ioMode = fileIO; }
	else if (argc == 2 && strcmp(argv[1], "CommandInput") == 0) { ioMode = commandIO; }
	else if (argc == 2 && strcmp(argv[1], "GUI") == 0) { ioMode = GUI; }

	// If use file IO, open the files.
	if (ioMode == fileIO) {
		iFile.open(argv[2]);
		oFile.open(argv[3]);
	}

	// If use GUI.
	if (ioMode == GUI) {
		return 0;
	}

	string text;
	Board gBoard;

	while (getline(IN, text)) {
		// Use a string vector to store the input text, seporate by blanks.
		vector<string> cmds;
		split(text, cmds, ' ');

		// If the cmd is Print, call print function.
		if (cmds.front() == "Print" && cmds.size() == 2) {
			OUT << "<" << text << "> : ";
			gBoard.print(cmds[1]);
		}

		// If the state is Standby.
		else if (gBoard.state == Standby) {
			// If the cmd is Load, call load function.
			if (cmds.front() == "Load") {
				OUT << "<" << text << "> : ";
				gBoard.loadBoard(cmds);
			}
			// If the cmd is StartGame, change game state if it can.
			else if (cmds.front() == "StartGame" && cmds.size() == 1 && gBoard.hasLoad) {
				gBoard.state = Playing;
				OUT << "<" << text << "> : Success\n";
			}
			// If the cmd is invalid, print Failed.
			else {
				OUT << "<" << text << "> : Failed\n";
			}
		}

		// If the state is Playing.
		else if (gBoard.state == Playing && cmds.size() == 3) {
			// If the cmd is LeftClick, call LeftClick function.
			if (cmds.front() == "LeftClick") {
				OUT << "<" << text << "> : ";
				gBoard.leftClick(stoi(cmds[1]), stoi(cmds[2]));
			}
			// If the cmd is RightClick, call RightClick function.
			else if (cmds.front() == "RightClick") {
				OUT << "<" << text << "> : ";
				gBoard.rightClick(stoi(cmds[1]), stoi(cmds[2]));
			}
			// If the cmd is invalid, print Failed.
			else {
				OUT << "<" << text << "> : Failed\n";
			}
		}

		// If the state is GameOver.
		else if (gBoard.state == GameOver && cmds.size() == 1) {
			// If the cmd is Replay, reconstruct the board.
			if (cmds.front() == "Replay") {
				gBoard.Board::Board();
				gBoard.state = Standby;
				OUT << "<" << text << "> : Success\n";
			}
			// If the cmd is Quit, break the loop.
			else if (cmds.front() == "Quit") {
				OUT << "<" << text << "> : Success\n";
				break;
			}
			// If the cmd is invalid, print Failed.
			else {
				OUT << "<" << text << "> : Failed\n";
			}
		}

		// If the cmd is invalid, print Failed.
		else {
			OUT << "<" << text << "> : Failed\n";
		}
	}

	// Close the files before return 0.
	if (fileIO) {
		iFile.close();
		oFile.close();
	}

	return 0;
}