#pragma once
#include<vector>

class character;
class Obstacle;

class Map {
private:
	int rows;   // 地圖的行數
	int cols;   // 地圖的列數
	std::vector<std::vector<char> > map;  // 地圖的表示

public:
	Map(int rows, int cols);

	void draw() const;
	void cleanCharacter(character& character);
	void cleanObstacle(Obstacle& obstacle);
	void placeCharacter(const character* character);
	void placeObstacle(const Obstacle& obstacle);
	//    void removeObstacle(Obstacle& obstacle) ;
	bool isCellOccupied(int x, int y) const;
};