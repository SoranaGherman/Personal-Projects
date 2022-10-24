#include "DriverWindow.h"
#include "qmessagebox.h"
#include <sstream>

DriverWindow::DriverWindow(Service* serv, Driver d, QWidget* parent)
	: serv{ serv }, d{ d }, QWidget(parent)
{
	ui.setupUi(this);
	this->populateList();
	this->connectSignalsAndSlots();
}

void DriverWindow::connectSignalsAndSlots()
{
	QObject::connect(this->ui.ADDpushButton, &QPushButton::clicked, this, &DriverWindow::addButtonHandler);
	QObject::connect(this->ui.VpushButton, &QPushButton::clicked, this, &DriverWindow::vButtonHandler);
	QObject::connect(ui.RlistWidget->selectionModel(), &QItemSelectionModel::selectionChanged, this, &DriverWindow::selectionHandler);
}

void DriverWindow::populateList()
{
	this->ui.RlistWidget->clear();
	std::vector<Road> data = this->serv->getAllReports();
	if (d.getScore() == 10)
	{
		this->setStyleSheet("background-color: yellow");
		d.setStatus("grown-up");
	}
	else if (d.getScore() == 15)
	{
		this->setStyleSheet("background-color: pink");
		d.setStatus("knight");
	}
	std::vector<Driver> dData = this->serv->getAllDrivers();
	for(auto obj: dData)
		if (obj.getName() == d.getName())
		{
			if (obj.getScore() >= 10 && obj.getStatus() == "baby")
			{
				this->setStyleSheet("background-color: yellow");
				d.setStatus("grown-up");
			}
			else if (obj.getScore() >= 15 && obj.getStatus() == "grown-up")
			{
				this->setStyleSheet("background-color: pink");
				d.setStatus("knight");
			}
			this->setWindowTitle(QString::fromStdString(obj.getName() + "     " + obj.getLocation() + "   " + std::to_string(obj.getScore()) +
				"   " + obj.getStatus()));
		}

	for (auto obj : data)
	{
		QString string = QString::fromStdString(obj.getDescription() + " " + obj.getReporter() + " " + obj.getLocation() +
		" " + obj.getValidated());

		this->ui.RlistWidget->addItem(string);
	}
}

void DriverWindow::update()
{
	this->populateList();
}

void DriverWindow::addButtonHandler()
{
	std::string desc = this->ui.DlineEdit->text().toStdString();
	std::string loc = this->ui.LlineEdit->text().toStdString();

	if (desc.empty())
	{
		QMessageBox msg;
		msg.setText("Invalid description!");
		msg.exec();
		return;
	}

	std::istringstream f(loc), ff(d.getLocation());
	std::string lat, longi, latd, longid;
	std::getline(f, lat, ':');
	std::getline(f, longi);

	std::getline(ff, latd, ':');
	std::getline(ff, longid);

	int latI = stoi(lat);
	int longI = stoi(longi);

	int latD = stoi(latd);
	int longD = stoi(longid);

	if (latI - latD > 20 && longI - longD > 20 || loc.empty())
	{
		QMessageBox msg;
		msg.setText("Invalid location!");
		msg.exec();
		return;

	}

	this->serv->addReport(desc, loc, this->d);

}

void DriverWindow::selectionHandler()
{
	std::string item = ui.RlistWidget->currentItem()->text().toStdString();
	std::istringstream f(item);
	std::string description, reporter, location, validated;
	std::getline(f, description, ' ');
	std::getline(f, reporter, ' ');
	std::getline(f, location, ' ');
	std::getline(f, validated, ' ');

	if (validated == "validated")
		this->ui.VpushButton->setDisabled(true);
	else
		this->ui.VpushButton->setEnabled(true);
}

void DriverWindow::vButtonHandler()
{
	std::string item = ui.RlistWidget->currentItem()->text().toStdString();
	std::istringstream f(item);
	std::string description, reporter, location, validated;
	std::getline(f, description, ' ');
	std::getline(f, reporter, ' ');
	std::getline(f, location, ' ');
	std::getline(f, validated, ' ');

	this->serv->validateReport(reporter, description);
	
}
