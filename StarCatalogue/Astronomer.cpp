#include "Astronomer.h"

Astronomer::Astronomer(std::string name, std::string constellation) :
    name{ name }, constellation{ constellation }
{
}

std::string Astronomer::getName()
{
    return this->name;
}

std::string Astronomer::getConstellation()
{
    return this->constellation;
}

std::ostream& operator<<(std::ostream& os, const Astronomer& a)
{
    return os << a.name << " " << a.constellation << "\n";
}

std::istream& operator>>(std::istream& is, Astronomer& a)
{
    return is >> a.name >> a.constellation;
}
