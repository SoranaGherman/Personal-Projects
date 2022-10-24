#pragma once
#include "Movie.h"
#include <string>
#include <iostream>
#include <vector>

class Repository
{
public:
	/// <summary>
	/// Default constructor for movie repo
	/// </summary>
	Repository();

	/// <summary>
	/// Destructor for a movie repo
	/// </summary>
	~Repository();

	/// <summary>
	/// Adds a new movie to the repository
	/// </summary>
	/// <param name="movie">The movie to be added</param>
	virtual void AddElement(const Movie& movie);

	/// <summary>
	/// Removes a movie from the repo
	/// </summary>
	/// <param name="position">The positio of the element to be removed</param>
	virtual void RemoveElemnt(size_t position);

	/// <summary>
	/// Update the title of a movie
	/// </summary>
	/// <param name="position">The position of the movie to be changed</param>
	/// <param name="newTitle">The new title to be given to the movie</param>
	virtual void UpdateTitle(size_t position, std::string newTitle);

	/// <summary>
	/// Update the genre of a movie
	/// </summary>
	/// <param name="position">The position of the movie to be changed</param>
	/// <param name="newGenre">The new genre to be given to the movie</param>
	virtual void UpdateGenre(size_t position, std::string newGenre);

	/// <summary>
	/// Update the year the movie has been released 
	/// </summary>
	/// <param name="position">The position of the movie to be updated</param>
	/// <param name="newYear">The new year to be given to the movie</param>
	virtual void UpdateYear(size_t position, size_t newYear);

	/// <summary>
	/// Update the number of likes of a movie
	/// </summary>
	/// <param name="position">The postition of the movie to be updated</param>
	/// <param name="newLikes">The new number of likes to be given the movie</param>
	virtual void UpdateLikes(size_t position, size_t newLikes);

	/// <summary>
	/// Update the trailer of a movie
	/// </summary>
	/// <param name="position">The position of the movie to be updated</param>
	/// <param name="newTraier">THe new trailer to be given to a certain movie</param>
	virtual void UpdateTrailer(size_t position, std::string newTraier);

	/// <summary>
	/// Find the position of the element which we want to search for
	/// </summary>
	/// <param name="title">The title of the movie to be removed</param>
	/// <returns>The position of the movie</returns>
	size_t FindElemByTitle(std::string title) const;

	size_t GetSize() const;
	std::vector<Movie> GetArray() const;

	friend class RepositoryTests;
private:
	std::vector<Movie> elementsArray;
};

class RepositoryTests
{
public:
	static void TestAll();
	static void TestAdd();
	static void TestRemoveSubscript();
	static void TestUpdate();
	static void TestFind();
	static void TestPrint();
};