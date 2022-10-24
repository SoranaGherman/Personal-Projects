#include "UserService.h"
#include <exception>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <fstream>

UserService::UserService(Repository& repo) :
	repo{ repo }, CurrentList{ repo.GetArray() }, WatchList{ std::vector < Movie >(1) }, index{ 0 }, writer{ nullptr }, writeMode{ "" }, movieList{MovieList()}
{
}

UserService::~UserService()
{
	delete writer;
}

void UserService::WriteData()
{
	writer->WriteToFile(movieList);
}

int UserService::getSize()
{
	return this->WatchList.size();
}

void UserService::AddToWatchList(const Movie& movie)
{
	
	/*bool found = false;

	if (this->WatchList.size() > 1)
	{
		auto it = find_if(this->WatchList.begin(), this->WatchList.end(), [movie](Movie m) {return m == movie;});
		if (it == this->WatchList.end()) found = true;
	}

	if (found) throw std::exception("The movie has already been added to the watch list!");*/
	movieList.AddMovie(movie);
	WatchList.push_back(movie);
	GoToNextMovie();

}

void UserService::GoToNextMovie()
{
	if (index == CurrentList.size() - 1)
	{
		index = 0;
		return;
	}
	index++;
}

void UserService::FilterByGenre(std::string genre)
{
	size_t i = 0;

	if (genre != "")
		while (i != CurrentList.size() - 1)
		{
			if (CurrentList[i].GetGenre() != genre)
				CurrentList.erase(CurrentList.begin() + i), i--;
			i++;
		}
	index = 0;
}

void UserService::DeleteMovieWatchList(std::string movie, size_t likes)
{
	bool found = false;
	for (size_t i = 0; i < WatchList.size() && !found; i++)
		if (WatchList[i].GetTitle() == movie)
		{
			found = true;
			if (likes > 0)
			{
				size_t currentLikes = WatchList[i].GetLikes() + likes;
				bool found1 = false;
				for (size_t j = 0; j < CurrentList.size() && !found1; j++)
					if (CurrentList[j].GetTitle() == movie)
					{
						found1 = true;
						repo.UpdateLikes(j, currentLikes);
						CurrentList[j].SetLikes(currentLikes);
					}
			}

			WatchList.erase(WatchList.begin() + i);
		}
	if (!found) throw std::exception("The movie you want to remove does not exist!");
}

void UserService::ReinitializeMovieList()
{
	if (CurrentList == repo.GetArray())
		return;

	CurrentList = repo.GetArray();
	index = 0;
}

MovieList UserService::getAll()
{
	return movieList;
}

std::vector<Movie> UserService::getCurrentList()
{
	return CurrentList;
}

std::vector<Movie> UserService::GetMovieList() const
{
	return WatchList;
}

Movie UserService::GetCurrentMovie() const
{
	return CurrentList[index];
}

const std::string& UserService::GetFileName() const
{
	return writer->GetFileName();
}

const std::string& UserService::GetWriteMode() const
{
	return writeMode;
}

void UserService::SetWriteMode(const std::string& newMode)
{
	if (newMode == "CSV")
	{
		writeMode = newMode;
		writer = new CSVMovieListWriter("adoption_list.csv");
	}
	else if (newMode == "HTML")
	{
		writeMode = newMode;
		writer = new HTMLMovieListWriter("adoption_list.html");
	}
	else
	{
		throw std::exception("Unhandled mode!");
	}
}

void UserServicesTests::TestAll()
{
	TestConstructor();
	TestSkippingAndAdoption();
	TestFilteringAndReinitialization();
	TestGetters();
}

void UserServicesTests::TestConstructor()
{
	Repository repo{};
	repo.AddElement(Movie("Sinister", "Horror", 2010, 100, "https://google.ro"));
	repo.AddElement(Movie("JurasicPark", "Adventure", 2011, 210, "https://google.ro"));
	repo.AddElement(Movie("Flowers", "Horror", 2013, 1000, "https://google.ro"));
	repo.AddElement(Movie("Mermaid", "Romance", 2018, 3000, "https://google.ro"));
	repo.AddElement(Movie("Sinner", "Drama", 2017, 4000, "https://google.ro"));
	repo.AddElement(Movie("Anabelle", "Horror", 2020, 2993, "https://google.ro"));
	repo.AddElement(Movie("Beatiful", "Romance", 2016, 4002, "https://google.ro"));
	repo.AddElement(Movie("Christmas", "Horror", 2022, 4563, "https://google.ro"));
	repo.AddElement(Movie("Mama", "Horror", 2013, 10024, "https://google.ro"));
	repo.AddElement(Movie("Home", "Horror", 2015, 3000, "https://google.ro"));
	UserService s1(repo);
	assert(s1.CurrentList == repo.GetArray());
	assert(s1.index == 0);
	assert(s1.WatchList.size() == 0);
}

void UserServicesTests::TestSkippingAndAdoption()
{
	Repository repo{};
	repo.AddElement(Movie("Sinister", "Horror", 2010, 100, "https://google.ro"));
	repo.AddElement(Movie("JurasicPark", "Adventure", 2011, 210, "https://google.ro"));
	UserService s1(repo);

	assert(s1.WatchList.size() == 1);
	assert(s1.index == 1);

	s1.GoToNextMovie();
	assert(s1.index == 0);
}

void UserServicesTests::TestFilteringAndReinitialization()
{
	Repository repo{};
	repo.AddElement(Movie("Sinister", "Horror", 2010, 100, "https://google.ro"));
	repo.AddElement(Movie("JurasicPark", "Adventure", 2011, 210, "https://google.ro"));
	repo.AddElement(Movie("Flowers", "Horror", 2013, 1000, "https://google.ro"));
	repo.AddElement(Movie("Mermaid", "Romance", 2018, 3000, "https://google.ro"));
	repo.AddElement(Movie("Sinner", "Drama", 2017, 4000, "https://google.ro"));
	repo.AddElement(Movie("Anabelle", "Horror", 2020, 2993, "https://google.ro"));
	repo.AddElement(Movie("Beatiful", "Romance", 2016, 4002, "https://google.ro"));
	repo.AddElement(Movie("Christmas", "Horror", 2022, 4563, "https://google.ro"));
	repo.AddElement(Movie("Mama", "Horror", 2013, 10024, "https://google.ro"));
	repo.AddElement(Movie("Home", "Horror", 2015, 3000, "https://google.ro"));
	UserService s1(repo);

	s1.FilterByGenre("Horror");
	assert(s1.CurrentList.size() == 6);
	assert(s1.CurrentList[0] == Movie("Sinister", "Horror", 2010, 100, "https://google.ro"));
	assert(s1.CurrentList[1] == Movie("Flowers", "Horror", 2013, 1000, "https://google.ro"));

	s1.ReinitializeMovieList();
	assert(s1.CurrentList.size() == 10);
	assert(s1.index == 0);

	s1.FilterByGenre("");
	assert(s1.CurrentList.size() == 10);

	s1.ReinitializeMovieList();
	assert(s1.CurrentList.size() == 10);
	assert(s1.index == 0);

	s1.ReinitializeMovieList();
	assert(s1.CurrentList.size() == 10);
	assert(s1.index == 0);

	s1.WatchList.push_back(Movie("Sinister", "Horror", 2002, 100, "https://google.ro"));
	s1.WatchList.push_back(Movie("Flowers", "Horror", 2013, 1000, "https://google.ro"));
	assert(s1.WatchList[0].GetTitle() == "Sinister");
	assert(s1.WatchList.size() == 2);
	s1.DeleteMovieWatchList("Sinister", 10);
	assert(s1.WatchList.size() == 1);
	assert(s1.WatchList[0].GetTitle() == "Flowers");

	bool found = false;
	size_t index = 0;
	for (size_t j = 0; j < s1.CurrentList.size() && !found; j++)
		if (s1.CurrentList[j].GetTitle() == "Sinister")
		{
			found = true;
			assert(s1.CurrentList[j].GetLikes() == 110);
			index = j;
		}
}

void UserServicesTests::TestGetters()
{
	Repository repo{};
	repo.AddElement(Movie("Mermaid", "Romance", 2018, 3000, "https://google.ro"));
	repo.AddElement(Movie("Mama", "Horror", 2013, 10024, "https://google.ro"));
	UserService s1(repo);

	/*s1.AddToWatchList(s1.repo[s1.index]);

	s1.GoToNextMovie();

	assert(s1.GetMovieList() == s1.WatchList);
	assert(s1.GetCurrentMovie() == Movie("Mermaid", "Romance", 2018, 3000, "https://google.ro"));
	try
	{
		s1.AddToWatchList(s1.repo[s1.index]);
		assert(false);
	}
	catch (std::exception& ex)
	{
		assert(true);
	}*/
}