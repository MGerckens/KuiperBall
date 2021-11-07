#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#define BOARD_SIZE 9


using std::cin;
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

class Minesweeper {
private:
	char grid[BOARD_SIZE][BOARD_SIZE];
	bool revealed[BOARD_SIZE][BOARD_SIZE];
	bool lost = false;
	bool valid = false;
	
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
		return count;
	}

public:
	Minesweeper() {
		srand(time(NULL));
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				int mine = rand() % 99;
				if (mine < 15) { grid[i][j] = 'X'; }
			}
		}
		//cout << "done placing mines \n\n\n";
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (grid[i][j] != 'X') { grid[i][j] = '0' + get_num(i, j); }
				revealed[i][j] = false;
			}
		}
	}
	string getResult() {
		stringstream outbuffer;
		if (lost) { return "L"; }
		if (!valid) { return "I"; }
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (!revealed[i][j]) { outbuffer << "-"; }
				else { outbuffer << grid[i][j]; }
				outbuffer << " ";
			}
			outbuffer << endl;
		}
		return outbuffer.str();
	}
	void process(int x, int y) {
		if (revealed[x][y]) {
			valid = false;
			return;
		}
		if(grid[x][y] != 'X') {
			//tempy = BOARD_SIZE - stoi(position.substr(2, 1)) - 1;
			//tempx = stoi(position.substr(0, 1)) - 1;
			//cout << grid[x][y] << endl;
			revealed[x][y] = true;
			valid = true;
			

			//for (int i = 0; i < BOARD_SIZE; i++) { for (int j = 0; j < BOARD_SIZE; j++) { print_point(i, j); } cout << endl; }
			
			//valid = false;
		}
		else {
			lost = true;
		}
	}

};