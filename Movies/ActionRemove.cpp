#include "ActionRemove.h"

ActionRemove::ActionRemove(Repository& repo, Movie movie) :
	repo{ repo }, removedMovie{ movie }
{
}

void ActionRemove::executeUndo()
{
	this->repo.AddElement(this->removedMovie);
}

void ActionRemove::executeRedo()
{
	size_t pos = this->repo.FindElemByTitle(this->removedMovie.GetTitle());
	this->repo.RemoveElemnt(pos);
}
