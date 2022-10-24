#include "Driver.h"

Driver::Driver(std::string name, std::string status, std::string location, int score):
	name{ name }, status{ status }, location{ location }, score{score}
{
}

std::string Driver::getName()
{
	return this->name;
}

std::string Driver::getStatus()
{
	return this->status;
}

std::string Driver::getLocation()
{
	return this->location;
}

int Driver::getScore()
{
	return this->score;
}

void Driver::setScore()
{
	this->score++;
}

void Driver::setStatus(std::string s)
{
	this->status = s;
}

std::ostream& operator<<(std::ostream& os, const Driver& d)
{
	return os << d.name << " " << d.status << " " << d.location << " " << d.score << "\n";
}

std::istream& operator>>(std::istream& is, Driver& d)
{
	return is >> d.name >> d.status >> d.location >> d.score;
}
