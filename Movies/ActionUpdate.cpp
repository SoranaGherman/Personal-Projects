#include "ActionUpdate.h"

ActionUpdate::ActionUpdate(Repository& repo, Movie oldMovie, Movie newMovie) :
	repo{ repo }, oldMovie{ oldMovie }, newMovie{ newMovie }
{
}

void ActionUpdate::executeUndo()
{
	size_t pos = this->repo.FindElemByTitle(oldMovie.GetTitle());
	this->repo.UpdateLikes(pos, oldMovie.GetLikes());
}

void ActionUpdate::executeRedo()
{
	size_t pos = this->repo.FindElemByTitle(newMovie.GetTitle());
	this->repo.UpdateLikes(pos, newMovie.GetLikes());
}
