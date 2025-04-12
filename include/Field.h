#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Field { // a class that implements methods for working with the field
private:
	const char LIVECELL = 'o';         // The symbol of a living cell
	const char DEATHCELL = ' ';        // The symbol of a dead cell
	vector<vector<char>> field;  // a two-dimensional array that is a field matrix

public:
	Field();
	void InitializeField(); // declaring a field initialization function
	void PrintField(); // declaring the print field function to the console

	int getCell(int row, int col) const; // Getter for accessing a single cell
	void setCell(int row, int col, int value); // Setter for setting the value of a single cell
	const vector<vector<char>>& getField() const; // Getter for field
};