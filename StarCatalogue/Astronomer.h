#pragma once

#include <iostream>

class Astronomer
{
public:
	Astronomer() = default;
	Astronomer(std::string name, std::string constellation);
	~Astronomer() = default;

	std::string getName();
	std::string getConstellation();

	friend std::ostream& operator<<(std::ostream& os, const Astronomer& a);
	friend std::istream& operator>>(std::istream& is, Astronomer& a);

private:
	std::string name;
	std::string constellation;
};
