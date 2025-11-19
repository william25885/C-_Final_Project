#include <iostream>
#include <vector>
#include <cmath>
#include <string> 
#include <cstdlib> 
#include <stdexcept>
#include <set>
#include <random>
#include<map>
#include"message.h"
#include"exception.h"
#include"Obstacle.h"
#include"Team.h"
#include"character.h"
#include"map.h"
using namespace std;

void addToTeam(Team& temp, int& teamCnt) {
	map<string, int> characterAddCount;
	while (temp.getSize() < 3) {
		string characterName;
		int quantity = 0;
		int x, y;
		int space = 3 - temp.getSize();

		if (teamCnt == 0) {
			cout << "Which character do you want to add in team1? ( Wizard1, Knight1, Archer1, Tank1 )" << endl;
		}
		else if (teamCnt == 1) {
			cout << "Which character do you want to add in team2? ( Wizard2, Knight2, Archer2, Tank2 )" << endl;
		}

		bool validInput = false;

		while (!validInput) {
			try {
				cin >> characterName;
				if (characterName != "Wizard1" && characterName != "Wizard2" && characterName != "Knight1" && characterName != "Knight2" && characterName != "Archer1" && characterName != "Archer2" && characterName != "Tank1" && characterName != "Tank2") {
					throw InvalidCharacterException("Invalid character type.");
				}

				cout << "You can at most add " << space << " characters." << endl;
				cout << "Quantity: ";
				cin >> quantity;

				if (quantity < 1 || quantity > space) {
					throw InvalidQuantityException("Invalid quantity. It must be between 1 and " + to_string(space) + ".");
				}

				if (characterAddCount[characterName] + quantity > 2) {
					throw InvalidQuantityException("Cannot add " + characterName + " more than twice.");
				}

				for (int i = 0; i < quantity; i++) {
					cout << "Location: ";
					cin >> x >> y;

					if ((2 < x && x < 12) || (2 < y && y < 12) || x > 14 || y > 14 || x < 0 || y < 0) {
						throw InvalidLocationException("Invalid location coordinates.");
					}


					if (characterName == "Wizard1") {
						temp.addClassWizard1(x, y);
					}
					else if (characterName == "Wizard2") {
						temp.addClassWizard2(x, y);
					}
					else if (characterName == "Knight1") {
						temp.addClassKnight1(x, y);
					}
					else if (characterName == "Knight2") {
						temp.addClassKnight2(x, y);
					}
					else if (characterName == "Archer1") {
						temp.addClassArcher1(x, y);
					}
					else if (characterName == "Archer2") {
						temp.addClassArcher2(x, y);
					}
					else if (characterName == "Tank1") {
						temp.addClassTank1(x, y);
					}
					else if (characterName == "Tank2") {
						temp.addClassTank2(x, y);
					}
				}

				characterAddCount[characterName] += quantity;
				validInput = true;
			}
			catch (const runtime_error& e) {
				cout << "Error: " << e.what() << " Please try again." << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}
	}

	teamCnt++;
}

int main() {
	Map chessBoard(15, 15);
	int teamCnt = 0;


	vector<Obstacle> All_obstacles;
	Obstacle sup1 = Obstacle('+', "supplement",4, 4);
	Obstacle plus1 = Obstacle('*', "plus", 10, 4);
	Obstacle sup2 = Obstacle('+', "supplement", 10, 9);
	Obstacle plus2 = Obstacle('*', "plus", 4, 9);
	All_obstacles.push_back(sup1);
	All_obstacles.push_back(plus1);
	All_obstacles.push_back(sup2);
	All_obstacles.push_back(plus2);


	//placeObstacle
	for (size_t i = 0; i < All_obstacles.size(); i++) {
		chessBoard.placeObstacle(All_obstacles[i]);
	}

	cout << "Characters Attack range: " << "\n";
	cout << "Wizard (square 4*4) " << "\n";
	cout << "Knight (cross 2*1 && 1*2) " << "\n";
	cout << "Tank (square 3*3)" << "\n";
	cout << "Archer (square 4*4)" << endl;

	chessBoard.draw();

	//set Team1 vector<character*> members
	Team team1;
	team1.setTeamMark();
	addToTeam(team1, teamCnt);
	
	Team team2;
	cout << "You cannot use team1's members' locations!!!!!!!" << endl;
	addToTeam(team2, teamCnt);


	// set Team2 vector<character*> members
	for (size_t i = 0; i < team1.getSize(); i++) {
		chessBoard.placeCharacter(&team1[i]);
	}

	for (size_t i = 0; i < team2.getSize(); i++) {
		chessBoard.placeCharacter(&team2[i]);
	}


	//Initial chess board
	cout << "Initial Chess Board:" << endl;
	chessBoard.draw();

	
	int turnCnt = 0;

	if (turnCnt == 0)
	{
		message1();
		message2();
		message3();
		cout << endl;
	}

	// Team loop
	while (!team1.allMembersDead() && !team2.allMembersDead()) {
		string check;

		for (size_t i = 0; i < 3; i++) {

			if (team1[i].get_current_HP() == 0) { continue; }

			else {
				cout << "Your team : Team1" << endl;

				
				team1[i].displayInfo(team1.getMembers(), i);

				
				team1[i].chooseToAttack(team2.getMembers());


				
				team1[i].move(chessBoard, team2);

				
				team1[i].checkObstacle(All_obstacles, chessBoard);

				cout << "\n\n\n\n\n\n\n\n\n\n";
				cout << "Chess Board after moving player:" << endl;
				chessBoard.draw();
			}


		}

		if (turnCnt == 0)
		{
			message4();
			cout << endl;
		}
		else if (turnCnt == 1)
		{
			message5();
			cout << endl;
		}
		else if (turnCnt == 2)
		{
			message6();
			cout << endl;
		}
		else if (turnCnt == 3)
		{
			message7();
			cout << endl;
		}

		turnCnt++;

		for (size_t i = 0; i < 3; i++) {
			if (team2[i].get_current_HP() == 0) {
				continue;
			}
			else {
				cout << "Your team : Team2" << endl;
				
				team2[i].displayInfo(team1.getMembers(), i);

				
				team2[i].chooseToAttack(team1.getMembers());

				
				team2[i].move(chessBoard, team1);

				
				team2[i].checkObstacle(All_obstacles, chessBoard);

				cout << "\n\n\n\n\n\n\n\n\n\n";
				cout << "Chess Board after moving player:" << endl;
				chessBoard.draw();
			}
		}
	}

	message8();
	cout << endl;

	return 0;
}