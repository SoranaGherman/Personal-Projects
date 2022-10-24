#include "Road.h"

Road::Road(std::string description, std::string reporter, std::string location, std::string validated) :
	description{ description }, reporter{ reporter }, location{ location }, validated{ validated }
{
}

std::string Road::getDescription()
{
	return this->description;
}

std::string Road::getReporter()
{
	return this->reporter;
}

std::string Road::getLocation()
{
	return this->location;
}

std::string Road::getValidated()
{
	return this->validated;
}

void Road::setValidated()
{
	this->validated = "validated";
}

std::ostream& operator<<(std::ostream& os, const Road& r)
{
	return os << r.description << " " << r.reporter << " " << r.location << " " << r.validated << "\n";
}

std::istream& operator>>(std::istream& is, Road& r)
{
	return is >> r.description >> r.reporter >> r.location >> r.validated;
}
