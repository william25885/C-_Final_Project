#pragma once
#include<string>

class Map;
class character;

class Obstacle {
private:
	char symbol;
	std::string name;
	int x;
	int y;
public:
	Obstacle(const char symbol, const std::string& name, int X, int Y);
	char getSymbol() const;
	int getX() const;
	int getY() const;
	void applyEffect(character& someone, Map& chessBoard);
};