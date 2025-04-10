#include "../include/Field.h"
#include "../include/Variable.h"
using namespace Variable;

Field::Field(const int x, const int y) {} // a constructor 


void Field::InitializeField() { // implementation of the field initialization function
	srand(time(0)); // Initialization of a random number generator that takes as a parameter the unix system time that has passed since January 1, 1970
	field = vector<vector<char>>(HEIGHT); // initializing a field
	for (int i = 0; i < HEIGHT; i++) {
		field[i] = vector<char>(WIDTH); // initialize each line
		for (int j = 0; j < WIDTH; j++) {
			field[i][j] = (rand() % 2); // initialize each element with a random number 0 or 1.
		}
	}
}


void Field::PrintField() { // implementation of the field print function
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
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