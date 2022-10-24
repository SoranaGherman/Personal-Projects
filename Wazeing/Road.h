#pragma once

#include <iostream>

class Road
{
public:
	Road() = default;
	Road(std::string description, std::string reporter, std::string location, std::string validated);
	~Road() = default;

	std::string getDescription();
	std::string getReporter();
	std::string getLocation();
	std::string getValidated();

	void setValidated();

	friend std::ostream& operator<<(std::ostream& os, const Road& r);
	friend std::istream& operator>>(std::istream& is, Road& r);

private:
	std::string description;
	std::string reporter;
	std::string location;
	std::string validated;
};

