#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#define BOARD_SIZE 9
#define MINE_COUNT 10


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
	void floodfill(int x, int y) {
		if (x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE || revealed[x][y] == true) { return; }
		revealed[x][y] = true;
		if (grid[x][y] != '0' ) { return; }
		floodfill(x - 1, y);
		floodfill(x + 1, y);
		floodfill(x, y - 1);
		floodfill(x, y + 1);
		return;
	}
	bool check_win() {
		int count = 0;
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				if (grid[i][j] != 'X' && revealed[i][j] == true) {
					count++;
				}
			}
		}
		return count == (BOARD_SIZE * BOARD_SIZE) - MINE_COUNT;
	}
public:
	Minesweeper() {
		int x, y;
		srand(time(NULL));
		for (int i = 0; i < MINE_COUNT; i++) {
			while (true) {
				x = rand() % 8;
				y = rand() % 8;
				if (grid[x][y] != 'X') {
					break;
				}
			}
			grid[x][y] = 'X';
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
		if (check_win()) {return "You Win!\n";}
		if (lost) { return "Game Over!\n"; }
		if (!valid) { return "Invalid Move, Please try again\n"; }
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
			floodfill(x, y);
			valid = true;
		}
		else {
			lost = true;
		}
	}

};