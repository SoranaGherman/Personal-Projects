#include "Service.h"

Service::Service(Repository<Road>* reporters, Repository<Driver>* drivers) :
	reporters{ reporters }, drivers{ drivers }
{
}

std::vector<Road> Service::getAllReports()
{
	return this->reporters->getAll();
}

std::vector<Driver> Service::getAllDrivers()
{
	return this->drivers->getAll();
}

void Service::addReport(std::string desc, std::string curLoc, Driver d)
{
	Road r{desc, d.getName(), curLoc, "not_validated"};
	this->reporters->addElement(r);
	this->notify();
}

void Service::validateReport(std::string name, std::string descr)
{
	std::vector<Road> getData = this->reporters->getAll();
	int ok = 0;
	
	for (int i = 0; i < getData.size() && !ok; i++)
	{
		if (name == getData[i].getReporter() && getData[i].getDescription() == descr)
			this->reporters->updateReport(i), ok = 1;
		
	}
	std::vector<Driver> getDataD = this->drivers->getAll();
	ok = 0;

	for (int i = 0; i < getDataD.size() && !ok; i++)
	{
		if (name == getDataD[i].getName())
			this->drivers->updateScore(i);
			
	}
	
	this->notify();
}
