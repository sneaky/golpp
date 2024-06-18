#include <iostream>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <thread>

using namespace std;

const int width = 80;
const int height = 40;

vector<vector<char>> initializeGrid() {
	vector<vector<char>> grid(height, vector<char>(width));
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			grid[i][j] = '.';
		}
	}

	grid[1][2] = 'O';
	grid[2][3] = 'O';
	grid[3][1] = 'O';
	grid[3][2] = 'O';
	grid[3][3] = 'O';

	return grid;
}

void printGrid(vector<vector<char>> grid) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			cout << grid[i][j];
		}
		cout << endl;
	}
}

void clearScreen() {
	system("clear");
}

int countAliveNeighbors(vector<vector<char>> grid, int x, int y) {
	int count = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (i == 0 && j == 0) continue;
			int ni = (y + i + height) % height;
			int nj = (x + j + width) % width;
			if (grid[ni][nj] == 'O') count++;
		}
	}
	return count;
}

vector<vector<char>> nextGeneration(vector<vector<char>> grid) {
	vector<vector<char>> newGrid(height, vector<char>(width));
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			newGrid[i][j] = '.';
		}
	}
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int aliveNeighbors = countAliveNeighbors(grid, x, y);
			if (grid[y][x] == 'O') {
				if (aliveNeighbors < 2 || aliveNeighbors > 3) {
					newGrid[y][x] = '.';
				} else {
					newGrid[y][x] = 'O';
				}
			} else {
				if (aliveNeighbors == 3) {
					newGrid[y][x] = 'O';
				}
			}
		}
	}

	return newGrid;
}

int main() {
	vector<vector<char>> grid = initializeGrid();
	printGrid(grid);

	for (int i = 0; i < 50; i++) {
		clearScreen();
		cout << "Generation: " << i << endl;
		printGrid(grid);
		grid = nextGeneration(grid);
		this_thread::sleep_for(chrono::milliseconds(250));
	}
	return 0;
}
