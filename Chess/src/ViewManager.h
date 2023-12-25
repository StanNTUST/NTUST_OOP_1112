#pragma once

// File: ViewManager.h
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This header file declare the class "ViewManager" and it's member functions.

#include <Qlabel>
#include <Qmediaplayer>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <Qvideowidget>
#include <QTime>
#include <QTimer>
#include <QScreen>
#include "ui_ViewManager.h"
#include "definition.h"
#include "GameManager.h"

class ViewManager : public QMainWindow
{
	Q_OBJECT

public:
	// Intent: Default constructor.
	// Pre: Input window's parent.
	// Post: The function returns nothing.
	ViewManager(QWidget* parent = Q_NULLPTR);

private:
	Ui::ChessClass ui;

	// Status bur's text and icon.
	QLabel* statusBarText = new QLabel();
	QLabel* statusBarIcon = new QLabel();

	// Create a music player.
	QMediaPlayer* musicPlayer = new QMediaPlayer;
	QMediaPlayer* soundEffectPlayer = new QMediaPlayer;
	QMediaPlayer* videoPlayer = new QMediaPlayer;
	QVideoWidget* videoWidget;

	// Create timers.
	QTime blackTime;
	QTime whiteTime;
	QTimer* blackTimer = new QTimer();
	QTimer* whiteTimer = new QTimer();

	// Buttons
	vector<QPushButton*> buttons;

	// Game Manager
	GameManager gManager;

	// Icons
	string BLACK_ICON[numOfType];
	string WHITE_ICON[numOfType];

	// Whose turn image.
	string BLACK_TURN_IMAGE = NORMAL_BLACK_TURN_IMAGE;
	string WHITE_TURN_IMAGE = NORMAL_WHITE_TURN_IMAGE;

	// The coordinate of the clicked button.
	int clickRow, clickCol;

	// Promote type.
	type promoteType;

	// Negotiate
	bool blackNegotiate = false, whiteNegotiate = false;

	// Intent: Play music.
	// Pre: Input music file's path.
	// Post: The function returns nothing.
	void play(QString musicPath);

	// Intent: Play sound effect.
	// Pre: Input sound effect file's path.
	// Post: The function returns nothing.
	void playSoundEffect(QString musicPath);

	// Intent: Play video.
	// Pre: Input video path.
	// Post: The function returns nothing.
	void playVideo(QString videoPath);

	// Intent: Set style.
	// Pre: Input the style user want to set.
	// Post: The function returns nothing.
	void setStyle(iconStyle settingStyle);

	// Intent: Show message box.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void showMsgBox();

	// Intent: Connect the button and push them into vector.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void connectButtons();

	// Intent: Update the icons and images of buttons and labels.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void update();

	// Intent: Update whose turn.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void updateWhoseTurn();

	// Intent: Set promote page.
	// Pre: Input the color of current player.
	// Post: The function returns nothing.
	void promote(color playerColor);

	// Intent: Update the icons and images of buttons and labels.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void setPromote(type promoteType);

	// Intent: Start the game.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void startGameButtonClicked();

	// Intent: Left click a button.
	// Pre: Input row and column.
	// Post: The function returns nothing.
	void leftClick(int row, int col);

	// Intent: Check the game status.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void checkStatus();
};
