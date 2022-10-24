#include "MapWindow.h"

MapWindow::MapWindow(Service* s, QWidget* parent)
	: s{ s }, QWidget(parent)
{
	ui.setupUi(this);
	this->populateList();
}

MapWindow::~MapWindow()
{
}

void MapWindow::update()
{
	this->populateList();
}

void MapWindow::populateList()
{
	this->ui.listWidget->clear();
	std::vector<Driver> data = this->s->getAllDrivers();

	for (auto obj : data)
	{
		QString string = QString::fromStdString(obj.getName() + " " + obj.getLocation());
		ui.listWidget->addItem(string);
	}
}
