#pragma once
#include<string>
#include<vector>

class Map;
class Team;
class Obstacle;

class character {
protected:
	//名字、血量、攻擊、防禦、速度
	char symbol;
	std::string name;
	int origin_healthPoints;
	int current_healthPoints;
	int attackPoints;
	int defensePoints;
	int speedPoints;
	int x;  // 角色在方格地圖上的x、y座標 
	int y;
	std::vector<size_t> canAttackIndex;
public:
	//Constructor
	character();
	character(const char charSymbol, const std::string& charName, int origin_HP, int current_HP, int charAttack, int charDefense, int charSpeed, int x, int y);

	//取得基本資料函數
	char getSymbol() const;
	std::string getName() const;
	int get_current_HP() const;
	int get_origin_HP() const;
	int getAttackPoints() const;
	int getDefensePoints() const;
	int getSpeedPoints() const;
	int getX() const;
	int getY() const;

	// 顯示基本資料
	void displayInfo(const std::vector<character*>& team, int index);
	// 傷害
	void takeDamage(Map& chessBoard, int damage, int index, Team& temp);

	// 攻擊
	void attack(int index, Team& temp, Map& chessBoard);
	// 移動角色
	virtual void move(Map& chessBoard, Team& otherTeam) {
	};
	// 確認是否在攻擊範圍內
	virtual bool checkCharacter(character& character) const = 0;

	void checkObstacle(std::vector<Obstacle>& allObstacles, Map& chessBoard);

	void obstacleHeal(int amount);

	void obstaclePlus(int amount);

	// 發送可供attack的對象的prompt
	void chooseToAttack(const std::vector<character*>& team);
};

class Wizard1 : public character {
private:

public:
	Wizard1(int x, int y);

	bool checkCharacter(character& character) const;

	void move(Map& chessBoard, Team& otherTeam);
};

class Wizard2 : public character {
private:

public:
	Wizard2(int x, int y);
	bool checkCharacter(character& character) const;

	void move(Map& chessBoard, Team& otherTeam);
};

class Knight1 : public character {
private:

public:
	Knight1(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};


class Knight2 : public character {
private:


public:
	Knight2(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};

class Archer1 : public character {
private:

public:
	Archer1(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};

class Archer2 : public character {
private:

public:
	Archer2(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};

class Tank1 : public character {
private:

public:
	Tank1(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};

class Tank2 : public character {
private:

public:
	Tank2(int x, int y);
	bool checkCharacter(character& character) const;
	void move(Map& chessBoard, Team& otherTeam);
};