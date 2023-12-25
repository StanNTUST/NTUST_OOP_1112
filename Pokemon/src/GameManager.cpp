// File: GameManager.cpp
// Author: B11130038, B11130005, B11132002, B11132035
// Create Date : 2023/05/31
// Editor : B11130038, B11130005, B11132002, B11132035
// Update Date : 2023/05/31
// Description : This C++ program define the member functions of class "GmaeManager".

#include"GameManager.h"

// Intent: Default constructor.
// Pre: Input nothing.
// Post: The function returns nothing.
GameManager::GameManager() {
	player1 = new Player;
	player2 = new Player;

	// Set the opponent of two player.
	player1->setOpponent(player2);
	player2->setOpponent(player1);

	// Set the name of two player.
	player1->setPlayerName(myPlayer::player1);
	player2->setPlayerName(myPlayer::player2);
}

// Intent: Set the pokemon library.
// Pre: Input a string.
// Post: The function returns nothing.
void GameManager::setPokeMonLibrary(string fileName) {
	ifstream file(fileName);
	string text, name;
	vector<string> words;
	vector<string> type;

	// If the file is not exist, output error message.
	if (file.fail()) {
		cout << "Pokemon library's file don't exist";
		return;
	}

	while (1) {
		if (file.eof()) break;
		// Input the name.
		getline(file, name);

		// Input type.
		getline(file, text);

		// Split the text.
		split(text, words, ' ');

		// Input the type.
		for (int i = 0; i < stoi(words[0]); i++) {
			type.push_back(words[1 + i]);
		}
		words.clear();

		// Input other information.
		getline(file, text);

		// Split the text.
		split(text, words, ' ');

		// Create a pokemon.
		Pokemon* pokemon = new Pokemon(name, stoi(words[0]), stoi(words[1]), stoi(words[2]), stoi(words[3]), stoi(words[4]), stoi(words[5]));

		// Add the type to the pokemon.
		pokemon->addType(type);

		// Push the pokemon into the pokemon library.
		pokemonLibrary.push_back(pokemon);

		// Clear the input.
		words.clear();
		type.clear();
	}
}

// Intent: Set Game data.
// Pre: Input a string.
// Post: The function returns nothing.
void GameManager::setGameData(string fileName) {
	ifstream file(fileName);

	// Input how many pokemon does the player have.
	int num;
	file >> num;
	player1->setNumOfPokemon(num);

	for (int i = 0; i < num; i++) {
		// Input the pokemon name and it's skills.
		string pokemonName;
		int numOfSkills;
		file >> pokemonName >> numOfSkills;

		for (int j = 0; j < pokemonLibrary.size(); j++) {
			// Find the pokemon.
			if (pokemonName == pokemonLibrary[j]->name) {
				// Add the pokemon.
				player1->addPokemon(pokemonLibrary[j]);
				// Add the skills.
				for (int k = 0; k < numOfSkills; k++) {
					// Input the skills.
					string skill;
					file >> skill;

					for (int l = 0; l < moveLibrary.size(); l++) {
						// Find the skill.
						if (skill == moveLibrary[l]->skillName) {
							// Add the skill.
							player1->pokemon.back()->addSkill(moveLibrary[l]);
						}
					}
				}
			}
		}
	}

	// Input how many pokemon does the player have.
	file >> num;
	player2->setNumOfPokemon(num);

	for (int i = 0; i < num; i++) {
		// Input the pokemon name and it's skills.
		string pokemonName;
		int numOfSkills;
		file >> pokemonName >> numOfSkills;

		for (int j = 0; j < pokemonLibrary.size(); j++) {
			// Find the pokemon.
			if (pokemonName == pokemonLibrary[j]->name) {
				// Add the pokemon.
				player2->addPokemon(pokemonLibrary[j]);
				// Add the skills.
				for (int k = 0; k < numOfSkills; k++) {
					// Input the skills.
					string skill;
					file >> skill;

					for (int l = 0; l < moveLibrary.size(); l++) {
						// Find the skill.
						if (skill == moveLibrary[l]->skillName) {
							// Add the skill.
							player2->pokemon.back()->addSkill(moveLibrary[l]);
						}
					}
				}
			}
		}
	}

	// Close the file.
	file.close();

	// Set the current pokemon.
	player1->currentPokemon = player1->pokemon[0];
	player2->currentPokemon = player2->pokemon[0];

	// Set the game status.
	game = gameStatus::carry;
}

// Intent: Set moveing library.
// Pre: Input a string.
// Post: The function returns nothing.
void GameManager::setMoveLibrary(string fileName) {
	// Open the file.
	ifstream file(fileName);

	while (!file.eof()) {
		// Input
		string word;
		vector<string> words;

		getline(file, word);

		split(word, words, ' ');

		// Store the information of the skill.
		string skillName = words[0];
		type skillType;
		attackType PS = ((words[2] == "Physical") ? PHYSICAL : SPECIAL);
		int power = stoi(words[3]);
		int accuracy = stoi(words[4]);
		int PP = stoi(words[5]);
		Con con = NONE;

		for (int i = 0; i < numOfType; i++) {
			// Find the skill type.
			if (words[1] == typeLibrary[i]) {
				skillType = types[i];
			}
		}

		// If there is a con.
		if (words.size() == 7) {
			for (int i = 0; i < NONE; i++) {
				// Find the con.
				if (words[6] == conLib[i]) {
					con = cons[i];
				}
			}
		}

		// Create a skill.
		Skill* newSkill = new Skill(
			skillName,
			skillType,
			PS,
			power,
			accuracy,
			PP,
			con);

		// Push the skill into the library.
		moveLibrary.push_back(newSkill);
	}

	// Close the file.
	file.close();
}

// Intent: Set command file.
// Pre: Input a string.
// Post: The function returns nothing.
void GameManager::setCommandFile(string fileName) {
	// Open the file.
	ifstream file(fileName);

	string pokemonLibFileName;
	string moveLibFileName;
	string gameDataFileName;
	string mode;

	// Input file names.
	file >> pokemonLibFileName >> moveLibFileName >> gameDataFileName >> mode;

	// Setting
	setPokeMonLibrary(pokemonLibFileName);
	setMoveLibrary(moveLibFileName);
	setGameData(gameDataFileName);
	testMode = mode;

	string command;

	while (file >> command) {
		vector<string> cmds;
		cmds.push_back(command);

		int numOfCommand;

		// Count the number of commands
		if (command == "Battle" || command == "Pokemon") { numOfCommand = 2; }
		else if (command == "Bag") { numOfCommand = 3; }
		else { numOfCommand = 0; }

		// Input the command according to the number of command
		for (int i = 0; i < numOfCommand; i++) {
			string input;
			file >> input;
			cmds.push_back(input);
		}

		if (cmds.size() != 1) { carryOneTurn(cmds); }
		else {
			// Status
			if (command == "Status") {
				string myStatus = " ", opponentStatus = " ";

				// Add status.
				for (string i : player1->currentPokemon->pStatus) {
					myStatus += i + " ";
				}
				for (string i : player2->currentPokemon->pStatus) {
					opponentStatus += i + " ";
				}

				// Output the message.
				turnMessage.push_back("[Turn " + to_string(turnCount) + "] " +
					player1->currentPokemon->getName() + " " + to_string(player1->currentPokemon->getHp()) + myStatus +
					player2->currentPokemon->getName() + " " + to_string(player2->currentPokemon->getHp()) + opponentStatus);
			}
			// Check
			else if (command == "Check") {
				string skillString;

				// Add all the skills.
				for (int i = 0; i < player1->currentPokemon->skill.size(); i++) {
					skillString += player1->currentPokemon->skill[i]->getName() + " " + to_string(player1->currentPokemon->skill[i]->getPP());

					if (i != player1->currentPokemon->skill.size() - 1)skillString += " ";
				}

				// Output the message.
				turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + skillString);
			}
			// Run
			else if (command == "Run") { return; }
		}
	}
}

// Intent: Print turn message
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::printTurnMessage() {
	for (int i = 0; i < turnMessage.size(); i++) {
		// Output all the turn message.
		cout << turnMessage[i] << endl;
	}
}

// Intent: Combat.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::combat() {
	string player1Move, player1Order, player2Order, player1Bag;
	bool leave = false;

	// Clear the test mode.
	testMode = "";

	while (game == gameStatus::carry) {
		bool chosen = false;
		//player1
		while (!chosen) {
			// Print the information.
			system("CLS");
			printTurnMessage();
			showCombatImformation();

			this->player1->information();
			int choice = 0;
			cin >> choice;

			//battle
			if (choice == battle) {
				// Output the choises.
				for (int i = 0; i < this->player1->currentPokemon->skill.size(); i++) {
					cout << "[" << i << "] : ";
					this->player1->currentPokemon->skill[i]->outputSkill();
				}
				cout << "[4] : Back\n";

				while (!chosen) {
					cin >> choice;
					if (choice < 4 && choice >= 0) {
						// If the PP is 0.
						if (player1->currentPokemon->skill[choice]->getPP() == 0) {
							cout << "not enough PP, choose again : ";
							cin >> choice;
						}
						// choose the pokemon.
						else {
							player1Move = "Battle";
							player1Order = player1->currentPokemon->skill[choice]->getName();
							chosen = true;
							break;
						}
					}
					else if (choice == 4) { break; }
					else { cout << "invalid input, choose again : "; }
				}
			}

			//potion
			else if (choice == potion) {
				this->player1->potionInformation();
				leave = false;

				while (!leave) {
					cin >> choice;
					if (choice < 4 && choice >= 0) {
						player1Move = "Bag";
						player1Order = potionName[choice];

						while (!chosen) {
							system("CLS");
							showCombatImformation();

							// Show the choises.
							for (int i = 0; i < player1->pokemon.size(); i++) {
								cout << "[" << i << "] : " << player1->pokemon[i]->name << " "
									<< player1->pokemon[i]->hp << "/" << player1->pokemon[i]->maxHp
									<< endl;
							}
							cout << "[3]: Back" << endl;
							cout << "choose which pokemon to use potion : ";

							cin >> choice;

							if (choice < 3 && choice >= 0) {
								// If the hp is 0.
								if (player1->pokemon[choice]->getHp() == 0) {
									cout << "chosen pokemon has fainted, enteryour choice again : ";
									cin >> choice;
								}
								// choose the pokemon.
								else {
									player1Bag = player1->pokemon[choice]->name;
									chosen = true;
									break;
								}
							}
							else if (choice == 3) break;
							else {
								cout << "invalid input, choose aagain : ";
								cin >> choice;
							}
						}

						break;
					}
					else if (choice == 4) {
						leave = true;
					}
					else cout << "invalid input, choose again : ";
				}
			}

			//swap
			else if (choice == swapPokemon) {
				// Output the information.
				for (int i = 0; i < player1->pokemon.size(); i++) {
					cout << i << " : " << player1->pokemon[i]->name << " "
						<< player1->pokemon[i]->hp << "/" << player1->pokemon[i]->maxHp
						<< endl;
				}
				system("CLS");

				while (!chosen) {
					showCombatImformation();

					// Show the choises.
					for (int i = 0; i < player1->pokemon.size(); i++) {
						cout << "[" << i << "]: " << player1->pokemon[i]->name << " "
							<< player1->pokemon[i]->hp << "/" << player1->pokemon[i]->maxHp
							<< endl;
					}
					cout << "[3]: Back" << endl;

					cin >> choice;
					if (choice < 3 && choice >= 0) {
						// If the hp is 0.
						if (player1->pokemon[choice]->hp == 0) {
							system("CLS");
							cout << "chosen pokemon has fainted, enteryour choice again : ";
						}
						// choose the pokemon.
						else {
							player1Move = "Pokemon";
							player1Order = player1->pokemon[choice]->getName();
							chosen = true;
						}
					}
					else if (choice == 3) break;
					else cout << "invalid input, choose again : ";
				}
			}
		}

		//player 2 attack
		int skillNumber;

		while (1) {
			// Randomly choose a pokemon.
			skillNumber = rand() % 4;
			if (skillNumber < 4 && skillNumber >= 0 &&
				player2->currentPokemon->skill[skillNumber]->getPP() != 0) {
				player2Order = player2->currentPokemon->skill[skillNumber]->getName();
				break;
			}
		}

		// Create the cmds.
		vector<string> cmds;
		cmds.push_back(player1Move);
		cmds.push_back(player1Order);
		if (player1Move == "Bag") { cmds.push_back(player1Bag); }
		cmds.push_back(player2Order);

		// Carry one turn.
		carryOneTurn(cmds);
	}

	// Output the information if win or lose.
	if (game == gameStatus::player1Win) { cout << "You Win" << endl; }
	else { cout << "You Lose" << endl; }
}

// Intent: Carry one turn.
// Pre: Input a vector string.
// Post: The function returns nothing.
void GameManager::carryOneTurn(vector<string> cmds) {
	int skillNumber, skillNumber2;
	bool isChange = false;

	// Print the informaiton.
	system("CLS");
	printTurnMessage();
	showCombatImformation();

	if (cmds[0] == "Bag") {
		// Find the skill of player2's pokemon.
		for (int i = 0; i < player2->currentPokemon->skill.size(); i++) {
			if (cmds[3] == player2->currentPokemon->skill[i]->getName()) {
				skillNumber2 = i;
			}
		}

		// Find the name of the pokemon of player1's.
		int index = 0;
		for (int i = 0; i < player1->pokemon.size(); i++) {
			if (cmds[2] == player1->pokemon[i]->name) {
				index = i;
				break;
			}
		}

		string turnPotionName = "";
		//heal player1
		if (cmds[1] == potionName[0]) {
			player1->pokemon[index]->hp += 20;
			turnPotionName = "Potion";
		}
		else if (cmds[1] == potionName[1]) {
			player1->pokemon[index]->hp += 60;
			turnPotionName = "Super Potion";
		}
		else if (cmds[1] == potionName[2]) {
			player1->pokemon[index]->hp += 120;
			turnPotionName = "Hyper Potion";
		}
		else if (cmds[1] == potionName[3]) {
			player1->pokemon[index]->hp = player1->currentPokemon->maxHp;
			turnPotionName = "Max Potion";
		}

		// The hp should not exceed the maxHp.
		if (player1->pokemon[index]->hp > player1->pokemon[index]->maxHp) {
			player1->pokemon[index]->hp = player1->pokemon[index]->maxHp;
		}

		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] You used a " + turnPotionName + "!");
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + cmds[2] + " had its HP restored.");
	}
	else {
		// Find the skill of player2's pokemon.
		for (int i = 0; i < player2->currentPokemon->skill.size(); i++) {
			if (cmds[2] == player2->currentPokemon->skill[i]->getName()) {
				skillNumber2 = i;
			}
		}

		if (cmds[0] == "Pokemon") {
			for (int i = 0; i < player1->pokemon.size(); i++) {
				// Find the pokemon.
				if (player1->pokemon[i]->getName() == cmds[1]) {
					// print the message.
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + player1->currentPokemon->getName() + ", switch out!");

					// change the pokemon
					player1->currentPokemon = player1->pokemon[i];

					// print the message
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] Come back!");
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] Go! " + player1->currentPokemon->getName() + "!");

					break;
				}
			}
		}
	}

	// Get the speed.
	int player1Speed = player1->currentPokemon->getSpeed(), player2Speed = player2->currentPokemon->getSpeed();

	// Calculate the speed.
	if (player1->currentPokemon->pStatus.find("PAR") != player1->currentPokemon->pStatus.end()) player1Speed *= 0.5;
	if (player2->currentPokemon->pStatus.find("PAR") != player2->currentPokemon->pStatus.end()) player2Speed *= 0.5;

	// If player2 is faster.
	if (player1Speed < player2Speed) {
		attack(player2, player1, skillNumber2);

		// The hp should not be negative.
		if (player1->currentPokemon->getHp() < 0) {
			player1->currentPokemon->setHp(0);
		}
	}

	// If the pokemon of player1 is not dead.
	if (cmds[0] == "Battle" && player1->currentPokemon->getHp() != 0) {
		// Find the skill.
		for (int i = 0; i < player1->currentPokemon->skill.size(); i++) {
			if (cmds[1] == player1->currentPokemon->skill[i]->getName()) {
				skillNumber = i;
			}
		}

		// Attack player2.
		attack(player1, player2, skillNumber);

		// If the hp is 0.
		if (player2->currentPokemon->getHp() <= 0) {
			turnMessage.push_back("[Turn " + to_string(turnCount) + "] The opposing " + player2->currentPokemon->getName() + " fainted!");
		}
	}

	// If player1 is faster.
	if (player1Speed >= player2Speed && !isChange && player2->currentPokemon->getHp() > 0) {
		// Attack
		attack(player2, player1, skillNumber2);

		// the hp should not be negative.
		if (player1->currentPokemon->getHp() < 0) {
			player1->currentPokemon->setHp(0);
		}
	}

	// If the pokemon is fainted.
	if (player1->currentPokemon->getHp() <= 0) {
		player1->currentPokemon->setHp(0);
		faint();
	}

	// If the pokemon is fainted.
	if (player2->currentPokemon->getHp() <= 0) {
		player2->currentPokemon->setHp(0);

		// Find the pokemon and replace by the next pokemon if player2 still have pokemon, otherwise, player2 lose
		for (int i = 0; i < player2->pokemon.size(); i++) {
			if (player2->currentPokemon->getName() == player2->pokemon[i]->getName()) {
				// player2 still have pokemon
				if (i != player2->pokemon.size() - 1) {
					// replace by the next pokemon
					player2->currentPokemon = player2->pokemon[i + 1];

					isChange = true;
					break;
				}
				// player2 don't have pokemon
				else {
					// print the message.
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] You win");

					// Set the game status.
					game = gameStatus::player1Win;

					return;
				}
			}
		}
	}

	// Deal with the status.
	for (auto i : player1->currentPokemon->pStatus) {
		if (i == "BRN") {
			// calculate the hp
			player1->currentPokemon->changeHp(player1->currentPokemon->maxHp * -1.0 / 16);
			// output the message
			turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + player1->currentPokemon->getName() + " is hurt by its burn!");
		}
		else if (i == "PSN") {
			// calculate the hp
			player1->currentPokemon->changeHp(player1->currentPokemon->maxHp * -1.0 / 16);
			// output the message
			turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + player1->currentPokemon->getName() + " is hurt by its poisoning!");
		}
	}

	// Deal with the status.
	for (auto i : player2->currentPokemon->pStatus) {
		if (i == "BRN") {
			// calculate the hp
			player2->currentPokemon->changeHp(player2->currentPokemon->maxHp * -1.0 / 16);
			// output the message
			turnMessage.push_back("[Turn " + to_string(turnCount) + "] The opposing " + player2->currentPokemon->getName() + " is hurt by its burn!");
		}
		else if (i == "PSN") {
			// calculate the hp
			player2->currentPokemon->changeHp(player2->currentPokemon->maxHp * -1.0 / 16);
			// output the message
			turnMessage.push_back("[Turn " + to_string(turnCount) + "] The opposing " + player2->currentPokemon->getName() + " is hurt by its poisoning!");
		}
	}

	// If the pokemon is fainted.
	if (player1->currentPokemon->getHp() <= 0) {
		player1->currentPokemon->setHp(0);
		faint();
	}

	// If the pokemon is fainted.
	if (player2->currentPokemon->getHp() <= 0) {
		player2->currentPokemon->setHp(0);

		// Find the pokemon and replace by the next pokemon if player2 still have pokemon, otherwise, player2 lose
		for (int i = 0; i < player2->pokemon.size(); i++) {
			if (player2->currentPokemon->getName() == player2->pokemon[i]->getName()) {
				// player2 still have pokemon
				if (i != player2->pokemon.size() - 1) {
					// replace by the next pokemon
					player2->currentPokemon = player2->pokemon[i + 1];

					isChange = true;
					break;
				}
				// player2 don't have pokemon
				else {
					// print the message.
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] You win");

					// Set the game status.
					game = gameStatus::player1Win;

					return;
				}
			}
		}
	}

	// Increase the turn.
	turnCount += 1;

	// show the information.
	showCombatImformation();
}

// Intent: Show combat information.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::showCombatImformation() {
	string myStatus = " ", opponentStatus = " ";

	// Add status.
	for (string i : player1->currentPokemon->pStatus) {
		myStatus += i + " ";
	}
	for (string i : player2->currentPokemon->pStatus) {
		opponentStatus += i + " ";
	}

	// print the status.
	cout << this->player1->currentPokemon->name << " " << this->player1->currentPokemon->level << myStatus << endl;
	cout << this->player1->currentPokemon->hp << "/" << this->player1->currentPokemon->maxHp << endl;
	cout << endl;
	cout << this->player2->currentPokemon->name << " " << this->player2->currentPokemon->level << opponentStatus << endl;
	cout << this->player2->currentPokemon->hp << "/" << this->player2->currentPokemon->maxHp << endl;
}

// Intent: The pokemon is faint.
// Pre: Input nothing.
// Post: The function returns nothing.
void GameManager::faint() {
	// print out the message.
	system("CLS");
	printTurnMessage();
	showCombatImformation();

	int fainted = 0;
	for (int i = 0; i < player1->pokemon.size(); i++) {
		// if the pokemon is fainted, fainted++
		if (player1->pokemon[i]->getHp() <= 0) {
			fainted += 1;
		}
	}

	// if all the pokemon of player1 is fainted, player2 win.
	if (fainted == player1->pokemon.size()) {
		// Set the game status.
		game = gameStatus::player2Win;
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] You lose");
	}
	else {
		while (1) {
			bool isValid = false;
			int index;
			int choice;

			// Show the choises.
			for (int i = 0; i < player1->pokemon.size(); i++) {
				cout << "[" << i << "]: " << player1->pokemon[i]->name << " "
					<< player1->pokemon[i]->hp << "/" << player1->pokemon[i]->maxHp
					<< endl;
			}
			cout << "fainted, choose :";

			cin >> choice;

			if (choice < 3 && choice >= 0) {
				// if the choosen one is fainted.
				if (player1->pokemon[choice]->hp == 0) {
					cout << "pokemon fainted, choose another : " << endl;
				}
				// choose the pokemon.
				else {
					player1->currentPokemon = player1->pokemon[choice];
					turnMessage.push_back("[Turn " + to_string(turnCount) + "] Go! " + player1->currentPokemon->name + "!");
					break;
				}
			}
			else cout << "invalid input, choose again : ";
		}
	}
}

// Intent: Attack.
// Pre: Input attacker and defender and the index of skill.
// Post: The function returns nothing.
void GameManager::attack(Player* attacker, Player* defender, int skillNumber) {
	// Set the opponent.
	if (attacker->playerName == myPlayer::player1) { opponent = ""; }
	else { opponent = "The opposing "; }

	int num = rand() % 4;
	// if the pokemon is paralyzed
	if (attacker->currentPokemon->pStatus.find("PAR") != attacker->currentPokemon->pStatus.end() &&
		(testMode != "" || num == 0)) {
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + attacker->currentPokemon->getName() + " is paralyzed!");
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] It can't move!");
		return;
	}
	// Output the message.
	turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + attacker->currentPokemon->name + " used " + attacker->currentPokemon->skill[skillNumber]->getName() + "!");

	// Set the defender.
	if (defender->playerName == myPlayer::player1) { opponent = ""; }
	else { opponent = "The opposing "; }

	// Decrease the PP.
	attacker->currentPokemon->skill[skillNumber]->PP -= 1;

	// Calculate the damage.
	int damage = damageCal(attacker->currentPokemon, defender->currentPokemon, skillNumber);

	// Decrease the hp.
	defender->currentPokemon->changeHp(-1 * damage);
}

// Intent: Calculate damage.
// Pre: Input attacker and defender and the index of the skill.
// Post: The function returns a float.
float GameManager::damageCal(Pokemon* attacker, Pokemon* defender, int skillOrder) {
	vector<Skill*> pSkill = attacker->getSkill();

	int accuracy = rand() % 100;
	// if the random accuracy > accuracy.
	if (accuracy >= pSkill[skillOrder]->getAcc() && testMode == "") {
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + defender->getName() + " avoided the attack!");
		return 0;
	}

	int result = 0;

	// Calculate the power
	result *= pSkill[skillOrder]->getPower();

	// Calculate the attack
	if (pSkill[skillOrder]->getPS() == PHYSICAL) {
		result = int(((float(2 * attacker->getLevel()) + 10) / 250) * pSkill[skillOrder]->getPower() * attacker->getPhysicalAttack() / defender->getDefense());
	}
	else if (pSkill[skillOrder]->getPS() == SPECIAL) {
		result = int(((float(2 * attacker->getLevel()) + 10) / 250) * pSkill[skillOrder]->getPower() * attacker->getSpecialAttack() / defender->getSpecialDefense());
	}

	// +2
	result += 2;

	int critical = rand() % 100;
	float criticalHit = 1;

	// Calculate the critical hit
	if (critical < 10 && testMode == "") {
		criticalHit = 2;
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] A critical hit!");
	}

	float STAB = 1;

	// Calculate the STAB
	for (int i = 0; i < attacker->getType().size(); i++) {
		if (pSkill[skillOrder]->getType() == attacker->getType()[i]) {
			STAB = 1.5;
		}
	}

	float typeEffect = 1;

	// Calculate the type effect.
	for (int i = 0; i < defender->getType().size(); i++) {
		typeEffect *= typeCheck(pSkill[skillOrder]->getType(), defender->getType()[i]);
	}

	// Output the message.
	if (typeEffect >= 2) turnMessage.push_back("[Turn " + to_string(turnCount) + "] It's super effective!");
	else if (typeEffect <= 0.5) turnMessage.push_back("[Turn " + to_string(turnCount) + "] It's not very effective...");
	else if (typeEffect == 0) turnMessage.push_back("[Turn " + to_string(turnCount) + "] It's not effective!\n");

	// Get the con.
	Con attackCon = attacker->skill[skillOrder]->getCon();

	// PAR
	if (attackCon == PAR) {
		// Add the con.
		defender->pStatus.insert(conLib[PAR]);
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + defender->getName() + " is paralyzed, so it may be unable to move!");
	}
	// BRN
	else if (attackCon == BRN) {
		// Add the con.
		defender->pStatus.insert(conLib[BRN]);
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + defender->getName() + " was burned!");
	}
	// PSN
	else if (attackCon == PSN) {
		// Add the con.
		defender->pStatus.insert(conLib[PSN]);
		// Output the message.
		turnMessage.push_back("[Turn " + to_string(turnCount) + "] " + opponent + defender->getName() + " was poisoned!");
	}

	// if the power is 0, return 0.
	if (pSkill[skillOrder]->getPower() == 0) return 0;

	// return the answer.
	return result * criticalHit * typeEffect * STAB;
}

// Intent: Check the type.
// Pre: Input attack and defence.
// Post: The function returns a float.
float GameManager::typeCheck(int atk, int def) {
	//normal
	if (atk == normal) {
		if (def == rock || def == steel) { return 0.5; }
		else if (def == ghost) { return 0; }
		else { return 1; }
	}

	//fire
	if (atk == fire) {
		if (def == fire || def == water || def == rock || def == dragon) { return 0.5; }
		else if (def == grass || def == ice || def == bug || def == steel) { return 2; }
		else { return 1; }
	}

	//water
	if (atk == water) {
		if (def == grass || def == water || def == dragon) { return 0.5; }
		else if (def == fire || def == ground || def == rock) { return 2; }
		else { return 1; }
	}

	//eletric
	if (atk == electric) {
		if (def == electric || def == grass || def == dragon) { return 0.5; }
		else if (def == water || def == flying) { return 2; }
		else if (def == ground) { return 0; }
		else { return 1; }
	}

	//grass
	if (atk == grass) {
		if (def == fire || def == grass || def == poison || def == dragon || def == flying || def == bug || def == dragon) { return 0.5; }
		else if (def == water || def == ground || def == rock) { return 2; }
		else { return 1; }
	}

	//ice
	if (atk == ice) {
		if (def == fire || def == water || def == ice || def == steel) { return 0.5; }
		else if (def == grass || def == ground || def == flying || def == dragon) { return 2; }
		else { return 1; }
	}

	//fighting
	if (atk == fighting) {
		if (def == poison || def == flying || def == psychic || def == bug || def == fairy) { return 0.5; }
		else if (def == normal || def == ice || def == rock || def == steel || def == dark) { return 2; }
		else if (def == ghost) { return 0; }
		else { return 1; }
	}

	//poison
	if (atk == poison) {
		if (def == poison || def == ground || def == rock || def == ghost) { return 0.5; }
		else if (def == grass || def == fairy) { return 2; }
		else if (def == steel) { return 0; }
		else { return 1; }
	}

	//ground
	if (atk == ground) {
		if (def == grass || def == bug) { return 0.5; }
		else if (def == fire || def == electric || def == poison || def == rock || def == steel) { return 2; }
		else if (def == flying) { return 0; }
		else { return 1; }
	}

	//flying
	if (atk == flying) {
		if (def == electric || def == rock || def == steel) { return 0.5; }
		else if (def == grass || def == fighting || def == bug) { return 2; }
		else { return 1; }
	}

	//psychic
	if (atk == psychic) {
		if (def == fighting || def == poison) { return 0.5; }
		else if (def == psychic || def == steel) { return 2; }
		else if (def == dark) { return 0; }
		else { return 1; }
	}

	//bug
	if (atk == bug) {
		if (def == fire || def == fighting || def == poison || def == flying || def == ghost || def == steel || def == fairy) { return 0.5; }
		else if (def == grass || def == psychic || def == dark) { return 2; }
		else { return 1; }
	}

	//rock
	if (atk == rock) {
		if (def == fighting || def == ground || def == steel) { return 0.5; }
		else if (def == fire || def == ice || def == flying || def == bug) { return 2; }
		else { return 1; }
	}

	//ghost
	if (atk == ghost) {
		if (def == dark) { return 0.5; }
		else if (def == psychic || def == ghost) { return 2; }
		else if (def == normal) { return 0; }
		else { return 1; }
	}

	//dragon
	if (atk == dragon) {
		if (def == dragon) { return 0.5; }
		else if (def == steel) { return 2; }
		else if (def == fairy) { return 0; }
		else { return 1; }
	}

	//dark
	if (atk == dark) {
		if (def == fighting || def == dark || def == fairy) { return 0.5; }
		else if (def == psychic || def == rock) { return 2; }
		else { return 1; }
	}

	//steel
	if (atk == steel) {
		if (def == fire || def == water || def == electric || def == steel) { return 0.5; }
		else if (def == ice || def == rock || def == fairy) { return 2; }
		else { return 1; }
	}

	//fairy
	if (atk == fairy) {
		if (def == fire || def == poison || def == steel) { return 0.5; }
		else if (def == fighting || def == dragon || def == dark) { return 2; }
		else { return 1; }
	}
}