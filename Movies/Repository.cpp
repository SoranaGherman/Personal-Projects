#include "Repository.h"
#include <sstream>
#include <assert.h>
#include <fstream>

Repository::Repository()
{
	
}

Repository::~Repository()
{
	
}

//std::ostream& operator<<(std::ostream& os, const Movie& movie)
//{
//	std::ofstream f("file.txt");
//	f << "Movie: " << movie.GetTitle() << " | Genre: " << movie.GetGenre() << " | Year: " << movie.GetYear() << " | Nr. of likes: "
//		<< movie.GetLikes()<< " | Trailer: " << movie.GetTrailer() << "\n";
//
//	return os;
//}

//size_t getInt(std::string string)
//{
//	size_t characters = string.size() - 1;
//	size_t digit;
//	size_t nr = 0, p = 1;
//	while (characters >= 0) {
//		digit = string[characters] - '0';
//		nr = nr + p * digit;
//		p *= 10;
//		characters--;
//	}
//	return nr;
//}

std::vector<std::string> tokenize(std::string str, char delimiter)
{
	std::vector<std::string>result;
	std::stringstream ss(str);
	std::string token;

	while (getline(ss, token, ','))
		result.push_back(token);

	return result;
}

//std::istream& operator>>(std::istream& is, std::vector<Movie>& vec)
//{
//	std::ifstream fin("file.txt");
//	std::string line;
//	getline(is, line);
//	Movie movie;
//
//	while(fin.getline())
//
//	std::vector<std::string> tokens = tokenize(line, ',');
//	if (tokens.size() != 5)
//		return is;
//
//	movie.SetTitle(tokens[0]);
//	movie.SetGenre(tokens[1]);
//	movie.SetYear(getInt(tokens[2]));
//	movie.SetLikes(getInt(tokens[3]));
//	movie.SetTrailer(tokens[4]);
//
//	vec.push_back(movie);
//
//	return is;
//}

void Repository::AddElement(const Movie& movie)
{
	this->elementsArray.push_back(movie);
}

void Repository::RemoveElemnt(size_t position)
{
	this->elementsArray.erase(this->elementsArray.begin() + position);
}

void Repository::UpdateTitle(size_t position, std::string newTitle)
{
	this->elementsArray[position].SetTitle(newTitle);
}

void Repository::UpdateGenre(size_t position, std::string newGenre)
{
	this->elementsArray[position].SetGenre(newGenre);
}

void Repository::UpdateYear(size_t position, size_t newYear)
{
	this->elementsArray[position].SetYear(newYear);
}

void Repository::UpdateLikes(size_t position, size_t newLikes)
{
	this->elementsArray[position].SetLikes(newLikes);
}

void Repository::UpdateTrailer(size_t position, std::string newTrailer)
{
	this->elementsArray[position].SetTrailer(newTrailer);
}

size_t Repository::FindElemByTitle(std::string title) const
{
	auto it = find_if(this->elementsArray.begin(), this->elementsArray.end(), [title](Movie m) {return m.GetTitle() == title;});
	if (it == this->elementsArray.end()) return -1;

	return it - this->elementsArray.begin();
}

size_t Repository::GetSize() const
{
	return this->elementsArray.size();
}

std::vector<Movie> Repository::GetArray() const
{
	return this->elementsArray;
}


void RepositoryTests::TestAll()
{
	TestAdd();
	TestRemoveSubscript();
	TestUpdate();
	TestFind();
	TestPrint();
}
void RepositoryTests::TestAdd()
{
	Repository repo2{};
	Movie d1("Idk", "Idk", 1, 2, "google.com");
	Movie d2("Idk", "Idk1", 1, 2, "google.com");
	Movie d3("Idk", "Idk2", 1, 2, "google.com");
	Movie d4("Idk", "Idk3", 1, 2, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	assert(repo2.GetArray()[0] == d1);
	assert(repo2.GetArray()[1] == d2);
	assert(repo2.GetArray()[2]== d3);
	assert(repo2.GetArray()[3] == d4);
}

void RepositoryTests::TestRemoveSubscript()
{
	Repository repo2{};
	Movie d1("Idk", "Idk", 1, 2, "google.com");
	Movie d2("Idk", "Idk1", 1, 2, "google.com");
	Movie d3("Idk", "Idk2", 1, 2, "google.com");
	Movie d4("Idk", "Idk3", 1, 2, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	repo2.RemoveElemnt(1);

	assert(repo2.GetArray()[0] == d1);
	assert(repo2.GetArray()[1] == d3);
	assert(repo2.GetArray()[2] == d4);
}

void RepositoryTests::TestUpdate()
{
	Repository repo2{};
	Movie d1("Idk", "Idk", 1, 2, "google.com");
	repo2.AddElement(d1);

	repo2.UpdateTitle(0, "A");
	repo2.UpdateGenre(0, "B");
	repo2.UpdateYear(0, 2002);
	repo2.UpdateLikes(0, 209);
	repo2.UpdateTrailer(0, "google.ro");
	assert(repo2.GetArray()[0].GetTitle() == "A");
	assert(repo2.GetArray()[0].GetGenre() == "B");
	assert(repo2.GetArray()[0].GetYear() == 2002);
	assert(repo2.GetArray()[0].GetLikes() == 209);
	assert(repo2.GetArray()[0].GetTrailer() == "google.ro");

}

void RepositoryTests::TestFind()
{
	Repository repo2{};
	Movie d1("Idk", "Idk", 1, 2, "google.com");
	Movie d2("Idk", "Idk1", 1, 2, "google.com");
	Movie d3("Idkk", "Idk2", 1, 2, "google.com");
	Movie d4("Idk", "Idk3", 1, 2, "google.com");
	repo2.AddElement(d1);
	repo2.AddElement(d2);
	repo2.AddElement(d3);
	repo2.AddElement(d4);

	size_t position = repo2.FindElemByTitle("Idkk");
	assert(position == 2);
}

void RepositoryTests::TestPrint()
{
	Repository repo{};
	Movie d1("Ion", "Something", 1980, 100, "site.ro");
	std::stringbuf buffer;
	std::ostream os(&buffer);
	os << d1;
	assert(buffer.str() == "Movie: Ion | Genre: Something | Year: 1980 | Nr. of likes: 100 | Trailer: site.ro\n");
}

