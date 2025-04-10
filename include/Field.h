#pragma once

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Field { // a class that implements methods for working with the field
public:
	vector<vector<char>> field;  // a two-dimensional array that is a field matrix

	Field(const int x, const int y); // declaring a constructor with two parameters
	void InitializeField(); // declaring a field initialization function
	void PrintField(); // declaring the print field function to the console
};