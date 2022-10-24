#pragma once

#include "Action.h"
#include "Repository.h"

class ActionRemove : public Action
{
public:
	ActionRemove(Repository& repo, Movie movie);
	void executeUndo() override;
	void executeRedo() override;
	~ActionRemove() = default;
	
private:
	Movie removedMovie;
	Repository& repo;
};

