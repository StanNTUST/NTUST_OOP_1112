// File: main.cpp
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This C++ program allow user to play pokemon.

#include"definition.h"
#include"GameManager.h"

// Intent: Output information.
// Pre: Input nothing.
// Post: The function returns nothing.
void information() {
	cout << "Please input integer to start the game" << endl;
	cout << "Input -1: Exit" << endl;
	cout << "Input 0: Load file" << endl;
	cout << "Input 1: Command file" << endl;
}

int main() {
	int type;
	string gameDataFileName, moveLibFileName, pokemonLibFileName, commandFile;

	while (1) {
		GameManager gManager;

		information();

		cin >> type;

		system("CLS");

		// Load file
		if (type == gameType::loadFile) {
			// Input pokemon library
			cout << "Please Input Pokemon library file path";
			cin >> pokemonLibFileName;
			system("CLS");

			// Input move library
			cout << "Please Input move library file path";
			cin >> moveLibFileName;
			system("CLS");

			// Input game data
			cout << "Please Input game data file path";
			cin >> gameDataFileName;
			system("CLS");

			gManager.setPokeMonLibrary(pokemonLibFileName);
			gManager.setMoveLibrary(moveLibFileName);
			gManager.setGameData(gameDataFileName);

			gManager.combat();

			system("CLS");

			gManager.printTurnMessage();
			gManager.showCombatImformation();

			break;
		}
		// Command file
		else if (type == gameType::commandFile) {
			// Input command file
			cin >> commandFile;
			gManager.setCommandFile(commandFile);

			system("CLS");

			gManager.combat();

			system("CLS");

			gManager.printTurnMessage();
			gManager.showCombatImformation();

			break;
		}
		// Exit
		else if (type == gameType::exitGame) break;
	}

	system("pause");
}

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