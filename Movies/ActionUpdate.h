#pragma once

#include "Action.h"
#include "Repository.h"

class ActionUpdate : public Action
{
public:
	ActionUpdate(Repository& repo, Movie oldMovie, Movie newMovie);
	void executeUndo() override;
	void executeRedo() override;
	~ActionUpdate() = default;

private:
	Movie oldMovie;
	Movie newMovie;
	Repository& repo;
};

