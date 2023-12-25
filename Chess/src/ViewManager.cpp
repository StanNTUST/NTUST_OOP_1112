// File: ViewManager.cpp
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This C++ program define the member functions of class "ViewManager".

#include "definition.h"
#include "ViewManager.h"

extern char gBoard[ROW][COL];
bool isCheating = false;
extern bool isDiagonalEat;
extern vector<promoteRecord> promotion;

// Intent: Default constructor.
// Pre: Input window's parent.
// Post: The function returns nothing.
ViewManager::ViewManager(QWidget* parent)
	: QMainWindow(parent)
{
	// Set up ui by using the auto generated file ui_ViewManager.h
	ui.setupUi(this);

	//Set the contents of status bar.
	statusBarIcon->setPixmap(QPixmap(STATUS_BAR_ICON));
	statusBarIcon->setScaledContents(true);
	statusBarIcon->setMaximumSize(QSize(ui.statusBar->height(), ui.statusBar->height()));
	statusBarText->setText("GameState : " + QString::fromStdString(gManager.getGameState()));
	ui.statusBar->addWidget(statusBarIcon);
	ui.statusBar->addWidget(statusBarText, 1);
	ui.statusBar->setStyleSheet("background-color:rgb(125,125,125);color:white;");

	// startGameButton
	connect(ui.startGameButton, &QPushButton::clicked, this, &ViewManager::startGameButtonClicked);

	// Setting page
	connect(ui.actionSetting, &QAction::triggered, this, [=]() { ui.stackedWidget->setCurrentIndex(1); });
	connect(ui.backButton, &QPushButton::clicked, this, [=]() {
		// Change page according to game state.
		if (gManager.gState == Playing) { ui.stackedWidget->setCurrentIndex(2); }
		else { ui.stackedWidget->setCurrentIndex(0); }

		// Find the current status.
		((gManager.whoseTurn == black) ? gManager.blackPlayer : gManager.whitePlayer).status();

		// Check game status.
		checkStatus();
		});
	connect(ui.blackTempoCheckBox, &QCheckBox::clicked, this, [=]() {
		// If black tempo
		if (ui.blackTempoCheckBox->isChecked()) { ui.whiteTempoCheckBox->setChecked(false); }
		// If white tempo
		else { ui.whiteTempoCheckBox->setChecked(true); }

		// Change player
		gManager.changePlayer();
		});
	connect(ui.whiteTempoCheckBox, &QCheckBox::clicked, this, [=]() {
		// If white tempo
		if (ui.whiteTempoCheckBox->isChecked()) { ui.blackTempoCheckBox->setChecked(false); }
		// If black tempo
		else { ui.blackTempoCheckBox->setChecked(true); }

		// Change player
		gManager.changePlayer();
		});
	connect(ui.actionQuit, &QAction::triggered, this, [=]() {
		// Output the message.
		cout << "Quit\n";

		// End the gui
		QCoreApplication::quit();
		});

	// volumeSlider
	connect(ui.volumeSlider, &QSlider::valueChanged, this, [=]() { musicPlayer->setVolume(ui.volumeSlider->value()); });

	// Print
	connect(ui.actionGameState, &QAction::triggered, this, [=]() { cout << "GameState : " << gManager.getGameState() << endl; });
	connect(ui.actionGameBoard, &QAction::triggered, this, [=]() {
		cout << "GameBoard : \n";
		if (gManager.gState == Playing) { gManager.printGameBoard(); }
		});
	connect(ui.actionRecord, &QAction::triggered, this, [=]() { gManager.printRecord(); });

	// Undo & Redo
	connect(ui.actionUndo, &QAction::triggered, this, [=]() {
		// If the game state is playing.
		if (gManager.gState == Playing) {
			// Undo and update.
			gManager.undo();
			update();
			updateWhoseTurn();

			// Reset the background color of the buttons.
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if ((i + j) % 2 == 0) { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 207, 159)")); }
					else { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(210, 140, 69)")); }
				}
			}
		}
		});
	connect(ui.actionRedo, &QAction::triggered, this, [=]() {
		// If the game state is playing.
		if (gManager.gState == Playing) {
			// Redo and update.
			gManager.redo();
			update();
			updateWhoseTurn();

			// Reset the background color of the buttons.
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if ((i + j) % 2 == 0) { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 207, 159)")); }
					else { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(210, 140, 69)")); }
				}
			}
		}
		});

	// Cheating check box
	connect(ui.cheatingCheckBox, &QCheckBox::clicked, this, [=]() {
		isCheating = ui.cheatingCheckBox->isChecked();

		if (gManager.blackPlayer.hasChoose || gManager.whitePlayer.hasChoose) {
			// Canceling clicking.
			leftClick(clickRow, clickCol);

			// Click again.
			leftClick(clickRow, clickCol);
		}
		});

	// Change player by cheating.
	connect(ui.changePlayerButton, &QPushButton::clicked, this, [=]() {
		// If the game state is playing.
		if (gManager.gState == Playing && isCheating && !gManager.whitePlayer.hasChoose && !gManager.blackPlayer.hasChoose) {
			// Change player.
			gManager.changePlayer();
			updateWhoseTurn();

			// Manage timer.
			if (gManager.whoseTurn == white) {
				// Change timer.
				blackTimer->stop();
				whiteTimer->start(1000);
			}
			else {
				// Change timer.
				whiteTimer->stop();
				blackTimer->start(1000);
			}
		}
		});

	// Promote
	connect(ui.promotionQueen, &QPushButton::clicked, this, [&]() { setPromote(queen); });
	connect(ui.promotionBishop, &QPushButton::clicked, this, [&]() { setPromote(bishop); });
	connect(ui.promotionKnight, &QPushButton::clicked, this, [&]() { setPromote(knight); });
	connect(ui.promotionRook, &QPushButton::clicked, this, [&]() { setPromote(rook); });

	// Surrender and Negotiate
	connect(ui.blackSurrenderButton, &QPushButton::clicked, this, [=]() {
		// If the turn is black.
		if (gManager.whoseTurn == black) {
			// Manage the state and output the message.
			Player::game = blackSurrender;

			// Check status.
			checkStatus();
		}
		});
	connect(ui.whiteSurrenderButton, &QPushButton::clicked, this, [=]() {
		// If the turn is white.
		if (gManager.whoseTurn == white) {
			// Manage the state and output the message.
			Player::game = whiteSurrender;

			// Check status.
			checkStatus();
		}
		});
	connect(ui.blackNegotiateButton, &QPushButton::clicked, this, [=]() {
		blackNegotiate = true;

		// If both player negotiate
		if (blackNegotiate && whiteNegotiate) {
			// Manage the state and output the message.
			Player::game = draw;

			checkStatus();
		}
		});
	connect(ui.whiteNegotiateButton, &QPushButton::clicked, this, [=]() {
		whiteNegotiate = true;

		// If both player negotiate
		if (blackNegotiate && whiteNegotiate) {
			// Manage the state and output the message.
			Player::game = draw;

			// Check status.
			checkStatus();
		}
		});

	// Set FEN
	connect(ui.enterButton, &QPushButton::clicked, this, [=]() {
		// Get input FEN
		string input = ui.lineEdit->text().toStdString();

		if (input != "") {
			gManager.setFEN(input);
			gManager.deathCount(input);
			gManager.recordIndex = -1;
			gManager.stepRecord.clear();
			gManager.record();
			update();
			updateWhoseTurn();

			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					if ((i + j) % 2 == 0) { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 207, 159)")); }
					else { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(210, 140, 69)")); }
				}
			}
		}
		});

	// Open history file
	connect(ui.actionHistory_2, &QAction::triggered, this, [=]() {
		// Clear the promotion imformation.
		promotion.clear();

		// If the game state is playing.
		if (gManager.gState != Playing) {
			// Open QFileDialog to let user select file and get the file path.
			string path = QFileDialog::getOpenFileName(this, "Choose File", "./history", "Text Files (*.txt)").toStdString();

			if (path != "") {
				// Clear the record.
				gManager.recordIndex = -1;
				gManager.stepRecord.clear();

				// Initialize the dead chessman.
				for (int i = 0; i < numOfType; i++) {
					gManager.whitePlayer.deadChessman[i] = 0;
					gManager.blackPlayer.deadChessman[i] = 0;
				}

				// Update the board.
				update();

				// Change to board page.
				ui.stackedWidget->setCurrentIndex(2);

				// Open history file.
				ifstream historyFile(path);

				// A char to record who win.
				char whoWin;

				// Input who win.
				historyFile >> whoWin;

				// Ignore the endline.
				historyFile.ignore();

				// Astring to record history FEN.
				string historyFEN;

				// While there is an input.
				while (getline(historyFile, historyFEN)) {
					// Set up the situation.
					gManager.setFEN(historyFEN);
					gManager.deathCount(historyFEN);

					// The value must be positive.
					for (int i = 0; i < numOfType; i++) {
						if (gManager.whitePlayer.deadChessman[i] < 0) {
							gManager.whitePlayer.deadChessman[i] = 0;
						}
						if (gManager.blackPlayer.deadChessman[i] < 0) {
							gManager.blackPlayer.deadChessman[i] = 0;
						}
					}

					// Update.
					update();
					updateWhoseTurn();

					// Wait 1 second.
					Sleep(1000);
					QCoreApplication::processEvents();
				}

				// Manage the state.
				if (whoWin == 'W') { Player::game = whiteWin; }
				else if (whoWin == 'B') { Player::game = blackWin; }
				else if (whoWin == 'd') { Player::game = draw; }
				else if (whoWin == 'w') { Player::game = blackSurrender; }
				else if (whoWin == 'b') { Player::game = whiteSurrender; }

				// Show message box.
				showMsgBox();

				// Close the file.
				historyFile.close();

				// Clear the promotion imformation.
				promotion.clear();
			}
		}
		});

	// Delete file
	connect(ui.actionDelete_file, &QAction::triggered, this, [=]() {
		// If the game state is playing.
		if (gManager.gState != Playing) {
			// A QStringList to record the selected files' path.
			QStringList paths = QFileDialog::getOpenFileNames(this, "Delete Files", "./history", "Text Files (*.txt)");

			// Traverse paths.
			for (QString& path : paths) {
				if (path != "") {
					// Remove the file.
					QFile file(path);
					file.remove();
				}
			}
		}
		});

	// Style
	connect(ui.normalStyleCheckBox, &QCheckBox::clicked, this, [=]() {
		// If choose normal style.
		if (ui.normalStyleCheckBox->isChecked()) {
			ui.specialStyleCheckBox->setChecked(false);
			setStyle(normal);
		}
		// If choose special style.
		else {
			ui.specialStyleCheckBox->setChecked(true);
			setStyle(special);
		}
		});
	connect(ui.specialStyleCheckBox, &QCheckBox::clicked, this, [=]() {
		// If choose special style.
		if (ui.specialStyleCheckBox->isChecked()) {
			ui.normalStyleCheckBox->setChecked(false);
			setStyle(special);
		}
		// If choose normal style.
		else {
			ui.normalStyleCheckBox->setChecked(true);
			setStyle(normal);
		}
		});

	// Ridicule
	connect(ui.actionRidicule, &QAction::triggered, this, [=]() {
		if (gManager.gState == Playing) { playVideo(RIDICULE_VIDEO); }
		});

	// If the video stop playing.
	connect(videoPlayer, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state) {
		// If the video stop playing, close the window.
		if (state == QMediaPlayer::StoppedState) {
			// Close the window.
			videoWidget->close();


			videoPlayer->stop();

			// Delete the video widget.
			delete videoWidget;
		}
		});

	// Connect timers.
	connect(blackTimer, &QTimer::timeout, [&]() {
		blackTime = blackTime.addSecs(-1);
		ui.blackTimerLabel->setText(blackTime.toString("hh:mm:ss"));

		if (blackTime == QTime(0, 0)) {
			Player::game = blackSurrender;
			checkStatus();
			blackTimer->stop();
		}
		});
	connect(whiteTimer, &QTimer::timeout, [&]() {
		whiteTime = whiteTime.addSecs(-1);
		ui.whiteTimerLabel->setText(whiteTime.toString("hh:mm:ss"));

		if (whiteTime == QTime(0, 0)) {
			Player::game = whiteSurrender;
			checkStatus();
			whiteTimer->stop();
		}
		});

	// Connect buttons
	connectButtons();

	// Set initial style to normal.
	setStyle(normal);

	// Update the board.
	update();
}

// Intent: Play music.
// Pre: Input music file's path.
// Post: The function returns nothing.
void ViewManager::play(QString musicPath) {
	// Set media by file path.
	musicPlayer->setMedia(QUrl::fromLocalFile(musicPath));

	// Set player's volume.
	musicPlayer->setVolume(ui.volumeSlider->value());

	// Play the music.
	musicPlayer->play();
}

// Intent: Play sound effect.
// Pre: Input sound effect file's path.
// Post: The function returns nothing.
void ViewManager::playSoundEffect(QString musicPath) {
	// Set media by file path.
	soundEffectPlayer->setMedia(QUrl::fromLocalFile(musicPath));

	// Set player's volume.
	soundEffectPlayer->setVolume(60);

	// Play the sound effect.
	soundEffectPlayer->play();
}

// Intent: Play video.
// Pre: Input video path.
// Post: The function returns nothing.
void ViewManager::playVideo(QString videoPath) {
	// Create video widgit
	videoWidget = new QVideoWidget();

	// Create a new video player.
	delete videoPlayer;
	videoPlayer = new QMediaPlayer;

	// If the video stop playing.
	connect(videoPlayer, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state) {
		// If the video stop playing, close the window.
		if (state == QMediaPlayer::StoppedState) {
			// Close the window.
			videoWidget->close();

			// Delete the video widget.
			delete videoWidget;
		}
		});

	// Show video widgit
	videoWidget->show();

	// Set video media
	videoPlayer->setVideoOutput(videoWidget);

	// Set media by file path.
	videoPlayer->setMedia(QUrl::fromLocalFile(videoPath));

	// Set player's volume
	videoPlayer->setVolume(30);

	// Play the music
	videoPlayer->play();
}

// Intent: Set style.
// Pre: Input the style user want to set.
// Post: The function returns nothing.
void ViewManager::setStyle(iconStyle settingStyle) {
	// If the setting style is normal.
	if (settingStyle == normal) {
		// Set all the icons and images into normal style.
		for (int i = 0; i < numOfType; i++) {
			BLACK_ICON[i] = NORMAL_BLACK_ICON[i];
			WHITE_ICON[i] = NORMAL_WHITE_ICON[i];
		}
		BLACK_TURN_IMAGE = NORMAL_BLACK_TURN_IMAGE;
		WHITE_TURN_IMAGE = NORMAL_WHITE_TURN_IMAGE;
	}
	// If the setting style is special.
	else {
		// Set all the icons and images into special style.
		for (int i = 0; i < numOfType; i++) {
			BLACK_ICON[i] = SPECIAL_BLACK_ICON[i];
			WHITE_ICON[i] = SPECIAL_WHITE_ICON[i];
		}
		BLACK_TURN_IMAGE = SPECIAL_BLACK_TURN_IMAGE;
		WHITE_TURN_IMAGE = SPECIAL_WHITE_TURN_IMAGE;
	}

	// Deat count label
	ui.deadBlackKing->setIcon(QIcon(QString::fromStdString(BLACK_ICON[king])));
	ui.deadBlackQueen->setIcon(QIcon(QString::fromStdString(BLACK_ICON[queen])));
	ui.deadBlackBishop->setIcon(QIcon(QString::fromStdString(BLACK_ICON[bishop])));
	ui.deadBlackKnight->setIcon(QIcon(QString::fromStdString(BLACK_ICON[knight])));
	ui.deadBlackRook->setIcon(QIcon(QString::fromStdString(BLACK_ICON[rook])));
	ui.deadBlackPawn->setIcon(QIcon(QString::fromStdString(BLACK_ICON[pawn])));
	ui.deadWhiteKing->setIcon(QIcon(QString::fromStdString(WHITE_ICON[king])));
	ui.deadWhiteQueen->setIcon(QIcon(QString::fromStdString(WHITE_ICON[queen])));
	ui.deadWhiteBishop->setIcon(QIcon(QString::fromStdString(WHITE_ICON[bishop])));
	ui.deadWhiteKnight->setIcon(QIcon(QString::fromStdString(WHITE_ICON[knight])));
	ui.deadWhiteRook->setIcon(QIcon(QString::fromStdString(WHITE_ICON[rook])));
	ui.deadWhitePawn->setIcon(QIcon(QString::fromStdString(WHITE_ICON[pawn])));

	// Update the board and whose turn.
	update();
	updateWhoseTurn();
}

// Intent: Show message box.
// Pre: Input nothing.
// Post: The function returns nothing.
void ViewManager::showMsgBox() {
	// Play sound effect.
	playSoundEffect(HOTPOT_SOUND_EFFECT);

	// Create a message box
	QMessageBox msgBox;

	// Set window title and text in the message box
	msgBox.setWindowTitle("Game Over!");
	if (Player::game == draw) { msgBox.setInformativeText("Draw"); }
	else if (Player::game == blackWin) { msgBox.setInformativeText("Checkmate\nWinner is black"); }
	else if (Player::game == whiteWin) { msgBox.setInformativeText("Checkmate\nWinner is white"); }
	else if (Player::game == blackSurrender) { msgBox.setInformativeText("Winner is white"); }
	else if (Player::game == whiteSurrender) { msgBox.setInformativeText("Winner is black"); }

	// Set standard and default button in the message box
	msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
	msgBox.setDefaultButton(QMessageBox::Yes);

	// Set button in the message box
	msgBox.setButtonText(QMessageBox::Yes, "Replay");
	msgBox.setButtonText(QMessageBox::No, "Quit");

	// Move message box into the center of the screen.
	int x = (QGuiApplication::primaryScreen()->availableGeometry().width() - msgBox.sizeHint().width()) / 2;
	int y = (QGuiApplication::primaryScreen()->availableGeometry().height() - msgBox.sizeHint().height()) / 2;
	msgBox.move(x, y);

	// Get the value when the message box finish
	int reply = msgBox.exec();

	if (reply == QMessageBox::Yes) {
		// Close the message box
		msgBox.close();

		// Stop sound effect
		soundEffectPlayer->stop();

		// Initialize the GameManager.
		gManager.GameManager::GameManager();

		// Clear the promotion imformation.
		promotion.clear();

		// Enable tempo check box.
		ui.blackTempoCheckBox->setDisabled(false);
		ui.whiteTempoCheckBox->setDisabled(false);

		// Set the status bar.
		statusBarText->setText("GameState : " + QString::fromStdString(gManager.getGameState()));

		// Output the message.
		cout << "Replay\n";

		// Update the board.
		update();

		// Update whose turn.
		updateWhoseTurn();

		// Turn to start game page
		ui.stackedWidget->setCurrentIndex(0);
	}
	else {
		// Output the message.
		cout << "Quit\n";

		// End the gui
		QCoreApplication::quit();
	}
}

// Intent: Connect the button and push them into vector.
// Pre: Input nothing.
// Post: The function returns nothing.
void ViewManager::connectButtons() {
	// row 8
	buttons.push_back(ui.a8);
	buttons.push_back(ui.b8);
	buttons.push_back(ui.c8);
	buttons.push_back(ui.d8);
	buttons.push_back(ui.e8);
	buttons.push_back(ui.f8);
	buttons.push_back(ui.g8);
	buttons.push_back(ui.h8);

	// row 7
	buttons.push_back(ui.a7);
	buttons.push_back(ui.b7);
	buttons.push_back(ui.c7);
	buttons.push_back(ui.d7);
	buttons.push_back(ui.e7);
	buttons.push_back(ui.f7);
	buttons.push_back(ui.g7);
	buttons.push_back(ui.h7);

	// row 6
	buttons.push_back(ui.a6);
	buttons.push_back(ui.b6);
	buttons.push_back(ui.c6);
	buttons.push_back(ui.d6);
	buttons.push_back(ui.e6);
	buttons.push_back(ui.f6);
	buttons.push_back(ui.g6);
	buttons.push_back(ui.h6);

	// row 5
	buttons.push_back(ui.a5);
	buttons.push_back(ui.b5);
	buttons.push_back(ui.c5);
	buttons.push_back(ui.d5);
	buttons.push_back(ui.e5);
	buttons.push_back(ui.f5);
	buttons.push_back(ui.g5);
	buttons.push_back(ui.h5);

	// row 4
	buttons.push_back(ui.a4);
	buttons.push_back(ui.b4);
	buttons.push_back(ui.c4);
	buttons.push_back(ui.d4);
	buttons.push_back(ui.e4);
	buttons.push_back(ui.f4);
	buttons.push_back(ui.g4);
	buttons.push_back(ui.h4);

	// row 3
	buttons.push_back(ui.a3);
	buttons.push_back(ui.b3);
	buttons.push_back(ui.c3);
	buttons.push_back(ui.d3);
	buttons.push_back(ui.e3);
	buttons.push_back(ui.f3);
	buttons.push_back(ui.g3);
	buttons.push_back(ui.h3);

	// row 2
	buttons.push_back(ui.a2);
	buttons.push_back(ui.b2);
	buttons.push_back(ui.c2);
	buttons.push_back(ui.d2);
	buttons.push_back(ui.e2);
	buttons.push_back(ui.f2);
	buttons.push_back(ui.g2);
	buttons.push_back(ui.h2);

	// row 1
	buttons.push_back(ui.a1);
	buttons.push_back(ui.b1);
	buttons.push_back(ui.c1);
	buttons.push_back(ui.d1);
	buttons.push_back(ui.e1);
	buttons.push_back(ui.f1);
	buttons.push_back(ui.g1);
	buttons.push_back(ui.h1);

	// Connect all the buttons with leftClick function.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			connect(buttons[i * COL + j], &QPushButton::clicked, this, [=]() {
				leftClick(i, j);
				});
		}
	}
}

// Intent: Update the icons and images of buttons and labels.
// Pre: Input nothing.
// Post: The function returns nothing.
void ViewManager::update() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			// Change the icon according to the chessman's type.
			for (int k = 0; k < numOfType; k++) {
				if (gBoard[i][j] == BLACK_SYMBOL[k]) {
					buttons[i * COL + j]->setIcon(QIcon(QString::fromStdString(BLACK_ICON[k])));
				}
				else if (gBoard[i][j] == WHITE_SYMBOL[k]) {
					buttons[i * COL + j]->setIcon(QIcon(QString::fromStdString(WHITE_ICON[k])));
				}
			}

			// Unset the icon if it's blank.
			if (gBoard[i][j] == BLANK) { buttons[i * COL + j]->setIcon(QIcon()); }
		}
	}

	// Update dead count labels.
	ui.deadBlackRookLabel->setText(QString::number(gManager.blackPlayer.deadChessman[rook]));
	ui.deadBlackKnightLabel->setText(QString::number(gManager.blackPlayer.deadChessman[knight]));
	ui.deadBlackBishopLabel->setText(QString::number(gManager.blackPlayer.deadChessman[bishop]));
	ui.deadBlackQueenLabel->setText(QString::number(gManager.blackPlayer.deadChessman[queen]));
	ui.deadBlackKingLabel->setText(QString::number(gManager.blackPlayer.deadChessman[king]));
	ui.deadBlackPawnLabel->setText(QString::number(gManager.blackPlayer.deadChessman[pawn]));
	ui.deadWhiteRookLabel->setText(QString::number(gManager.whitePlayer.deadChessman[rook]));
	ui.deadWhiteKnightLabel->setText(QString::number(gManager.whitePlayer.deadChessman[knight]));
	ui.deadWhiteBishopLabel->setText(QString::number(gManager.whitePlayer.deadChessman[bishop]));
	ui.deadWhiteQueenLabel->setText(QString::number(gManager.whitePlayer.deadChessman[queen]));
	ui.deadWhiteKingLabel->setText(QString::number(gManager.whitePlayer.deadChessman[king]));
	ui.deadWhitePawnLabel->setText(QString::number(gManager.whitePlayer.deadChessman[pawn]));
}

// Intent: Update whose turn.
// Pre: Input nothing.
// Post: The function returns nothing.
void ViewManager::updateWhoseTurn() {
	// If whose turn is white, set the icon of change player button into white turn image.
	if (gManager.whoseTurn == white) { ui.changePlayerButton->setIcon(QIcon(WHITE_TURN_IMAGE.c_str())); }
	// If whose turn is black, set the icon of change player button into black turn image.
	else { ui.changePlayerButton->setIcon(QIcon(BLACK_TURN_IMAGE.c_str())); }
}

// Intent: Set promote page.
// Pre: Input the color of current player.
// Post: The function returns nothing.
void ViewManager::promote(color playerColor) {
	// If the player color is white, set the promote buttons' icon into white icon.
	if (playerColor == white) {
		ui.promotionQueen->setIcon(QIcon(QString::fromStdString(WHITE_ICON[queen])));
		ui.promotionBishop->setIcon(QIcon(QString::fromStdString(WHITE_ICON[bishop])));
		ui.promotionKnight->setIcon(QIcon(QString::fromStdString(WHITE_ICON[knight])));
		ui.promotionRook->setIcon(QIcon(QString::fromStdString(WHITE_ICON[rook])));
	}
	// If the player color is black, set the promote buttons' icon into black icon.
	else {
		ui.promotionQueen->setIcon(QIcon(QString::fromStdString(BLACK_ICON[queen])));
		ui.promotionBishop->setIcon(QIcon(QString::fromStdString(BLACK_ICON[bishop])));
		ui.promotionKnight->setIcon(QIcon(QString::fromStdString(BLACK_ICON[knight])));
		ui.promotionRook->setIcon(QIcon(QString::fromStdString(BLACK_ICON[rook])));
	}

	// Change to the promote page.
	ui.stackedWidget->setCurrentIndex(3);
}

// Intent: Promote the chessman.
// Pre: Input the type user want to promote.
// Post: The function returns nothing.
void ViewManager::setPromote(type promoteType) {
	// Get current player and its color.
	Player* currPlayer = (gManager.whoseTurn == black) ? &gManager.whitePlayer : &gManager.blackPlayer;
	color currColor = currPlayer->pColor;

	// Set the coordinate into promote type.
	if (currColor == white) { gBoard[clickRow][clickCol] = WHITE_SYMBOL[promoteType]; }
	else { gBoard[clickRow][clickCol] = BLACK_SYMBOL[promoteType]; }

	// Record the FEN again.
	gManager.stepRecord.pop_back();
	gManager.recordIndex--;
	gManager.record();

	// A structure to record promote imformations.
	promoteRecord tmp;
	tmp.promoteIndex = gManager.recordIndex;
	tmp.promoteColor = currColor;
	tmp.promoteType = promoteType;

	// Push back the promote imformation into the vector.
	promotion.push_back(tmp);

	// Update the promoted chessman.
	for (int i = 0; i < currPlayer->myPieces.size(); i++) {
		if (currPlayer->myPieces[i]->rowPos == clickRow && currPlayer->myPieces[i]->colPos == clickCol) {
			currPlayer->myPieces[i]->sType = promoteType;

			// Update the GUI.
			update();

			break;
		}
	}

	if (gManager.whoseTurn == white) {
		// Add step second.
		blackTime = blackTime.addSecs(ui.stepSecoundSpinBox->value());

		// Set text.
		ui.blackTimerLabel->setText(blackTime.toString("hh:mm:ss"));

		// Change timer.
		blackTimer->stop();
		whiteTimer->start(1000);
	}
	else {
		// Add step second.
		whiteTime = whiteTime.addSecs(ui.stepSecoundSpinBox->value());

		// Set text.
		ui.whiteTimerLabel->setText(whiteTime.toString("hh:mm:ss"));

		// Change timer.
		whiteTimer->stop();
		blackTimer->start(1000);
	}

	ui.stackedWidget->setCurrentIndex(2);

	// Find the current status.
	currPlayer->status();

	// Check game status.
	checkStatus();
}

// Intent: Start the game.
// Pre: Input nothing.
// Post: The function returns nothing.
void ViewManager::startGameButtonClicked() {
	// Change game state and status bar text.
	gManager.gState = Playing;
	Player::game = carry;

	// Innitialize player's negotiate boolean.
	blackNegotiate = false;
	whiteNegotiate = false;

	// Set status bar text.
	statusBarText->setText("GameState : " + QString::fromStdString(gManager.getGameState()));

	// Disable the tempo check box.
	ui.blackTempoCheckBox->setDisabled(true);
	ui.whiteTempoCheckBox->setDisabled(true);

	// Set timers' value.
	whiteTime.setHMS(ui.hourSpinBox->value(), ui.minuteSpinBox->value(), ui.secondSpinBox->value());
	blackTime.setHMS(ui.hourSpinBox->value(), ui.minuteSpinBox->value(), ui.secondSpinBox->value());

	// Set text.
	ui.whiteTimerLabel->setText(whiteTime.toString("hh:mm:ss"));
	ui.blackTimerLabel->setText(blackTime.toString("hh:mm:ss"));

	// Start timing.
	if (gManager.whoseTurn == white) { whiteTimer->start(1000); }
	else { blackTimer->start(1000); }

	// Change to the game board page.
	ui.stackedWidget->setCurrentIndex(2);

	// record the FEN.
	gManager.record();

	// Update whose turn's Icon.
	updateWhoseTurn();

	// Play music.
	play(MAIN_MUSIC);
}

// Intent: Left click a button.
// Pre: Input row and column.
// Post: The function returns nothing.
void ViewManager::leftClick(int row, int col) {
	// Record current player.
	Player* currPlayer = (gManager.whoseTurn == black) ? &gManager.blackPlayer : &gManager.whitePlayer;
	Player* opponentPlayer = (gManager.whoseTurn == white) ? &gManager.blackPlayer : &gManager.whitePlayer;

	// If current player has choose, doesn't move, click invalid destination, blank or opponent, cancel clicking.
	if (currPlayer->hasChoose && !currPlayer->hasMoved &&
		currPlayer->movingPiece->validDestinations[row][col] == false &&
		((row == clickRow && col == clickCol) ||
			currPlayer->movingPiece->check(row, col, blank) ||
			currPlayer->movingPiece->check(row, col, opponent))) {
		// Reset hasChoose. 
		currPlayer->hasChoose = false;

		// Reset movingPiece valid destination.
		currPlayer->movingPiece->initValidDestination();

		// Change the buttons' background color.
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				// If the destination is valid, change the background color into red.
				if (currPlayer->movingPiece->validDestinations[i][j]) {
					buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:red"));
				}
				// Otherwise, change the color into the original one.
				else {
					if ((i + j) % 2 == 0) { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 207, 159)")); }
					else { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(210, 140, 69)")); }
				}
			}
		}

		return;
	}

	// If the main music is stop, player the main music.
	if (musicPlayer->state() == QMediaPlayer::StoppedState) { play(MAIN_MUSIC); }

	// If game state is not Playing, leave the function.
	if (gManager.gState != Playing) { return; }

	// If the position is out of board, leave the function.
	if (row < 0 || ROW <= row || col < 0 || COL <= col) { return; }

	clickRow = row;
	clickCol = col;

	// Current player want to move.
	if (currPlayer->wantMove(row, col)) {
		// If diagonal eat, modify the dead piece's position.
		if (isDiagonalEat) {
			if (gManager.whoseTurn == white) row += 1;
			else row -= 1;

			isDiagonalEat = false;
		}

		// Find the dead piece.
		for (int i = 0; i < opponentPlayer->myPieces.size(); i++) {
			// If find the dead piece.
			if (opponentPlayer->myPieces[i]->rowPos == row && opponentPlayer->myPieces[i]->colPos == col) {
				// opponent player's deadChessman's "type" + 1.
				opponentPlayer->deadChessman[opponentPlayer->myPieces[i]->sType]++;

				// Erase the piece.
				opponentPlayer->myPieces.erase(opponentPlayer->myPieces.begin() + i);
			}
		}
	}

	// If the player does not pick his own piece, return.
	if (!currPlayer->hasChoose) { return; }

	bool isPromoting = false;

	// If "player" is pawn and is in the margin, promote the pawn. 
	if (gManager.whoseTurn == black && gBoard[clickRow][clickCol] == BLACK_SYMBOL[pawn] && clickRow == 7) {
		promote(black);
		isPromoting = true;
	}
	else if (gManager.whoseTurn == white && gBoard[clickRow][clickCol] == WHITE_SYMBOL[pawn] && clickRow == 0) {
		promote(white);
		isPromoting = true;
	}

	// Otherwise, change the buttons' background color.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			// If the destination is valid, change the background color into red.
			if (currPlayer->movingPiece->validDestinations[i][j]) {
				buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:red"));
			}
			// Otherwise, change the color into the original one.
			else {
				if ((i + j) % 2 == 0) { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 207, 159)")); }
				else { buttons[i * COL + j]->setStyleSheet(QString::fromUtf8("background-color:rgb(210, 140, 69)")); }
			}
		}
	}

	// Update the GUI.
	update();

	// Initialize and change player.
	if (currPlayer->hasMoved) {
		// Plat click sound effect.
		playSoundEffect(soundEffect[ui.moveComboBox->currentIndex()].c_str());

		// Innitialize the movingPiece, hasChoose, hasMove.
		currPlayer->movingPiece = nullptr;
		currPlayer->hasChoose = false;
		currPlayer->hasMoved = false;

		// Set all oppoentPlayer's pieces are not enpassant.
		for (int i = 0; i < opponentPlayer->myPieces.size(); i++) {
			opponentPlayer->myPieces[i]->isEnPassant = false;
		}

		// Find the current status.
		currPlayer->status();

		// Check game status.
		checkStatus();

		// Change the player.
		gManager.changePlayer();

		// Manage timer.
		if (gManager.whoseTurn == white && !isPromoting) {
			// Add step second.
			blackTime = blackTime.addSecs(ui.stepSecoundSpinBox->value());

			// Set text.
			ui.blackTimerLabel->setText(blackTime.toString("hh:mm:ss"));

			// Change timer.
			blackTimer->stop();
			whiteTimer->start(1000);
		}
		else if (gManager.whoseTurn == black && !isPromoting) {
			// Add step second.
			whiteTime = whiteTime.addSecs(ui.stepSecoundSpinBox->value());

			// Set text.
			ui.whiteTimerLabel->setText(whiteTime.toString("hh:mm:ss"));

			// Change timer.
			whiteTimer->stop();
			blackTimer->start(1000);
		}

		// record the FEN.
		gManager.record();

		// Update whose turn's Icon.
		updateWhoseTurn();

		// Innitialize player's negotiate boolean.
		blackNegotiate = false;
		whiteNegotiate = false;
	}
}

// Intent: Check the game status.
// Pre: Input nothing.
// Post: The function returns nothing.
void  ViewManager::checkStatus() {
	if (Player::game == carry) { return; }

	// Record the FEN.
	gManager.record();

	// Save the file.
	gManager.saveFile();

	// Set the status.
	gManager.gState = GameOver;

	// Set status bar text.
	statusBarText->setText("GameState : " + QString::fromStdString(gManager.getGameState()));

	// Stop playing music.
	musicPlayer->stop();

	// Stop clock.
	blackTimer->stop();
	whiteTimer->stop();

	// Show message box.
	showMsgBox();

	// Output the result.
	if (Player::game == draw) { cout << "Draw\n"; }
	else if (Player::game == blackWin) { cout << "Checkmate\nWinner is black\n"; }
	else if (Player::game == whiteWin) { cout << "Checkmate\nWinner is white\n"; }
	else if (Player::game == blackSurrender) { cout << "Winner is white\n"; }
	else if (Player::game == whiteSurrender) { cout << "Winner is black\n"; }
}