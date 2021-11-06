#include <iostream>
#include <cstdlib>
#include <string>

#define BOARD_SIZE 8

using namespace std;

bool revealed[BOARD_SIZE][BOARD_SIZE];
char grid[BOARD_SIZE][BOARD_SIZE];

int get_num(int x, int y);
void print_point(int x, int y) {
	cout << " ";
	if (!revealed[x][y]) { cout << "-"; }
	else { cout << grid[x][y]; }
}

int main() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			revealed[i][j] = false;
			grid[i][j] = ' ';
		}
	}
	srand(time(NULL));
	int length = 6;
	int height = 6;
	int tempx = 0;
	int tempy = 0;
	int mine = 0;
	int counter = 0;
	bool lose = false;
	bool valid = false;
	string position = "";
	//cout << "Please enter the height of the grid: ";
	//cin >> length;
	//cout << "Please enter the length of the grid: ";
	//cin >> height;
	//int x = length;
	//int y = height;
	//char** grid = new char* [x];
	//for (int i = 0; i < x; i++) { grid[i] = new char[y]; }

	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			mine = rand() % 99;
			if (mine < 15) { grid[i][j] = 'X'; }
		}
		//cout << endl;
	}
	cout << "done placing mines \n\n\n";
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (grid[i][j] != 'X') { grid[i][j] = '0' + get_num(i, j); }
			//cout << grid[i][j];
		}
		cout << endl;
	}

	while (lose == false) {
		counter = 0;
		while (valid == false) {
			cout << "Enter the position you would like to uncover [x y]: ";
			cin >> tempy >> tempx; //swapped
			//tempy = BOARD_SIZE - stoi(position.substr(2, 1)) - 1;
			//tempx = stoi(position.substr(0, 1)) - 1;
			cout << grid[tempx][tempy] << endl;
			if (!revealed[tempx][tempy]) { 
				revealed[tempx][tempy] = true;
				valid = true; 
			}
			else {
				cout << "Already revealed. Pick again." << endl;
				valid = false;
			}
			
			for (int i = 0; i < BOARD_SIZE; i++) { for (int j = 0; j < BOARD_SIZE; j++) { print_point(i, j); } cout << endl; }
		}
		valid = false;
		
		if (grid[tempx][tempy] == 'X') { lose = true; }
		
		/*cout << "displaying grid \n\n\n";
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (lose == false) {
					cout << grid[i][j]; 
				}
				else {
					print_point(i, j);
				}
			}
			cout << endl;
		}*/
	}
	cout << "You lose!";
}

int get_num(int tempx, int tempy) {
	if (grid[tempx][tempy] == 'X') { return -1; }
	int count = 0;
	for (int i = tempx - 1; i <= tempx + 1; i++) {
		for (int j = tempy - 1; j <= tempy + 1; j++) {
			if (i < 0 || j < 0 || i >= BOARD_SIZE || j >= BOARD_SIZE) { continue; }
			if (grid[i][j] == 'X') {
				count++;
			}
		}
	}
	//cout << endl << "grid: " << grid[tempx - 1][tempy - 1] << endl;
	//if (tempx > 0 && tempy > 0 && grid[tempx - 1][tempy - 1] == 'X') { count++; }
	return count;
}