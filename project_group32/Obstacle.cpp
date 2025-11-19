#include"Obstacle.h"
#include"map.h"
#include"character.h"
#include<string>


Obstacle::Obstacle(const char symbol, const std::string& name, int X, int Y) : symbol(symbol), name(name), x(X), y(Y) {};

char Obstacle::getSymbol() const { return symbol; }

int Obstacle::getX() const { return x; }

int Obstacle::getY() const { return y; }

void Obstacle::applyEffect(character& someone, Map& chessBoard) {

	if (name == "supplement") {

		// 回血
		int healAmount = 30;
		someone.obstacleHeal(healAmount);
	}

	if (name == "plus") {

		//攻擊力加成 
		int plusAmount = 20;
		someone.obstaclePlus(plusAmount);
	}

}