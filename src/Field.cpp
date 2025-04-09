#include "../include/Field.h"
#include "../include/Variable.h"
using namespace Variable;

Field::Field(int x, int y) : Height(x), Width(y) {} // a constructor that initializes the height and width of the field in advance


void Field::InitializeField() { // implementation of the field initialization function
	srand(time(0)); // Initialization of a random number generator that takes as a parameter the unix system time that has passed since January 1, 1970
	field = vector<vector<char>>(Height); // initializing a field
	for (int i = 0; i < Height; i++) {
		field[i] = vector<char>(Width); // initialize each line
		for (int j = 0; j < Width; j++) {
			field[i][j] = (rand() % 2); // initialize each element with a random number 0 or 1.
		}
	}
}


void Field::PrintField() { // implementation of the field print function
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (field[i][j] == 1) { // if the number is 1, then print the symbol of a live cell, otherwise a dead one.
				cout << LIVECELL;
			}
			else {
				cout << DEATHCELL;
			}
		}
		cout << endl;
	}
}