#include "Star.h"

Star::Star(std::string name, std::string constelaltion, int RA, int Dec, int diameter) :
    name{ name }, constellation{ constelaltion }, RA{ RA }, Dec{ Dec }, diameter{ diameter }
{
}

std::string Star::getName()
{
    return this->name;
}

std::string Star::getConstellation()
{
    return this->constellation;
}

int Star::getRA()
{
    return this->RA;
}

int Star::getDec()
{
    return this->Dec;
}

int Star::getDiameter()
{
    return this->diameter;
}

std::ostream& operator<<(std::ostream& os, const Star& s)
{
    return os << s.name << " " << s.constellation << " " << s.RA << " " << s.Dec << " " << s.diameter << "\n";
}

std::istream& operator>>(std::istream& is, Star& s)
{
    return is >> s.name >> s.constellation >> s.RA >> s.Dec >> s.diameter;
}
