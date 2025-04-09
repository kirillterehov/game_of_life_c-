#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Field { // a class that implements methods for working with the field
public:
	int Height;// field height
	int Width;// field width
	vector<vector<char>> field;  // a two-dimensional array that is a field matrix

	Field(int x, int y); // declaring a constructor with two parameters
	void InitializeField(); // declaring a field initialization function
	void PrintField(); // declaring the print field function to the console
};