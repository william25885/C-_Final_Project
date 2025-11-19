#include"map.h"
#include"Obstacle.h"
#include"character.h"
#include<vector>
#include<iostream>



Map::Map(int rows, int cols) : rows(rows), cols(cols), map(rows, std::vector<char>(cols, '.')) {}

bool Map::isCellOccupied(int x, int y) const {

	if (map[y][x] != '.' && map[y][x] != '*' && map[y][x] != '+') { return true; }
	else { return false; }
}

void Map::cleanCharacter(character& character) {
	int row = character.getY();
	int col = character.getX();

	// 檢查座標是否合法
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		map[row][col] = '.';
	}
}

void Map::cleanObstacle(Obstacle& obstacle) {
	int row = obstacle.getY();
	int col = obstacle.getX();

	// 檢查座標是否合法
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		if (map[row][col] != 'W' && map[row][col] != 'w' && map[row][col] != 'A' && map[row][col] != 'a' && map[row][col] != 'K' && map[row][col] != 'k' && map[row][col] != 'T' && map[row][col] != 't')
		{
			map[row][col] = '.';
		}
	}
}

void Map::placeCharacter(const character* character) {
	int row = character->getY();
	int col = character->getX();

	// 檢查座標是否合法
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		map[row][col] = character->getSymbol();
	}
}

void Map::placeObstacle(const Obstacle& obstacle) {
	int row = obstacle.getY();
	int col = obstacle.getX();

	// 檢查座標是否合法
	if (row >= 0 && row < rows && col >= 0 && col < cols) {
		map[row][col] = obstacle.getSymbol();
	}
}

void Map::draw() const {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << map[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}