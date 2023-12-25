// File: MineSweeper.cpp
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005, B11130038
// Update Date : 2023/04/12
// Description : This C++ program define the member functions of class "MineSweeper".

#include "MineSweeper.h"

// Constructor
MineSweeper::MineSweeper(QWidget* parent)
	: QMainWindow(parent)
{
	//-------------------set and modify the ui---------------------
	// Using the setupUi function define in ui_MineSweeper.h to set up the ui.
	ui.setupUi(this);

	// Create a QGridLayout gMap in ui.boardWigit.
	gMap = new QGridLayout(ui.boardWigit);

	//Set the game state at status bar and resize the label.
	statusBarGameState = new QLabel(ui.statusBar);
	statusBarGameState->setText("GameState : Standby");
	statusBarGameState->setMinimumSize(QSize(230, 30));

	// Set the style of status bar, load button and start game button.
	ui.statusBar->setStyleSheet("background-color:rgb(125,125,125);color:white;");
	ui.loadButton->setStyleSheet("background-color:rgb(170,170,170);");
	ui.startGameButton->setStyleSheet("background-color:rgb(170,170,170);");

	// Fixed the row and column spin box in the random bomb count page.
	ui.randomCountRowSpinBox->setMinimum(MIN_WIDTH);
	ui.randomCountRowSpinBox->setMaximum(MAX_WIDTH);
	ui.randomCountColSpinBox->setMinimum(MIN_WIDTH);
	ui.randomCountColSpinBox->setMaximum(MAX_WIDTH);

	// Set the lowerbound and upperbound of bombs spin box in the random bomb count page.
	ui.numOfBombsSpinBox->setMinimum(0);
	ui.numOfBombsSpinBox->setMaximum(ui.randomCountRowSpinBox->value() * ui.randomCountColSpinBox->value());

	// Fixed the row and column spin box in the random bomb rate page.
	ui.randomRateRowSpinBox->setMinimum(MIN_WIDTH);
	ui.randomRateRowSpinBox->setMaximum(MAX_WIDTH);
	ui.randomRateColSpinBox->setMinimum(MIN_WIDTH);
	ui.randomRateColSpinBox->setMaximum(MAX_WIDTH);

	// Connect buttons to the corresponding function.
	connect(ui.actionGameBoard, &QAction::triggered, this, &MineSweeper::printGameBoardActionTriggered);
	connect(ui.actionGameAnswer, &QAction::triggered, this, &MineSweeper::printGameAnswerActionTriggered);
	connect(ui.actionGameState, &QAction::triggered, this, &MineSweeper::printGameStateActionTriggered);
	connect(ui.actionBombCount, &QAction::triggered, this, &MineSweeper::printBombCountActionTriggered);
	connect(ui.actionFlagCount, &QAction::triggered, this, &MineSweeper::printFlagCountActionTriggered);
	connect(ui.actionOpenBlankCount, &QAction::triggered, this, &MineSweeper::printOpenBlankCountActionTriggered);
	connect(ui.actionRemainBlankCount, &QAction::triggered, this, &MineSweeper::printRemainBlankCountActionTriggered);
	connect(ui.loadButton, &QPushButton::clicked, this, &MineSweeper::loadButtonClicked);
	connect(ui.startGameButton, &QPushButton::clicked, this, &MineSweeper::startGameButtonClicked);
	//-------------------------------------------------------------
}

// Intent: Print game board when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printGameBoardActionTriggered() {
	cout << "<Print GameBoard> : \n";

	// If cmd is GameBoard and the board has load, print out the game board.
	if (gBoard.hasLoad) {
		// Print out the game board.
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				cout << gBoard.map[i][j] << " ";
			}
			cout << endl;
		}
	}
}

// Intent: Print game answer when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printGameAnswerActionTriggered() {
	cout << "<Print GameAnswer> : \n";

	// If the board has load, print out the game answer.
	if (gBoard.hasLoad) {
		// Print out game answer.
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				cout << gBoard.mapAns[i][j] << " ";
			}
			cout << endl;
		}
	}
}

// Intent: Print game state when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printGameStateActionTriggered() {
	cout << "<Print GameState> : ";

	// Print out game state.
	if (gBoard.state == Standby) { cout << "Standby\n"; }
	if (gBoard.state == Playing) { cout << "Playing\n"; }
	if (gBoard.state == GameOver) { cout << "GameOver\n"; }
}

// Intent: Print bomb count when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printBombCountActionTriggered() {
	cout << "<Print BombCount> : ";

	// If the state is not Standby, print out the bomb count.
	if (gBoard.state != Standby) {
		cout << gBoard.getBombCount();
	}
	cout << endl;
}

// Intent: Print flag count when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printFlagCountActionTriggered() {
	cout << "<Print FlagCount> : ";

	// If the state is not Standby, print out the flag count.
	if (gBoard.state != Standby) {
		cout << gBoard.getFlagCount();
	}
	cout << endl;
}

// Intent: Print open blank count when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printOpenBlankCountActionTriggered() {
	cout << "<Print OpenBlankCount> : ";

	// If the state is not Standby, print out the open blank count.
	if (gBoard.state != Standby) {
		cout << gBoard.getOpenBlankCount();
	}
	cout << endl;
}

// Intent: Print remain blank count when the action triggered.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::printRemainBlankCountActionTriggered() {
	cout << "<Print RemainBlankCount> : ";

	// If the state is not Standby, print out the remain blank count count.
	if (gBoard.state != Standby) {
		cout << gBoard.getRemainBlankCount();
	}
	cout << endl;
}

// Intent: Load the map when the load button clicked.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::loadButtonClicked() {
	gBoard.Board::Board();

	bool success = false;

	// If the load mode is Board File.
	if (ui.loadModeComboBox->currentIndex() == 0) {
		string path = ui.boardFilePathLineEdit->text().toLocal8Bit();

		cout << "<Load BoardFile " << path << "> : ";

		// Open the file.
		ifstream file;
		file.open(path);

		// If fail to open, the loading is not success.
		success = !file.fail();

		// The game state must be Standby when clicking the load button.
		success = success && gBoard.state == Standby;

		// If success to open the file.
		if (success) {
			int row, col;

			// File input row and col.
			file >> row >> col;

			// Set board's row and col.
			gBoard.setRow(row);
			gBoard.setCol(col);

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
							gBoard.mapAns[i][j] = '0';
						}
						// Otherwise, fill in the icon of bomb and increase BombCount.
						else if (rows[j] == BOMB) {
							gBoard.mapAns[i][j] = BOMB;
							gBoard.setBombCount(gBoard.getBombCount() + 1);
						}
					}
				}
				// If the coordinate is bomb, increase the number of surrounding coordinate.
				for (int i = 0; i < row; i++) {
					for (int j = 0; j < col; j++) {
						if (gBoard.mapAns[i][j] == BOMB) {
							if (IS_VALID(i - 1, j - 1) && gBoard.mapAns[i - 1][j - 1] != BOMB) { gBoard.mapAns[i - 1][j - 1]++; }
							if (IS_VALID(i - 1, j/**/) && gBoard.mapAns[i - 1][j/**/] != BOMB) { gBoard.mapAns[i - 1][j/**/]++; }
							if (IS_VALID(i - 1, j + 1) && gBoard.mapAns[i - 1][j + 1] != BOMB) { gBoard.mapAns[i - 1][j + 1]++; }
							if (IS_VALID(i/**/, j - 1) && gBoard.mapAns[i/**/][j - 1] != BOMB) { gBoard.mapAns[i/**/][j - 1]++; }
							if (IS_VALID(i/**/, j + 1) && gBoard.mapAns[i/**/][j + 1] != BOMB) { gBoard.mapAns[i/**/][j + 1]++; }
							if (IS_VALID(i + 1, j - 1) && gBoard.mapAns[i + 1][j - 1] != BOMB) { gBoard.mapAns[i + 1][j - 1]++; }
							if (IS_VALID(i + 1, j/**/) && gBoard.mapAns[i + 1][j/**/] != BOMB) { gBoard.mapAns[i + 1][j/**/]++; }
							if (IS_VALID(i + 1, j + 1) && gBoard.mapAns[i + 1][j + 1] != BOMB) { gBoard.mapAns[i + 1][j + 1]++; }
						}
					}
				}
			}
			// Close the file.
			file.close();
		}
	}

	// If the load mode is RandomCount.
	else if (ui.loadModeComboBox->currentIndex() == 1) {
		// Input row and col.
		gBoard.setRow(ui.randomCountRowSpinBox->value());
		gBoard.setCol(ui.randomCountColSpinBox->value());

		// Input the number of bombs.
		int upperBound = ui.numOfBombsSpinBox->value();
		int row = gBoard.getRow(), col = gBoard.getCol();

		cout << "<Load RandomCount " << row << " " << col << " " << upperBound << "> : ";

		// Check if row and col are valid.
		success = (MIN_WIDTH <= row && row <= MAX_WIDTH && MIN_WIDTH <= col && col <= MAX_WIDTH);
		// Check if the upper bound is valid.
		success = success && (0 <= upperBound && upperBound <= row * col);
		// Check if the game state is Standby.
		success = success && gBoard.state == Standby;

		if (success) {

			// Set a seed.
			srand(time(NULL));

			// Fill the board with 0.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					gBoard.mapAns[i][j] = '0';
				}
			}

			// Fill in the bomb.
			while (gBoard.getBombCount() != upperBound) {
				int randRow = rand() % row, randCol = rand() % col;
				if (gBoard.mapAns[randRow][randCol] != BOMB) {
					gBoard.mapAns[randRow][randCol] = BOMB;
					gBoard.setBombCount(gBoard.getBombCount() + 1);
				}
			}

			// If the coordinate is bomb, increase the number of surrounding coordinate.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (gBoard.mapAns[i][j] == BOMB) {
						if (IS_VALID(i - 1, j - 1) && gBoard.mapAns[i - 1][j - 1] != BOMB) { gBoard.mapAns[i - 1][j - 1]++; }
						if (IS_VALID(i - 1, j/**/) && gBoard.mapAns[i - 1][j/**/] != BOMB) { gBoard.mapAns[i - 1][j/**/]++; }
						if (IS_VALID(i - 1, j + 1) && gBoard.mapAns[i - 1][j + 1] != BOMB) { gBoard.mapAns[i - 1][j + 1]++; }
						if (IS_VALID(i/**/, j - 1) && gBoard.mapAns[i/**/][j - 1] != BOMB) { gBoard.mapAns[i/**/][j - 1]++; }
						if (IS_VALID(i/**/, j + 1) && gBoard.mapAns[i/**/][j + 1] != BOMB) { gBoard.mapAns[i/**/][j + 1]++; }
						if (IS_VALID(i + 1, j - 1) && gBoard.mapAns[i + 1][j - 1] != BOMB) { gBoard.mapAns[i + 1][j - 1]++; }
						if (IS_VALID(i + 1, j/**/) && gBoard.mapAns[i + 1][j/**/] != BOMB) { gBoard.mapAns[i + 1][j/**/]++; }
						if (IS_VALID(i + 1, j + 1) && gBoard.mapAns[i + 1][j + 1] != BOMB) { gBoard.mapAns[i + 1][j + 1]++; }
					}
				}
			}
		}
	}

	// If the load mode is RandomRate.
	else {
		// Input row and col.
		gBoard.setRow(ui.randomRateRowSpinBox->value());
		gBoard.setCol(ui.randomRateColSpinBox->value());

		// Input the probability.
		double probability = ui.bombSpawnRateDoubleSpinBox->value();
		int row = gBoard.getRow();
		int col = gBoard.getCol();

		cout << "<Load RandomRate " << row << " " << col << " " << probability << "> : ";

		// Check if row and col are valid.
		success = (MIN_WIDTH <= row && row <= MAX_WIDTH && MIN_WIDTH <= col && col <= MAX_WIDTH);
		// Check if probability is valid.
		success = success && (0 <= probability && probability <= 1);
		// Check if the game state is Standby.
		success = success && gBoard.state == Standby;

		if (success) {

			// Set a seed.
			srand(time(NULL));

			probability *= 100;

			// Fill int the bomb.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (probability > rand() % 100) {
						gBoard.mapAns[i][j] = BOMB;
						gBoard.setBombCount(gBoard.getBombCount() + 1);
					}
					else {
						gBoard.mapAns[i][j] = '0';
					}
				}
			}

			// If the coordinate is bomb, increase the number of surrounding coordinate.
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if (gBoard.mapAns[i][j] == BOMB) {
						if (IS_VALID(i - 1, j - 1) && gBoard.mapAns[i - 1][j - 1] != BOMB) { gBoard.mapAns[i - 1][j - 1]++; }
						if (IS_VALID(i - 1, j/**/) && gBoard.mapAns[i - 1][j/**/] != BOMB) { gBoard.mapAns[i - 1][j/**/]++; }
						if (IS_VALID(i - 1, j + 1) && gBoard.mapAns[i - 1][j + 1] != BOMB) { gBoard.mapAns[i - 1][j + 1]++; }
						if (IS_VALID(i/**/, j - 1) && gBoard.mapAns[i/**/][j - 1] != BOMB) { gBoard.mapAns[i/**/][j - 1]++; }
						if (IS_VALID(i/**/, j + 1) && gBoard.mapAns[i/**/][j + 1] != BOMB) { gBoard.mapAns[i/**/][j + 1]++; }
						if (IS_VALID(i + 1, j - 1) && gBoard.mapAns[i + 1][j - 1] != BOMB) { gBoard.mapAns[i + 1][j - 1]++; }
						if (IS_VALID(i + 1, j/**/) && gBoard.mapAns[i + 1][j/**/] != BOMB) { gBoard.mapAns[i + 1][j/**/]++; }
						if (IS_VALID(i + 1, j + 1) && gBoard.mapAns[i + 1][j + 1] != BOMB) { gBoard.mapAns[i + 1][j + 1]++; }
					}
				}
			}
		}
	}

	// After loading the board of answer, set the game board and compute RemainBlankCount.
	if (success) {
		// Fill the game board with the icon of blank.
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				gBoard.map[i][j] = BLANK;
			}
		}

		// Compute RemainBlankCount.
		gBoard.setRemainBlankCount(gBoard.getRow() * gBoard.getCol() - gBoard.getBombCount());

		// Record it has load the board.
		gBoard.hasLoad = true;

		// Print out message.
		cout << "Success\n";
	}

	// If not success to loading, print out Failed.
	else { cout << "Failed\n"; }
}

// Intent: To start the game, change the page and create the button in the gui when the start game button clicked.
// Pre: Input nothing.
// Post: The function returns nothing.
void MineSweeper::startGameButtonClicked() {
	//----------------------play the music-------------------------
	// Set media by file path.
	musicPlayer->setMedia(QUrl::fromLocalFile("./sounds/Road to Dazir.wav"));

	// Set player's volume.
	musicPlayer->setVolume(50);

	// Play the music.
	musicPlayer->play();
	//-------------------------------------------------------------

	// Set maximum size
	ui.centralWidget->setMaximumSize(QSize(12777215, 12777215));

	cout << "<StartGame> : ";

	// If has load the map.
	if (gBoard.hasLoad) {
		cout << "Success\n";

		// Set the game state.
		gBoard.state = Playing;

		// Set the game state at the bottom.
		statusBarGameState->setText("GameState : Playing");

		// Display the blank count, remain blank count, bomb count, flag count.
		ui.openBlankCountLcdNumber->display(gBoard.getOpenBlankCount());
		ui.remainBlankCountLcdNumber->display(gBoard.getRemainBlankCount());
		ui.bombCountLcdNumber->display(gBoard.getBombCount());
		ui.flagCountLcdNumber->display(gBoard.getFlagCount());

		// Fix the board widget.
		ui.boardWigit->setMaximumSize(QSize(BUTTON_WIDTH * gBoard.getCol(), BUTTON_WIDTH * gBoard.getRow()));
		ui.boardWigit->setMinimumSize(QSize(BUTTON_WIDTH * gBoard.getCol(), BUTTON_WIDTH * gBoard.getRow()));

		// Maintain the layout gMap set the layout no size between buttons.
		gMap->setSpacing(0);
		gMap->setSizeConstraint(QLayout::SetMinimumSize);

		// Put the button in the layout gMap.
		for (int i = 0; i < gBoard.getRow(); i++) {
			// Push 1d dynamic array.
			QVector<QPushButton*> tmp;
			field.push_back(tmp);
			for (int j = 0; j < gBoard.getCol(); j++) {
				// Set the button.
				QPushButton* button = new QPushButton(this);

				// Set the button's icon.
				button->setIcon(QIcon("./images/Minesweeper_unopened_square"));

				// Set the button's icon's size.
				button->setIconSize(QSize(BUTTON_WIDTH, BUTTON_WIDTH));

				// Fix the button's size.
				button->setMinimumSize(QSize(BUTTON_WIDTH, BUTTON_WIDTH));
				button->setMaximumSize(QSize(BUTTON_WIDTH, BUTTON_WIDTH));

				// Put the button in the layout gMap.
				gMap->addWidget(button, i, j);

				// Set gMap's minimum height and width.
				gMap->setRowMinimumHeight(i, BUTTON_WIDTH);
				gMap->setColumnMinimumWidth(j, BUTTON_WIDTH);

				// Store button in 2d dynamic array.
				field[i].push_back(button);
			}
		}

		// Turn to game pages.
		ui.pages->setCurrentIndex(1);

		// Set ui minimum size and adjust the size.
		this->minimumSizeHint();
		this->adjustSize();

		// Connect the button to the function when press or click.
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				// Connect the button to the function when press.
				connect(field[i][j], &QPushButton::pressed, this, [=]() {
					// If press the button, change the icon.
					if (gBoard.map[i][j] == BLANK) {
						field[i][j]->setIcon(QIcon("./images/Minesweeper_0"));
					}
					});

				// Connect the button to the leftClick function when click.
				connect(field[i][j], &QPushButton::released, this, [=]() {
					leftClick(field[i][j], i, j);
					});
			}
		}
	}
	// If the cmd is invalid, print Failed.
	else { cout << "Failed\n"; }
}

// Intent: Show the icon of specific button.
// Pre: The variable row and col must have a value.
// Post: The function returns nothing.
void MineSweeper::showIcon(int row, int col) {
	// Get symbols in the map.
	char symbol = gBoard.map[row][col];

	// Judge the symbol and set icon.
	if (symbol == BLANK) { field[row][col]->setIcon(QIcon("./images/Minesweeper_unopened_square")); }
	else if (symbol == '0') { field[row][col]->setIcon(QIcon("./images/Minesweeper_0")); }
	else if (symbol == '1') { field[row][col]->setIcon(QIcon("./images/Minesweeper_1")); }
	else if (symbol == '2') { field[row][col]->setIcon(QIcon("./images/Minesweeper_2")); }
	else if (symbol == '3') { field[row][col]->setIcon(QIcon("./images/Minesweeper_3")); }
	else if (symbol == '4') { field[row][col]->setIcon(QIcon("./images/Minesweeper_4")); }
	else if (symbol == '5') { field[row][col]->setIcon(QIcon("./images/Minesweeper_5")); }
	else if (symbol == '6') { field[row][col]->setIcon(QIcon("./images/Minesweeper_6")); }
	else if (symbol == '7') { field[row][col]->setIcon(QIcon("./images/Minesweeper_7")); }
	else if (symbol == '8') { field[row][col]->setIcon(QIcon("./images/Minesweeper_8")); }
	else if (symbol == BOMB) { field[row][col]->setIcon(QIcon("./images/Minesweeper_answer_bomb")); }
	else if (symbol == FLAG) { field[row][col]->setIcon(QIcon("./images/Minesweeper_flag")); }
	else if (symbol == QUESTION_MARK) { field[row][col]->setIcon(QIcon("./images/Minesweeper_questionmark")); }
}

// Intent: To set the button enable to click, show icon and diffuse when the button in the game left clicked.
// Pre: The variable row and col and the reference of QPushButton button must have a value.
// Post: The function returns nothing.
void MineSweeper::leftClick(QPushButton* button, int row, int col) {
	// If the button is not blank, leave the function.
	if (gBoard.map[row][col] != BLANK) {
		cout << "<LeftClick " << row << " " << col << "> : Failed\n";
		return;
	}

	cout << "<LeftClick " << row << " " << col << "> : Success\n";

	// If the bomb was clicked, game over, and print out the message.
	if (gBoard.mapAns[row][col] == BOMB) {
		//----------------------play the music-------------------------
		// Create a player
		QMediaPlayer* player = new QMediaPlayer;

		// Set media by url
		player->setMedia(QUrl::fromLocalFile("./sounds/BombExplosion.wav"));

		// Set player's volume
		player->setVolume(80);

		// Play the music
		player->play();
		//-------------------------------------------------------------

		// Set game state
		gBoard.state = GameOver;

		// Show the answer
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				gBoard.map[i][j] = gBoard.mapAns[i][j];
				showIcon(i, j);
			}
		}

		// Set icon of the exploded bomb.
		button->setIcon(QIcon("./images/Minesweeper_bomb"));

		// Set the game state at the status bar.
		statusBarGameState->setText("GameState : GameOver");

		cout << "You lose the game\n";

		// Stop playing music
		musicPlayer->stop();

		//----------------------QMessageBox----------------------------
		// Create a message box
		QMessageBox msgBox;

		// Set window title and text in the message box
		msgBox.setWindowTitle("Game Over!");
		msgBox.setInformativeText("You lose the game");

		// Set standard and default button in the message box
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);

		// Set button in the message box
		msgBox.setButtonText(QMessageBox::Yes, "Replay");
		msgBox.setButtonText(QMessageBox::No, "Quit");

		int screenWidth = ui.centralWidget->width() + ui.pages->width() + ui.gameBoard->width() + ui.boardWigit->width();
		int screenHeight = ui.centralWidget->height() + ui.pages->height() + ui.gameBoard->height();
		int x = (screenWidth - msgBox.width()) / 2;
		int y = (screenHeight - msgBox.height()) / 2;
		msgBox.setGeometry(x, y, msgBox.width(), msgBox.height());

		// Get the value when the message box finish
		int reply = msgBox.exec();
		//-------------------------------------------------------------

		if (reply == QMessageBox::Yes) {
			// Close the message box
			msgBox.close();

			cout << "<Replay> : Success\n";

			// Delete button in the map from the widget gMap
			for (int i = 0; i < gBoard.getRow(); i++) {
				for (int j = 0; j < gBoard.getCol(); j++) {
					gMap->removeWidget(field[i][j]);
					delete field[i][j];
				}
			}

			// Delete the widgit gMap
			delete gMap;

			// Create the new widgit gMap
			gMap = new QGridLayout(ui.boardWigit);

			// Clear the button
			field.clear();

			// Reconstruct the board
			gBoard.Board::Board();

			// Set the game state at the status bar.
			statusBarGameState->setText("GameState : Standby");

			// Set maximum size
			ui.centralWidget->setMaximumSize(QSize(686, 440));

			// Set ui minimum size and adjust the size
			this->minimumSizeHint();
			this->adjustSize();

			// Turn to start game page
			ui.pages->setCurrentIndex(0);

			return;
		}
		else {
			cout << "<Quit> : Success\n";

			// End the gui
			QCoreApplication::quit();
		}
	}

	// If a 0 was clicked, diffuse.
	else if (gBoard.mapAns[row][col] == '0') {
		//----------------------play the music-------------------------
		// Create a player
		QMediaPlayer* player = new QMediaPlayer;

		// Set media by url
		player->setMedia(QUrl::fromLocalFile("./sounds/OpenCell.wav"));

		// Set player's volume
		player->setVolume(80);

		// Play the music
		player->play();
		//-------------------------------------------------------------

		// Diffuse the surrounding coordinates
		diffuse(row, col);
	}

	// If a number was clicked, open it and change the record.
	else {
		//----------------------play the music-------------------------
		// Create a player
		QMediaPlayer* player = new QMediaPlayer;

		// Set media by url
		player->setMedia(QUrl::fromLocalFile("./sounds/OpenCell.wav"));

		// Set player's volume
		player->setVolume(80);

		// Play the music
		player->play();
		//-------------------------------------------------------------

		// Show the answer
		gBoard.map[row][col] = gBoard.mapAns[row][col];

		// Update the open blank count, remain blank count, and display
		gBoard.setOpenBlankCount(gBoard.getOpenBlankCount() + 1);
		gBoard.setRemainBlankCount(gBoard.getRemainBlankCount() - 1);
		ui.openBlankCountLcdNumber->display(gBoard.getOpenBlankCount());
		ui.remainBlankCountLcdNumber->display(gBoard.getRemainBlankCount());

		// Show icon
		showIcon(row, col);
	}

	// Check if the player won the game after clicking.
	if (gBoard.getRemainBlankCount() == 0) {
		//Set the game state
		gBoard.state = GameOver;

		//Set the game state at the status bar.
		statusBarGameState->setText("GameState : GameOver");

		// Show the answer
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				gBoard.map[i][j] = gBoard.mapAns[i][j];
				showIcon(i, j);
			}
		}

		cout << "You win the game\n";

		// Stop playing music
		musicPlayer->stop();

		//----------------------QMessageBox----------------------------
		// Create a message box
		QMessageBox msgBox;
		msgBox.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
		// Set window title and text in the message box
		msgBox.setWindowTitle("Game Over!");
		msgBox.setInformativeText("You win the game");

		// Set standard and default button in the message box
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);

		// Set button in the message box
		msgBox.setButtonText(QMessageBox::Yes, "Replay");
		msgBox.setButtonText(QMessageBox::No, "Quit");
		msgBox.setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

		int screenWidth = ui.centralWidget->width() + ui.pages->width() + ui.gameBoard->width() + ui.boardWigit->width();
		int screenHeight = ui.centralWidget->height() + ui.pages->height() + ui.gameBoard->height();
		int x = (screenWidth - msgBox.width()) / 2;
		int y = (screenHeight - msgBox.height()) / 2;
		msgBox.setGeometry(x, y, msgBox.width(), msgBox.height());

		// Get the value when the message box finish
		int reply = msgBox.exec();
		//-------------------------------------------------------------

		if (reply == QMessageBox::Yes) {
			// Close the message box
			msgBox.close();

			cout << "<Replay> : Success\n";

			// Delete button in the map from the widget gMap
			for (int i = 0; i < gBoard.getRow(); i++) {
				for (int j = 0; j < gBoard.getCol(); j++) {
					gMap->removeWidget(field[i][j]);
					delete field[i][j];
				}
			}

			// Delete the widgit gMap
			delete gMap;

			// Create the new widgit gMap
			gMap = new QGridLayout(ui.boardWigit);

			// Clear the button
			field.clear();

			// Reconstruct the board
			gBoard.Board::Board();

			// Set the game state at the status bar.
			statusBarGameState->setText("GameState : Standby");

			// Set maximum size
			ui.centralWidget->setMaximumSize(QSize(686, 440));

			// Set ui minimum size and adjust the size
			this->minimumSizeHint();
			this->adjustSize();

			// Turn to start game page
			ui.pages->setCurrentIndex(0);

			return;
		}
		else {
			cout << "<Quit> : Success\n";
			QCoreApplication::quit();
		}
	}
}

// Intent: To diffuse the surrounding coordinates when the button in the game clicked.
// Pre: The variable row and col must have a value.
// Post: The function returns nothing.
void MineSweeper::diffuse(int diffuseRow, int diffuseCol) {
	// If is not valid.
	if (!(0 <= diffuseRow && diffuseRow < gBoard.getRow() && 0 <= diffuseCol && diffuseCol < gBoard.getCol())) { return; }
	// If cannot be open.
	if (gBoard.map[diffuseRow][diffuseCol] != BLANK && gBoard.map[diffuseRow][diffuseCol] != QUESTION_MARK) { return; }
	// If the answer is a bomb, it cannot be diffused.
	else if (gBoard.mapAns[diffuseRow][diffuseCol] == BOMB) { return; }

	// If it can be diffused, open it and change the record.
	gBoard.map[diffuseRow][diffuseCol] = gBoard.mapAns[diffuseRow][diffuseCol];
	gBoard.setOpenBlankCount(gBoard.getOpenBlankCount() + 1);
	gBoard.setRemainBlankCount(gBoard.getRemainBlankCount() - 1);
	ui.openBlankCountLcdNumber->display(gBoard.getOpenBlankCount());
	ui.remainBlankCountLcdNumber->display(gBoard.getRemainBlankCount());
	showIcon(diffuseRow, diffuseCol);

	// If still need to diffuse, diffuse the surrounding coordinates.
	if (gBoard.mapAns[diffuseRow][diffuseCol] == '0') {
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

// Intent: To set flag, question mark or blank when the button in the game right clicked.
// Pre: The variable row and col must have a value.
// Post: The function returns nothing.
void MineSweeper::rightClick(int row, int col) {
	// Change between blank, flag, and question mark.
	if (gBoard.map[row][col] == BLANK) {
		gBoard.map[row][col] = FLAG;
		gBoard.setFlagCount(gBoard.getFlagCount() + 1);
		cout << "<RightClick " << row << " " << col << "> : Success\n";
	}
	else if (gBoard.map[row][col] == FLAG) {
		gBoard.map[row][col] = QUESTION_MARK;
		gBoard.setFlagCount(gBoard.getFlagCount() - 1);
		cout << "<RightClick " << row << " " << col << "> : Success\n";
	}
	else if (gBoard.map[row][col] == QUESTION_MARK) {
		gBoard.map[row][col] = BLANK;
		cout << "<RightClick " << row << " " << col << "> : Success\n";
	}
	else {
		cout << "<RightClick " << row << " " << col << "> : Failed\n";
	}

	// Display new flag count
	ui.flagCountLcdNumber->display(gBoard.getFlagCount());

	// Show icon
	showIcon(row, col);
}

// Intent: To get the right click event and get the row and column of the button by judge the position.
// Pre: The reference of QMouseEvent e must have a value.
// Post: The function returns nothing.
void MineSweeper::mousePressEvent(QMouseEvent* e) {
	// If the mouse event is right click
	if (e->button() == Qt::RightButton) {
		// If the game state is not Playing, leave the function
		if (gBoard.state != Playing) { return; }

		// Get mouse position
		int x = e->pos().x(), y = e->pos().y();

		// Modify mouse position
		x -= ui.centralWidget->x() + ui.pages->x() + ui.gameBoard->x() + ui.boardWigit->x();
		y -= ui.centralWidget->y() + ui.pages->y() + ui.gameBoard->y() + ui.boardWigit->y();

		// Find if the button clcik
		for (int i = 0; i < gBoard.getRow(); i++) {
			for (int j = 0; j < gBoard.getCol(); j++) {
				// Get button position
				int buttonX = field[i][j]->x(), buttonY = field[i][j]->y();

				// If mouse position is in the range of button position, execute rightclick function and leave the function
				if (buttonX <= x && x <= buttonX + BUTTON_WIDTH && buttonY <= y && y <= buttonY + BUTTON_WIDTH) {
					rightClick(i, j);
					return;
				}
			}
		}
	}
}