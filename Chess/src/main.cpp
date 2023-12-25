// File: main.cpp
// Author: B11130038, B11130005, B11132002, B11115041
// Create Date : 2023/05/06
// Editor : B11130038, B11130005, B11132002, B11115041
// Update Date : 2023/05/06
// Description : This C++ program allows user to play chess.

#include "ViewManager.h"
#include "definition.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	ViewManager w;

	// Set the windows toolbar icon and the icon in the upper left corner of the application.
	w.setWindowIcon(QIcon(MAIN_WINDOW_ICON));

	// Show GUI.
	w.show();

	// Proccess the GUI until quit.
	return a.exec();
}
