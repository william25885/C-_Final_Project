#pragma once
#include<vector>
#include<cstddef>

class character;



class Team {
private:
	std::vector<character*> members;
	bool teamMark;
public:
	Team();
	~Team();
	
	std::size_t getSize() const;

	character& operator[](std::size_t index) const;

	
	const std::vector<character*>& getMembers() const;

	void setTeamMark();

	void addClassWizard1(int x, int y);

	void addClassWizard2(int x, int y);

	void addClassArcher1(int x, int y);

	void addClassArcher2(int x, int y);

	void addClassTank1(int x, int y);

	void addClassTank2(int x, int y);

	void addClassKnight1(int x, int y);

	void addClassKnight2(int x, int y);

	
	bool getteamMark();

	bool allMembersDead() const;
};

