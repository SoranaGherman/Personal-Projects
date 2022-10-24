#pragma once

#include "Repository.h"
#include "Observer.h"

class Service: public Subject
{
public:
	Service(Repository<Road>* reporters, Repository<Driver>* drivers);
	~Service() = default;

	std::vector<Road> getAllReports();
	std::vector<Driver> getAllDrivers();
	void addReport(std::string desc, std::string curLoc, Driver d);
	void validateReport(std::string name, std::string descr);

private:
	Repository<Road>* reporters;
	Repository<Driver>* drivers;
};

