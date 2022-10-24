#pragma once

#include<iostream>

class Driver
{
public:
	Driver() = default;
	Driver(std::string name, std::string status, std::string location, int score);
	~Driver() = default;

	std::string getName();
	std::string getStatus();
	std::string getLocation();
	int getScore();

	void setScore();
	void setStatus(std::string s);

	friend std::ostream& operator<<(std::ostream& os , const Driver& d);
	friend std::istream& operator>>(std::istream& is, Driver& d);

private:
	std::string name;
	std::string status;
	std::string location;
	int score;
};
