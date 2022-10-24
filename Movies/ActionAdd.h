#pragma once

#include "Action.h"
#include "Repository.h"

class ActionAdd : public Action
{
public:
	ActionAdd(Repository& repo, Movie& movie);
	void executeUndo() override;
	void executeRedo() override;
	~ActionAdd() = default;

private:
	Movie addedMovie;
	Repository& repo;
};

