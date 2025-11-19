#include"character.h"
#include"exception.h"
#include"map.h"
#include"Team.h"
#include"Obstacle.h"
#include<string>
#include<vector>
#include<iostream>
#include<algorithm>

character::character() : symbol('N'), name("None"), origin_healthPoints(0), current_healthPoints(0), attackPoints(0), defensePoints(0), speedPoints(0), x(0), y(0) {}

character::character(const char charSymbol, const std::string& charName, int origin_HP, int current_HP, int charAttack, int charDefense, int charSpeed, int x, int y) : symbol(charSymbol), name(charName), origin_healthPoints(origin_HP), current_healthPoints(current_HP), attackPoints(charAttack), defensePoints(charDefense), speedPoints(charSpeed), x(x), y(y) {}

char character::getSymbol() const { return symbol;}

std::string character::getName() const { return name; }

int character::get_current_HP() const { return current_healthPoints; }

int character::get_origin_HP() const { return origin_healthPoints; }

int character::getAttackPoints() const { return attackPoints; }

int character::getDefensePoints() const { return defensePoints; }

int character::getSpeedPoints() const { return speedPoints; }

int character::getX() const { return x; }

int character::getY() const { return y; }

void character::displayInfo(const std::vector<character*>& team, int index) {
	std::cout << "member_number " << index << ',' << "Name: " << name << std::endl;
	std::cout << "HP: " << current_healthPoints << "/" << origin_healthPoints << std::endl;
	std::cout << "Attack: " << attackPoints << std::endl;
	std::cout << "current position (x , y) : " << "(" << getX() << "," << getY() << ")" << std::endl;
}

void character::chooseToAttack(const std::vector<character*>& team) {
	std::vector<size_t> tempAttackIndex;
	for (size_t i = 0; i < team.size(); i++) {
		if (checkCharacter(*(team[i])) == true) {
			if (team[i]->get_current_HP() == 0) {
				continue;
			}
			else {
				tempAttackIndex.push_back(i);
			}
		}
	}
	
	if (tempAttackIndex.empty() == true) {
		return;
	}
	else {
		std::cout << "You can attack: ";
		canAttackIndex = tempAttackIndex;
		for (size_t i = 0; i < tempAttackIndex.size(); i++) {
			std::cout << tempAttackIndex[i] << ',' << team[tempAttackIndex[i]]->getName() << " ";
		}
		std::cout << '\n';
		return;
	}
}

void character::attack(int index, Team& temp, Map& chessBoard) {
	temp[index].takeDamage(chessBoard, attackPoints, index, temp);
}

void character::takeDamage(Map& chessBoard, int damage, int index, Team& temp) {
	current_healthPoints -= damage;
	if (current_healthPoints <= 0) {
		current_healthPoints = 0;
		chessBoard.cleanCharacter(*this);
		std::cout << index << ',' << name << " is DEAD! " << std::endl;
	}
	else {
		std::cout << index << ',' << name << " received damage points: " << damage << " Current Health Point: " << current_healthPoints << std::endl;
	}
}


void character::obstacleHeal(int amount) {

	int old_healthPoints = current_healthPoints;
	int new_healthPoints = current_healthPoints + amount;
	current_healthPoints = std::min(new_healthPoints, origin_healthPoints);
	std::cout << name << " restored health points: " << current_healthPoints - old_healthPoints << " Current Health Point : " << current_healthPoints << std::endl;
}

void character::obstaclePlus(int amount) {

	this->attackPoints += amount;

	std::cout << name << " gain an power up, increase " << amount << " attack points, Current attack points is : " << attackPoints << std::endl;
}


void character::checkObstacle(std::vector<Obstacle>& allObstacles, Map& chessBoard) {
	for (auto iter = allObstacles.begin(); iter != allObstacles.end(); ) {

		int obstacleX = iter->getX();
		int obstacleY = iter->getY();

		if (x == obstacleX && y == obstacleY) {
		
			iter->applyEffect(*this, chessBoard);

		
			chessBoard.cleanObstacle(*iter);
			iter = allObstacles.erase(iter); 
		}
		else {
			++iter;
		}
	}
}


Wizard1::Wizard1(int x, int y) : character('W', "Wizard1", 80, 80, 100, 5, 8, x, y) {}

bool Wizard1::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 2 && abs(y - character.getY()) <= 2) {
		return true;
	}
	return false;
}

void::Wizard1::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 6;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 6.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Wizard2::Wizard2(int x, int y) : character('w', "Wizard2", 80, 80, 100, 5, 8, x, y) {}

bool Wizard2::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 2 && abs(y - character.getY()) <= 2) {
		return true;
	}
	return false;
}

void::Wizard2::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 6;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 6.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Knight1::Knight1(int x, int y) : character('K', "Knight1", 180, 180, 60, 3, 5, x, y) {}

bool Knight1::checkCharacter(character& character) const {
	if((abs(x - character.getX()) <= 2 && abs(y - character.getY()) == 0) or (abs(x - character.getX()) == 0 && abs(y - character.getY()) <= 2) ){
        return true;
    }
    return false;
}

void Knight1::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 5;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 5.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Knight2::Knight2(int x, int y) : character('k', "Knight2", 180, 180, 60, 3, 5, x, y) {}

bool Knight2::checkCharacter(character& character) const{
	if((abs(x - character.getX()) <= 2 && abs(y - character.getY()) == 0) or (abs(x - character.getX()) == 0 && abs(y - character.getY()) <= 2) ){
        return true;
    }
    return false;
}

void Knight2::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 5;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 5.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Archer1::Archer1(int x, int y) : character('A', "Archer1", 80, 80, 100, 1, 7, x, y) {}

bool Archer1::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 2 && abs(y - character.getY()) <= 2) {
		return true;
	}
	return false;
}

void Archer1::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 6;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 6.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Archer2::Archer2(int x, int y) : character('a', "Archer2", 80, 80, 100, 1, 7, x, y) {}

bool Archer2::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 2 && abs(y - character.getY()) <= 2) {
		return true;
	}
	return false;
}

void Archer2::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 6;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 6.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Tank1::Tank1(int x, int y) : character('T', "Tank1", 220, 220, 45, 10, 10, x, y) {}

bool Tank1::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 1 && abs(y - character.getY()) <= 1) {
		return true;
	}
	return false;
}

void Tank1::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 4;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 4.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}

Tank2::Tank2(int x, int y) : character('t', "Tank2", 220, 220, 45, 10, 10, x, y) {}

bool Tank2::checkCharacter(character& character) const {
	if (abs(x - character.getX()) <= 1 && abs(y - character.getY()) <= 1) {
		return true;
	}
	return false;
}

void Tank2::move(Map& chessBoard, Team& otherTeam) {
	const int MAX_DIMENSION = 15;
	const int MAX_MOVE_SUM = 4;
	bool moveCompleted = false;

	while (!moveCompleted) {
		try {
			std::string input;
			std::cout << "Your Move (attack or move): ";
			std::cin >> input;
			chessBoard.cleanCharacter(*this);

			if (input == "attack") {
				int attackIndex;
				std::cout << "Enter attack index: ";
				std::cin >> attackIndex;
				attack(attackIndex, otherTeam, chessBoard);
				chessBoard.placeCharacter(this);
				moveCompleted = true;
			}

			else if (input == "move") {
				int moveX = 0, moveY = 0;
				std::cout << "Enter move coordinates (x y): ";
				std::cin >> moveX >> moveY;

				if (abs(moveX) + abs(moveY) > MAX_MOVE_SUM) {
					throw OutOfBoundsException("Move exceeds maximum allowed distance of 4.");
				}

				if (abs(moveX) + abs(moveY) < 1){
                    throw OutOfBoundsException("Move at least 1 grid.");
                }

				int targetX = x + moveX;
				int targetY = y + moveY;

				if (targetX < 0 || targetX >= MAX_DIMENSION || targetY < 0 || targetY >= MAX_DIMENSION) {
					throw OutOfBoundsException("Target position is out of bounds.");
				}

				if (chessBoard.isCellOccupied(targetX, targetY)) {
					throw OccupiedCellException("Cell is occupied!");
				}

				x = targetX;
				y = targetY;
				chessBoard.placeCharacter(this);
				std::cout << "New position: " << x << " " << y << std::endl;
				moveCompleted = true;
			}
			else {
				throw InvalidInputException("Invalid action input!");
			}
		}
		catch (const InvalidInputException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OccupiedCellException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
		catch (const OutOfBoundsException& e) {
			std::cout << "Error: " << e.what() << " Please try again." << std::endl;
		}
	}
}


