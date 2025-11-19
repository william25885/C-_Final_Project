#include"Team.h"
#include"character.h"
#include<vector>
#include<cstddef>

Team::Team() {
	teamMark = false;
};

Team::~Team() {
	for (character* member : members) {
		delete member;
	}
}

std::size_t Team::getSize() const {
	return members.size();
}

character& Team::operator[](std::size_t index) const {
	if (index < members.size()) {
		return *members[index];
	}
	else {
		//�V�ɳB�z�A�ݭ�
		return *members[0];
	}
}

const std::vector<character*>& Team::getMembers() const {
	return members;
}


void Team::setTeamMark() { teamMark = true; return; }

void Team::addClassWizard1(int x, int y) {
	character* newWizard = new Wizard1(x, y);  // ���] Wizard ���O���ŦX���غc�禡
	members.push_back(newWizard);
}

void Team::addClassWizard2(int x, int y) {
	character* newWizard = new Wizard2(x, y);  // ���] Wizard ���O���ŦX���غc�禡
	members.push_back(newWizard);
}

void Team::addClassArcher1(int x, int y) {
	character* newArcher = new Archer1(x, y);
	members.push_back(newArcher);
}

void Team::addClassArcher2(int x, int y) {
	character* newArcher = new Archer2(x, y);
	members.push_back(newArcher);
}

void Team::addClassTank1(int x, int y) {
	character* newTank = new Tank1(x, y);
	members.push_back(newTank);
}

void Team::addClassTank2(int x, int y) {
	character* newTank = new Tank2(x, y);
	members.push_back(newTank);
}

void Team::addClassKnight1(int x, int y) {
	character* newKnight = new Knight1(x, y);
	members.push_back(newKnight);
}

void Team::addClassKnight2(int x, int y) {
	character* newKnight = new Knight2(x, y);
	members.push_back(newKnight);
}

bool Team::getteamMark() { return teamMark; }

bool Team::allMembersDead() const {
	for (const character* member : members) {
		if (member->get_current_HP() > 0) {
			return false;  // �p�G������@�Ӧ�����q���� 0�A��^ false
		}
	}
	return true;
}