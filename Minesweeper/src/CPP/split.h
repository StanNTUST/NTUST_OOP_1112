#pragma once

// File: split.h
// Author: B11130005, B11130038, B11115021, B11132006
// Create Date : 2023/04/12
// Editor : B11130005
// Update Date : 2023/04/12
// Description : This header file define the split function in main.cpp.

#include <string>
#include <vector>

using namespace std;

// Intent: Split a string with separator and store the words into a string vector.
// Pre: Input a string, a string vector, and a char.
// Post: The function returns nothing.
void split(string str, vector<string>& splited, char separator) {
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