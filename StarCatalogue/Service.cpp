#include "Service.h"

Service::Service(Repository<Astronomer>* astronomers, Repository<Star>* stars) :
	astronomers{ astronomers }, stars{ stars }
{
}

std::vector<Astronomer> Service::getAllAstronomers()
{
	return this->astronomers->getAll();
}

std::vector<Star> Service::getAllStars()
{
	return this->stars->getAll();
}

std::vector<Star> Service::getCertainStar(Astronomer a)
{
	std::vector<Star> v = this->stars->getAll();
	std::vector<Star> res;
	for (auto obj : v)
	{
		if (obj.getConstellation() == a.getConstellation())
			res.push_back(obj);
	}
	return res;
}

int Service::getStarsRepo()
{
	return this->stars->getSize();
}

void Service::addStar(Star& s)
{
	this->stars->addElement(s);
}
