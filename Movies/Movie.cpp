#include "Movie.h"
#include <sstream>
#include <assert.h>
#include <vector>
#include <fstream>

Movie::Movie() :
	title{ "" }, genre{ "" }, year{ 0 }, likes{ 0 }, trailer{ "" }
{
}

Movie::Movie(std::string title, std::string genre, size_t year, size_t likes, std::string trailer) :
	title{ title }, genre{ genre }, year{ year }, likes{ likes }, trailer{ trailer }
{
}

Movie::~Movie()
{
}

std::ostream& operator<<(std::ostream& os, const Movie& movie)
{
	return os << movie.title << " " << movie.genre << " " << movie.year << " " << movie.likes << " " << movie.trailer <<'\n';
}

std::istream& operator>>(std::istream& is, Movie& movie)
{
	return is >> movie.title >> movie.genre >> movie.year >> movie.likes >> movie.trailer;
}

std::string Movie::GetTitle() const
{
	return this->title;
}

std::string Movie::GetGenre() const
{
	return this->genre;
}

size_t Movie::GetYear() const
{
	return this->year;
}

size_t Movie::GetLikes() const
{
	return this->likes;
}

std::string Movie::GetTrailer() const
{
	return this->trailer;
}


bool Movie::operator==(const Movie& other) const
{
	return this->title == other.title;
}

void Movie::SetTitle(std::string newTitle)
{
	this->title = newTitle;
}

void Movie::SetGenre(std::string newGenre)
{
	this->genre = newGenre;
}

void Movie::SetYear(size_t newYear)
{
	this->year = newYear;
}

void Movie::SetLikes(size_t newLikes)
{
	this->likes = newLikes;
}


void Movie::SetTrailer(std::string newTrailer)
{
	this->trailer = newTrailer;
}

void MovieTests::TestAllMovies()
{
	TestConstructorsAndGettersMovie();
	TestSettersMovie();
	TestEqualityMovie();
	TestExtractionOperator();
}

void MovieTests::TestConstructorsAndGettersMovie()
{
	Movie d1;
	assert(d1.GetTitle() == "");
	assert(d1.GetGenre() == "");
	assert(d1.GetYear() == 0);
	assert(d1.GetLikes() == 0);
	assert(d1.GetTrailer() == "");

	Movie d2("A", "B", 2, 3, "google.com");
	assert(d2.GetTitle() == "A");
	assert(d2.GetGenre() == "B");
	assert(d2.GetYear() == 2);
	assert(d2.GetLikes() == 3);
	assert(d2.GetTrailer() == "google.com");
}

void MovieTests::TestSettersMovie()
{
	Movie d2;
	d2.SetTitle("A");
	d2.SetGenre("B");
	d2.SetYear(2002);
	d2.SetLikes(3);
	d2.SetTrailer("google.com");

	assert(d2.GetTitle() == "A");
	assert(d2.GetGenre() == "B");
	assert(d2.GetYear() == 2002);
	assert(d2.GetLikes() == 3);
	assert(d2.GetTrailer() == "google.com");

}

void MovieTests::TestEqualityMovie()
{
	Movie d1;
	d1.SetTitle("A");
	d1.SetGenre("B");
	d1.SetYear(2002);
	d1.SetLikes(3);
	d1.SetTrailer("google.com");

	Movie d2;
	d2.SetTitle("A");
	d2.SetGenre("B");
	d2.SetYear(2002);
	d2.SetLikes(3);
	d2.SetTrailer("google.com");

	assert(d1 == d2);
	d2.SetTitle("Gigel");
	assert(!(d1 == d2));
}

void MovieTests::TestExtractionOperator()
{
	Movie d1;
	d1.SetTitle("Ion");
	d1.SetGenre("Something");
	d1.SetYear(1980);
	d1.SetLikes(100);
	d1.SetTrailer("site.ro");
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << d1;
	assert(buffer.str() == "Movie: Ion | Genre: Something | Year: 1980 | Nr. of likes: 100 | Trailer: site.ro\n");
}
