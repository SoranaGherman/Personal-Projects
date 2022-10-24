#include "AdministratorService.h"
#include <exception>
#include <assert.h>
#include "MovieValidator.h"

AdminService::AdminService(Repository& repository) :
	repo{ repository }
{
}

void AdminService::AddMovie(std::string title, std::string genre, size_t year, size_t likes, std::string trailer)
{
	/*try
		{*/
		Movie newMovie = Movie(title, genre, year, likes, trailer);
		MovieValidator::validate(newMovie);
		bool duplicate = false;
		for (size_t i = 0; i < this->repo.GetSize(); ++i)
			if (this->repo.GetArray()[i] == newMovie) duplicate = true;

		if (duplicate) throw std::exception("A movie with the same name already exists!");

		this->repo.AddElement(newMovie);

		std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(this->repo, newMovie);
		this->undoStack.push_back(move(addAction));

		/*}
	catch (ValidationException& e)
	{
		std::cout << e.getMessage() << std::endl;
	}*/
}

void AdminService::RemoveMovie(std::string title)
{
	size_t pos = this->repo.FindElemByTitle(title);
	if (pos >= this->repo.GetSize())
		throw std::exception("Movie not found!");

	Movie movie = this->repo.GetArray()[pos];

	this->repo.RemoveElemnt(pos);

	std::unique_ptr<Action> removeAction = std::make_unique<ActionRemove>(this->repo, movie);
	this->undoStack.push_back(move(removeAction));
}

void AdminService::UpdateMovieTitle(std::string title, std::string newTitle)
{
	if (!Validator::ValidMovieTitle(newTitle)) throw std::exception("Invalid movie!");
	size_t pos = this->repo.FindElemByTitle(title);

	if (pos >= this->repo.GetSize()) throw std::exception("Movie not found!");
	this->repo.UpdateTitle(pos, newTitle);
}

void AdminService::UpdateMovieGenre(std::string title, std::string newGenre)
{
	if (!Validator::ValidMovieGenre(newGenre)) throw std::exception("Invalid movie!");
	size_t pos = this->repo.FindElemByTitle(title);

	if (pos >= this->repo.GetSize()) throw std::exception("Movie not found!");
	this->repo.UpdateGenre(pos, newGenre);
}

void AdminService::UpdateMovieYear(std::string title, size_t newYear)
{
	if (!Validator::ValidMovieYear(newYear)) throw std::exception("Invalid movie!");
	size_t pos = this->repo.FindElemByTitle(title);

	if (pos >= this->repo.GetSize()) throw std::exception("Movie not found!");
	this->repo.UpdateYear(pos, newYear);
}

void AdminService::UpdateMovieLikes(std::string title, size_t newLikes)
{
	if (!Validator::ValidMovieLikes(newLikes)) throw std::exception("Invalid movie!");
	size_t pos = this->repo.FindElemByTitle(title);

	Movie oldMovie = this->repo.GetArray()[pos];

	if (pos >= this->repo.GetSize()) throw std::exception("Movie not found!");
	this->repo.UpdateLikes(pos, newLikes);

	Movie newMovie = this->repo.GetArray()[pos];

	std::unique_ptr<Action> updateAction = std::make_unique<ActionUpdate>(this->repo, oldMovie, newMovie);

	this->undoStack.push_back(move(updateAction));
}

void AdminService::UpdateMovieTrailer(std::string title, std::string newTraier)
{
	if (!Validator::ValidMovieTrailer(newTraier)) throw std::exception("Invalid movie!");
	size_t pos = this->repo.FindElemByTitle(title);

	if (pos >= this->repo.GetSize()) throw std::exception("Movie not found!");
	this->repo.UpdateTrailer(pos, newTraier);
}

Repository AdminService::GetRepo() const
{
	return this->repo;
}

std::vector<Movie> AdminService::getAll()
{
	return this->repo.GetArray();
}

void AdminService::InitializeRepo()
{
	/*AddMovie("Sinister", "Horror", 2010, 100, "https://google.ro");
	AddMovie("JurasicPark", "Adventure", 2011, 210, "https://google.ro");
	AddMovie("Flowers", "Horror", 2013, 1000, "https://google.ro");
	AddMovie("Mermaid", "Romance", 2018, 3000, "https://google.ro");
	AddMovie("Sinner", "Drama", 2017, 4000, "https://google.ro");
	AddMovie("Anabelle", "Horror", 2020, 2993, "https://google.ro");
	AddMovie("Beatiful", "Romance", 2016, 4002, "https://google.ro");
	AddMovie("Christmas", "Horror", 2022, 4563, "https://google.ro");
	AddMovie("Mama", "Horror", 2013, 10024, "https://google.ro");
	AddMovie("Home", "Horror", 2015, 3000, "https://google.ro");*/
}

void AdminService::undo()
{
	if (this->undoStack.size() == 0)
		throw std::exception("No more undos");

	std::unique_ptr<Action> undoAction = move(this->undoStack.back());
	this->undoStack.pop_back();
	undoAction->executeUndo();
	this->redoStack.push_back(move(undoAction));
}

void AdminService::redo()
{
	if (this->redoStack.size() == 0)
		throw std::exception("No more redo.");

	std::unique_ptr<Action> redoAction = move(this->redoStack.back());
	this->redoStack.pop_back();
	redoAction->executeRedo();
	this->undoStack.push_back(move(redoAction));
}

void AdminServicesTests::TestAll()
{
	TestConstructors();
	TestAdd();
	TestRemove();
	TestUpdate();
}

void AdminServicesTests::TestConstructors()
{
	Repository repo{};
	AdminService s2(repo);
	assert(s2.repo.GetSize() == 0);
}

void AdminServicesTests::TestAdd()
{
	Repository repo{};
	AdminService s2(repo);

	s2.AddMovie("Shutter_Island", "psychological", 2019, 1009, "https://google.ro");
	assert(s2.repo.GetArray()[0].GetTitle() == "Shutter_Island");
	assert(s2.repo.GetArray()[0].GetLikes() == 1009);
	assert(s2.repo.GetArray()[0].GetGenre() == "psychological");
	assert(s2.repo.GetArray()[0].GetYear() == 2019);
	assert(s2.repo.GetArray()[0].GetTrailer() == "https://google.ro");

	s2.AddMovie("Anabelle", "Horror", 2020, 2993, "https://google.ro");
	assert(s2.repo.GetArray()[1].GetTitle() == "Anabelle");
	assert(s2.repo.GetArray()[1].GetLikes() == 2993);
	assert(s2.repo.GetArray()[1].GetGenre() == "Horror");
	assert(s2.repo.GetArray()[1].GetYear() == 2020);
	assert(s2.repo.GetArray()[1].GetTrailer() == "https://google.ro");


}

void AdminServicesTests::TestRemove()
{
	Repository repo{};
	AdminService s2(repo);
	s2.InitializeRepo();
	assert(s2.repo.GetArray()[0].GetTitle() == "Sinister");
	assert(s2.repo.GetArray()[0].GetLikes() == 100);
	assert(s2.repo.GetArray()[0].GetGenre() == "Horror");
	assert(s2.repo.GetArray()[0].GetYear() == 2010);
	assert(s2.repo.GetArray()[0].GetTrailer() == "https://google.ro");

	s2.RemoveMovie("Sinister");
	assert(s2.repo.GetArray()[0].GetTitle() == "JurasicPark");
	assert(s2.repo.GetArray()[0].GetLikes() == 210);
	assert(s2.repo.GetArray()[0].GetGenre() == "Adventure");
	assert(s2.repo.GetArray()[0].GetYear() == 2011);
	assert(s2.repo.GetArray()[0].GetTrailer() == "https://google.ro");

}

void AdminServicesTests::TestUpdate()
{
	Repository repo{};
	AdminService s2(repo);
	s2.InitializeRepo();
	assert(s2.repo.GetArray()[0].GetTitle() == "Sinister");
	assert(s2.repo.GetArray()[0].GetLikes() == 100);
	assert(s2.repo.GetArray()[0].GetGenre() == "Horror");
	assert(s2.repo.GetArray()[0].GetYear() == 2010);
	assert(s2.repo.GetArray()[0].GetTrailer() == "https://google.ro");

	s2.UpdateMovieTitle("Sinister", "Avengers");
	assert(s2.repo.GetArray()[0].GetTitle() == "Avengers");

	s2.UpdateMovieGenre("Avengers", "Adventure");
	s2.UpdateMovieLikes("Avengers", 290);
	s2.UpdateMovieYear("Avengers", 2020);
	s2.UpdateMovieTrailer("Avengers", "https://dog.ro");


	assert(s2.repo.GetArray()[0].GetLikes() == 290);
	assert(s2.repo.GetArray()[0].GetGenre() == "Adventure");
	assert(s2.repo.GetArray()[0].GetYear() == 2020);
	assert(s2.repo.GetArray()[0].GetTrailer() == "https://dog.ro");
}

