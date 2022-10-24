#pragma once

#include <vector>
#include <algorithm>
#include <fstream>

#include "Driver.h";
#include "Road.h";

template<typename T>
class Repository
{
public:
	Repository(std::string filePath);
	~Repository() = default;

	std::vector<T> getAll();
	int getSize();
	void clear();
	void addElement(T& elem);
	void removeElement(int index);
	void updateReport(int index);
	void updateScore(int index);


private:
	std::string filePath;
	std::vector<T> data;
	void writeFile();
	void readFile();
};

template<typename T>
inline Repository<T>::Repository(std::string filePath) :
	filePath{ filePath }
{
	this->readFile();
}

template<typename T>
inline std::vector<T> Repository<T>::getAll()
{
	return this->data;
}

template<typename T>
inline int Repository<T>::getSize()
{
	return this->data.size();
}

template<typename T>
inline void Repository<T>::clear()
{
	this->data.clear();
}

template<typename T>
inline void Repository<T>::addElement(T& elem)
{
	this->data.push_back(elem);
	this->writeFile();
}

template<typename T>
inline void Repository<T>::removeElement(int index)
{
	this->data.erase(this->data.begin() + index);
	this->writeFile();
}

inline void Repository<Driver>::updateScore(int index)
{
	this->data[index].setScore();
	this->writeFile();
}

inline void Repository<Road>::updateReport(int index)
{
	this->data[index].setValidated();
	this->writeFile();
}

template<typename T>
inline void Repository<T>::writeFile()
{
	std::ofstream outputFile;
	outputFile.open(filePath, std::ios::out);

	for (auto obj : this->data)
		outputFile << obj;

	outputFile.close();
}

template<typename T>
inline void Repository<T>::readFile()
{
	std::ifstream inputFile;
	inputFile.open(filePath, std::ios::in);

	T obj;

	while (inputFile >> obj)
		this->data.push_back(obj);

	inputFile.close();

}
