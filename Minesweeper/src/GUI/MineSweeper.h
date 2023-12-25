#pragma once

// File: MineSweeper.h
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005, B11130038
// Update Date : 2023/04/12
// Description : This header file declare the class "MineSweeper" and it's member functions.

// ui_MineSweeper.h was automatically generated by Qt User Interface Compiler,
// this file cannot be edited so there will be no comments.
#include "ui_MineSweeper.h"

// This header file declare the class "Board" and it's member functions.
// All the global value and preprocessor like #include or #define are also in this header file.
#include "Board.h"

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QStackedLayout.h>
#include <qdebug.h>
#include <QtMultimedia/QMediaPlayer>
#include <QMouseEvent>
#include <QAbstractButton>
#include <QGuiApplication>
#include <QVector>
#include <QMessageBox>
#include <thread>
#include <chrono>

class MineSweeper : public QMainWindow
{
	Q_OBJECT

private:
	// Class for ui
	Ui::MineSweeperClass ui;

	// Class for board
	Board gBoard;

	// Qt element to set the ui size
	QGridLayout* gMap;

	// Qt element to change the status at the bottom of the ui
	QLabel* statusBarGameState;

	// 2d vector to store button pointers
	QVector<QVector<QPushButton*>> field;

	// Create a player.
	QMediaPlayer* musicPlayer = new QMediaPlayer;

public Q_SLOTS:

public:
	// Constructor
	MineSweeper(QWidget* parent = nullptr);

	// Destructor
	~MineSweeper() {}

	// Intent: Print game board when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printGameBoardActionTriggered();

	// Intent: Print game answer when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printGameAnswerActionTriggered();

	// Intent: Print game state when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printGameStateActionTriggered();

	// Intent: Print bomb count when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printBombCountActionTriggered();

	// Intent: Print flag count when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printFlagCountActionTriggered();

	// Intent: Print open blank count when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printOpenBlankCountActionTriggered();

	// Intent: Print remain blank count when the action triggered.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void printRemainBlankCountActionTriggered();

	// Intent: Load the map when the load button clicked.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void loadButtonClicked();

	// Intent: To start the game, change the page and create the button in the gui when the start game button clicked.
	// Pre: Input nothing.
	// Post: The function returns nothing.
	void startGameButtonClicked();

	// Intent: Show the icon of specific button.
	// Pre: The variable row and col must have a value.
	// Post: The function returns nothing.
	void showIcon(int row, int col);

	// Intent: To set the button enable to click, show icon and diffuse when the button in the game left clicked.
	// Pre: The variable row and col and the reference of QPushButton button must have a value.
	// Post: The function returns nothing.
	void leftClick(QPushButton* button, int row, int col);

	// Intent: To diffuse the surrounding coordinates when the button in the game clicked.
	// Pre: The variable row and col must have a value.
	// Post: The function returns nothing.
	void diffuse(int row, int col);

	// Intent: To set flag, question mark or blank when the button in the game right clicked.
	// Pre: The variable row and col must have a value.
	// Post: The function returns nothing.
	void rightClick(int row, int col);

	// Intent: To get the right click event and get the row and column of the button by judge the position.
	// Pre: The reference of QMouseEvent e must have a value.
	// Post: The function returns nothing.
	void mousePressEvent(QMouseEvent* e);
};