#pragma once

#include "Repository.h"

class Service
{
public:
	Service(Repository<Astronomer>* astronomers, Repository<Star>* stars);
	~Service() = default;

	std::vector<Astronomer> getAllAstronomers();
	std::vector<Star> getAllStars();
	std::vector<Star> getCertainStar(Astronomer a);
	int getStarsRepo();

	void addStar(Star& s);

private:
	Repository<Astronomer>* astronomers;
	Repository<Star>* stars;
};

