#pragma once

#include "../include/Field.h"


class Game_Of_Life { // a class that implements methods for working with cells
public:
	bool FlagEquality = 0; // a flag that changes when the current iteration of the field matches the previous one.In this case, the game stops as a stable configuration appears.
	int NextLiveCells(int i, int j, vector<vector<char>>& field); // declaring a method that checks the number of live cells around each cell
	void NextGeneration(Field& my_field); // declaring a method that generates a new generation of cells or a new iteration of the field
	int CountLiveCellsOnFileld(vector<vector<char>>& field); // declaring a method that generates a new generation of cells counts the number of living cells in a field
	void Start(const int height, const int width); // declaring the method that runs the program

};
