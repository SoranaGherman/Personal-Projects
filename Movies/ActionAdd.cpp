#include "ActionAdd.h"

ActionAdd::ActionAdd(Repository& repo, Movie& movie) :
	repo{ repo }, addedMovie{ movie }
{
}

void ActionAdd::executeUndo()
{
	size_t pos = this->repo.FindElemByTitle(this->addedMovie.GetTitle());
	this->repo.RemoveElemnt(pos);
}

void ActionAdd::executeRedo()
{
	this->repo.AddElement(addedMovie);
}
