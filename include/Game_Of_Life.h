#pragma once

#include "../include/Field.h"


class Game_Of_Life { // a class that implements methods for working with cells
private:
	const int COUNT_LIVECELLS_OPTION1 = 2; // the number of living cells. Option 1
	const int COUNT_LIVECELLS_OPTION2 = 3; // the number of living cells. Option 2
	const int MINIMUM_NEIGHBORS = -1;// minimum neighbor position
	const int MAXIMUM_NEIGHBORS = 1;// maximum neighbor position
	const int OUR_CELL = 0;// the position of our cell
	int NextLiveCells(int i, int j, const Field& board); // declaring a method that checks the number of live cells around each cell
public:
	bool FlagEquality = 0; // a flag that changes when the current iteration of the field matches the previous one.In this case, the game stops as a stable configuration appears.
	void NextGeneration(Field& my_field); // declaring a method that generates a new generation of cells or a new iteration of the field
	int CountLiveCellsOnFileld(Field& board); // declaring a method that generates a new generation of cells counts the number of living cells in a field
	void Start(); // declaring the method that runs the program
};