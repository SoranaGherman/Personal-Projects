#pragma once

#include <iostream>

class Star
{
public:
	Star() = default;
	Star(std::string name, std::string constelaltion, int RA, int Dec, int diameter);
	~Star() = default;

	std::string getName();
	std::string getConstellation();
	int getRA();
	int getDec();
	int getDiameter();


	friend std::ostream& operator<<(std::ostream& os, const Star& s);
	friend std::istream& operator>>(std::istream& is, Star& s);

private:
	std::string name;
	std::string constellation;
	int RA;
	int Dec;
	int diameter;
};
