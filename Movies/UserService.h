#pragma once
#include "Repository.h"
#include "MovieList.h"
#include <vector>

class UserService
{
public:

	/// <summary>
	/// Constructor for the user servivce
	/// </summary>
	/// <param name="repo">The repository the service depends on</param>
	UserService(Repository& repo);

	/// <summary>
	/// Add an object of type Movie to the watch list
	/// </summary>
	/// <param name="movie">The movie wwe want to add to the watch list</param>
	void AddToWatchList(const Movie& movie);

	/// <summary>
	/// Move the index to the net movie in the list
	/// </summary>
	void GoToNextMovie();

	/// <summary>
	/// Filter the watch list by a given genre
	/// </summary>
	/// <param name="genre">The genre too filter by</param>
	void FilterByGenre(std::string genre);

	/// <summary>
	/// Deletes an obj of type movie from the watch list after seeing it
	/// </summary>
	/// <param name="movie">The movie to delete</param>
	/// /// <param name="likes">After the movie has been deleted, the user has the opportunity to rate the movie</param>
	void DeleteMovieWatchList(std::string movie, size_t likes);

	/// <summary>
	/// Set the index to point to the beginning of the array
	/// </summary>
	void ReinitializeMovieList();

	MovieList getAll();

	std::vector<Movie> getCurrentList();

	~UserService();
	void WriteData();

	int getSize();

	//Getters
	std::vector<Movie> GetMovieList() const;
	Movie GetCurrentMovie() const;
	const std::string& GetFileName() const;
	const std::string& GetWriteMode() const;

	void SetWriteMode(const std::string& newMode);

	friend class UserServicesTests;

private:
	Repository& repo;
	std::vector<Movie> CurrentList;
	MovieList movieList;
	MovieListWriter* writer;
	std::vector<Movie> WatchList;
	size_t index;
	std::string writeMode;
};

class UserServicesTests
{
public:
	static void TestAll();
	static void TestConstructor();
	static void TestSkippingAndAdoption();
	static void TestFilteringAndReinitialization();
	static void TestGetters();
};

