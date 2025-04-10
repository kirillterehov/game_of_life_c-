#include "../include/Game_Of_Life.h"
#include "../include/Variable.h"
#include <chrono>
#include <thread>
using namespace Variable;


int Game_Of_Life::NextLiveCells(int i, int j, vector<vector<char>>&field) {
	int live = 0;
	int x = 0;
	int y = 0;
	for (int m = MINIMUM_NEIGHBORS; m <= MAXIMUM_NEIGHBORS; m++) { // we check the neighbors around each cell
		for (int n = MINIMUM_NEIGHBORS; n <= MAXIMUM_NEIGHBORS; n++) { // we check the neighbors around each cell
			if (m == OUR_CELL && n == OUR_CELL) {  // skip the cell itself
				continue;
			}
			else {
				x = (i + m + HEIGHT) % HEIGHT; // we calculate the x coordinate for each neighboring cell, around the cell we are considering. The coordinates of the cell in question are the variables i and j
				y = (j + n + WIDTH) % WIDTH; // we calculate the y coordinate for each neighboring cell, around the cell we are considering. The coordinates of the cell in question are the variables i and j
				live += int(field[x][y]); // we take the integer value of the field array element. It can be 0 or 1
			}
		}
	}
	return live; // the number of living cells around the cell
}

void Game_Of_Life::NextGeneration(Field& board) { // Creating a reference to an object of the Field class. Since my field is public, I can use the link to change it. If value transfer had been used, then nothing would have worked. Since in my case, I'm overwriting the field itself, which I have declared in the Field class
	FlagEquality = false;
	vector<vector<char>> new_field(HEIGHT); // initializing a new array
	for (int i = 0; i < HEIGHT; i++) {
		new_field[i] = vector<char>(WIDTH);
		for (int j = 0; j < WIDTH; j++) {
			int liveCells = NextLiveCells(i, j, board.field); // Access the member variable named field of the object named board. From class Field

			if (board.field[i][j] == INT_LIVE_CELL && liveCells == COUNT_LIVECELLS_OPTION1 || liveCells == COUNT_LIVECELLS_OPTION2) { // if a cell is alive and the number of neighbors around it is 2 or 3, then this cell will also be alive in the new array.
				new_field[i][j] = INT_LIVE_CELL;
			}
			else if (board.field[i][j] == INT_DEATH_CELL && liveCells == COUNT_LIVECELLS_OPTION2) { // if a cell in the array is dead and the number of living cells around it is 3, then the cell in the new array will be alive.
				new_field[i][j] = INT_LIVE_CELL;
			}
			else {
				new_field[i][j] = INT_DEATH_CELL; // otherwise, the cell is dead in the new array.
			}
		}
	}

	if (board.field == new_field) { // we check that our new array is equal to the old array
		FlagEquality = TRUE_FLAGE_QUALITY; // we make the flag equal to 1
	}
	else {
		board.field = new_field; // overwriting our field.
	}
}

int Game_Of_Life::CountLiveCellsOnFileld(vector<vector<char>>& field) {// We pass the field parameter via the link in order to work directly with our field and not with its copy.
	int Cells = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (int(field[i][j]) == INT_LIVE_CELL) {
				Cells++; // we count the number of living cells in the field.
			}
		}
	}
	return Cells;
}



void Game_Of_Life::Start(const int height, const int width) {
	int Generation = 0; // generation counter
	int CountLiveCells = 0; // live cell counter
	int MaxGeneration = 1500; // the maximum number of generations that the game lives in
	int all_cells_dead = 0; // flag all cells dead
	int our_sleep = 500; // DELAY BETWEEN ITERATIONS
	Field board(HEIGHT, WIDTH); // creating an object of the Field class
	board.InitializeField(); // initializing an object of the Field class
	board.PrintField(); // printing the field
	while (Generation < MaxGeneration) {
		NextGeneration(board); // generating a new generation of cells
		board.PrintField(); // printing the field
		this_thread::sleep_for(chrono::milliseconds(our_sleep)); // There is a delay of 100 milliseconds so that the field configuration does not change quickly.
		Generation++; // increasing the generation counter
		CountLiveCells = CountLiveCellsOnFileld(board.field); // counting the number of living cells. As an array, we pass a member variable named field to an object named board.From the class field. Since the transfer is done by reference, we work with our field from the class
		if (CountLiveCells == all_cells_dead || FlagEquality == TRUE_FLAGE_QUALITY) { // if the flag is 1 or the number of live cells is 0, then abort
			break;
		}
	}
}
